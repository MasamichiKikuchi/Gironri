#include	"deck.h"
#include	"gamemain.h"
#include	"winmain.h"
#include	"mymath.h"
#include	"data.h"
#include	"scenegamemain.h"

Deck::Deck()
{
	int i;

	flg_selectCard = 0;
	cardMoveFlag = 0;
	getCnt = 0;
	turnCnt = 0;
	deckCutInflag = -1;
	frame = 0;
}

Deck::~Deck()
{

}

// 手札の中心位置（選択中のカード）
int Deck::GetCenterCard()
{
	int i = cards.size() / 2;
	return i;
}

// カードのX座標の計算式
float Deck::calcX(int i)
{
	float x = SCREEN_W / 2 + (i - GetCenterCard()) * 300;
	return x;
}

// 同じ証言を所持しているかの確認
bool Deck::CheckCard(int number, int ttmcnt)
{
	int i;
	for (i = 0; i < cards.size(); i++)
	{
		// 所持しているカードの証言者番号と同じ番号があるかと、同じ証言であるかをチェック
		if (number == cards[i].num && ttmcnt == cards[i].testimonyCnt) { return TRUE; }
	}
	return FALSE;
}

// 手札追加
void Deck::GetCard(int number, int cgCard, int wordX, int wordY, float wordScale, int wordTtmCnt)
{
	struct CARD setCard = { number, cgCard , VGet(wordX, wordY, 0), wordScale, 1, wordTtmCnt};
	cards.push_back(setCard);		// デッキの最後尾に新規取得カードを追加
}

// カード選択, 正解判定
void Deck::SelectCard()
{
	int i;

	switch (gPad.gTrg)
	{
	// 左に1つずれる
	case PAD_INPUT_LEFT:
		cards.push_front(cards.back());
		cards.pop_back();
		PlaySoundMem(seCardSelecting, DX_PLAYTYPE_BACK, TRUE);
		turnCnt = 0;
		break;
	// 右に１つずれる
	case PAD_INPUT_RIGHT:
		cards.push_back(cards.front());
		cards.pop_front();
		PlaySoundMem(seCardSelecting, DX_PLAYTYPE_BACK, TRUE);
		turnCnt = 0;
		break;
	}
	// カード決定
	if (gPad.gTrg & PAD_INPUT_4)
	{
		if (cards[cards.size() / 2].num == answer_card
			&& cards[cards.size() / 2].testimonyCnt == tblAnsCard[gameChapter].ansCardCnt)		// 正解
		{
			flg_ans = 1;
			flg_selectCard = 4;
			PlaySoundMem(seCutin, DX_PLAYTYPE_BACK, TRUE);
		}
		else												// 不正解
		{
			flg_ans = 2;
			PlaySoundMem(seHazure, DX_PLAYTYPE_BACK, TRUE);
		}
	}
}

// カードの裏返し
void Deck::TurnCard()
{
	int center = GetCenterCard();			// 選択中のカード位置
	int tCnt = (int)(turnCnt / 10) - 2;		// 画像変更タイミング
	if (tCnt >= 3)
	{
		cards[center].cg = cgReturnCard[gameChapter][cards[center].num][cards[center].testimonyCnt];	// 正解のカード画像
	}
	else if (tCnt > 0)
	{
		cards[center].cg = cgTurnCard[tCnt];		// 裏返し中のカード画像
		if (tCnt == 2)
		{
			PlaySoundMem(seCardTurning, DX_PLAYTYPE_BACK, TRUE);
		}
	}
}

// 議論中カードモーション
void Deck::MotionCard(int flg_gf)
{
	int i;
	int count = 0;

	switch (flg_gf)
	{
	case 0:		// 偽証議論パート
		for (i = 0; i < cards.size(); i++)
		{
			cards[i].pos.x = DECK_CARD_X;
			cards[i].pos.y = DECK_CARD_Y - i * 116;
			cards[i].scale = 1.0f;
			if (cards[i].motionCnt > 0)
			{
				cards[i].motionCnt++;
				if (cards[i].motionCnt > 60) { cards[i].motionCnt = 0; }
			}
		}
		break;
	case 1:		// 反論パート
		// カード展開
		switch (flg_selectCard)
		{
		case 0:		// 画面外に移動
			if (cards[0].pos.y < SCREEN_H + 100)
			{
				cards[0].pos.y += 10;
				for (i = 1; i < cards.size(); i++)
				{
					if (cards[i].pos.y <= cards[0].pos.y) { cards[i].pos.y = cards[0].pos.y; }
				}
			}
			else { flg_selectCard = 1; }
			break;
		case 1:		// 画面内に移動
			if (cards[0].pos.y > 900)
			{
				for (i = 0; i < cards.size(); i++)
				{
					cards[i].pos.x = SCREEN_W / 2;
					cards[i].pos.y -= 10;
				}
			}
			else
			{
				PlaySoundMem(seCardOpening, DX_PLAYTYPE_BACK, TRUE);
				flg_selectCard = 2;
				for (i = 0; i < cards.size(); i++) { cards[i].pos.y = 900; }
			}
			break;
		case 2:		// 展開
			for (i = 0; i < cards.size(); i++)
			{
				if (cards[i].pos.x == calcX(i)) { count++; }

				if (i < GetCenterCard())
				{
					if (cards[i].pos.x > calcX(i)) { cards[i].pos.x -= 10; }
					else { cards[i].pos.x = calcX(i); }
				}
				else if (i > GetCenterCard())
				{
					if (cards[i].pos.x < calcX(i)) { cards[i].pos.x += 10; }
					else { cards[i].pos.x = calcX(i); }
				}
			}
			if (count >= cards.size()) { flg_selectCard = 3; }
			break;
		// カード選択
		case 3:
			if (flg_ans == 0) { SelectCard(); }
			break;
		}
		break;
	case 2:
		break;
	}
}

// ゲーム状況に合わせてカードを変更
void Deck::SetDrawCard(int flg_gf)
{
	int i;
	
	switch (flg_gf)
	{
	// 議論パート
	case 0:
		for (i = 0; i < cards.size(); i++)
		{
			// 議論パート
			cards[i].cg = cgStockCard[gameChapter][cards[i].num][cards[i].testimonyCnt];
			if (cards[i].motionCnt > 0)
			{
				cards[i].cg = cgStockWhiteCard;
			}
		}
		break;
	// 反論パート
	case 1:
		if (flg_selectCard == 0)
		{
			for (i = 0; i < cards.size(); i++)
			{
				// 議論パート
				cards[i].cg = cgStockCard[gameChapter][cards[i].num][cards[i].testimonyCnt];
			}
		}
		else
		{
			for (i = 0; i < cards.size(); i++)
			{
				// 展開・選択
				cards[i].cg = cgCounterCard[gameChapter][cards[i].num][cards[i].testimonyCnt];
			}

			if (flg_selectCard >= 3)
			{
				// カードを裏返す
				TurnCard();
				turnCnt++;
			}
		}
		break;
	// フィニッシュ（結果）
	case 2:
		
		break;
	}
}

// カード表示
void Deck::DrawCard(int flg_gf)
{
	int i, j;
	int center = GetCenterCard();		// 選択中のカード位置
	switch (flg_gf)
	{
	case 0:		// 議論パート
		for (i = 0; i < deckMax[gameChapter]; i++)
		{
			// 手札の空き表示
			// 証言を手に入れている場合、その位置には表示しない
			if (i >= cards.size()) { DrawRotaGraph(DECK_CARD_X, DECK_CARD_Y - i * 116, 1.0f, 0.0f, cgStockBrankCard, TRUE, 0); }
		}
		for (j = 0; j < cards.size(); j++)
		{
			DrawRotaGraph(cards[j].pos.x, cards[j].pos.y, cards[j].scale, 0.0f, cards[j].cg, TRUE, 0);
		}
		break;
	case 1:		// 反論パート
		// カード展開中
		if (flg_selectCard < 3)
		{
			for (i = 0; i < cards.size(); i++)
			{
				DrawRotaGraph(cards[i].pos.x, cards[i].pos.y, cards[i].scale, 0.0f, cards[i].cg, TRUE, 0);
			}
		}
		// 選択時
		else
		{
			for (i = 0; i < cards.size(); i++)
			{
				// カードの位置をセット
				if (cardMoveFlag != 1)
				{
					cards[i].pos.x = calcX(i);
					cards[center].pos.x = SCREEN_W / 2;
					cards[i].pos.y = 900;
					cards[i].scale = 1.0f;
				}
				// 選択中のカードは大きく表示
				if (i == center)
				{
					DrawRotaGraph(cards[i].pos.x, cards[i].pos.y, cards[i].scale, 0.0f, cards[i].cg, TRUE, 0);
				}
				// 選択していないカードは小さく薄く表示
				else
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
					DrawRotaGraph(cards[i].pos.x, cards[i].pos.y, cards[i].scale - 0.3f, 0.0f, cards[i].cg, TRUE, 0);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
				}
			}
		}
		break;
	case 2:		// 終了
		// 不正解
		if (flg_ans == 2)
		{
			for (i = 0; i < cards.size(); i++)
			{
				// 選択中のカードは大きく表示
				if (i == center)
				{
					DrawRotaGraph(cards[i].pos.x, cards[i].pos.y, cards[i].scale, 0.0f, cards[i].cg, TRUE, 0);
				}
				// 選択していないカードは小さく薄く表示
				else
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
					DrawRotaGraph(cards[i].pos.x, cards[i].pos.y, cards[i].scale - 0.3f, 0.0f, cards[i].cg, TRUE, 0);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
				}
			}
		}
		break;
	}
}

// カードの移動
void Deck::MoveCard(int &flg_gf)
{
	int center = GetCenterCard();		//選択中のカード位置
	cards[center].speed = CARD_SPEED;

	if (cards[center].scale >= 0)cards[center].scale -= DECREASE_SCALE;		//徐々に小さくなる

	float rad;
	int target;

	//カードの飛ぶ方向を設定
	for (int j = 0; j < ENEMY_MAX; j++)
	{
		if (j == cards[center].num)
		{
			rad = atan2(gikai[j].Y - cards[center].pos.y, gikai[j].X - cards[center].pos.x);
			target = j;
		}
	}

	// 角度をradianからdegreeに変換
	cards[center].direction = RadToDeg(rad);
	// 現在の角度でベクトルを作る
	VECTOR vDir = VGet(0, 0, 0);
	// 角度をdegreeからradianに変換
	float rad_2 = DegToRad(cards[center].direction);
	vDir.x = cos(rad_2);
	vDir.y = sin(rad_2);
	// 作ったベクトルを単位ベクトルにする
	VECTOR vUnit = VNorm(vDir);
	// 移動ベクトルを作る
	VECTOR vMove = VScale(vUnit, cards[center].speed);
	// 移動ベクトルを位置に加算する
	cards[center].pos = VAdd(cards[center].pos, vMove);

	if ((cards[center].pos.x > gikai[target].X - ENEMY_HIT_X && cards[center].pos.x < gikai[target].X + ENEMY_HIT_X) && (cards[center].pos.y > gikai[target].Y - ENEMY_HIT_Y && cards[center].pos.y < gikai[target].Y + ENEMY_HIT_Y))
	{
		cardMoveFlag = 0; 		//目的地に着いたら動かなくなる
		flg_gf = 2;		//シーン切り替え
	}
}

void Deck::SetCutInFlag(int cutInFlag)
{
	deckCutInflag = cutInFlag;
}
