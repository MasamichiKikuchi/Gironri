#include	"scenelook.h"
#include	"DxLib.h"
#include	"gamemain.h"
#include	"scenetalk.h"
#include	"scenegamemain.h"
#include	"mymath.h"
#include	"data.h"
#include	"SceneGameover.h"

SceneLook::SceneLook(int chapter)
{
	gameChapter = chapter;
	int i = 0;

	flgAnswer = 0;

	vSpotLight = VGet(tblLookPoint[gameChapter].initX, tblLookPoint[gameChapter].initY, 0);
	spotlightSize = SPOTLIGHT_SIZE_MAX;
	ansLightSize = 0;
	vInputR = VGet(0, 0, 0);
	vUnitR = VGet(1, 1, 1);
	vDirR = VGet(0, 0, 0);

	talkCnt = 0;
	flgAllTalk = 0;
	allTalkCnt = 0;
	lineflg = 0;

	// エフェクト情報の初期化
	gEffect.InitEffect();

	lightCnt = 0;
	step = 0;

	flgLook = 0;
	UniqueNoAnsCnt = 0;

	// BGM・se
	// 音量調整
	ChangeVolumeSoundMem(255 * LOOK_BGM_VOLUME / 100, seLookBGM);
	ChangeVolumeSoundMem(255 * LOOK_SE_VOLUME / 100, seLookDamage);
	ChangeVolumeSoundMem(255 * LOOK_SE_VOLUME / 100, seLookHazure);
	ChangeVolumeSoundMem(255 * LOOK_SE_VOLUME / 100, seLookSeikai);
	// BGM再生
	PlaySoundMem(seLookBGM, DX_PLAYTYPE_LOOP);
}

SceneLook::~SceneLook()
{
	
}

// ライトマップの値のセット
void SceneLook::SetLightMap()
{
	int x, y;

	// ライトマップ全体をALPHA_VALUEの値にする
	for (y = 0; y < LIGHTMAP_H; y++) {
		for (x = 0; x < LIGHTMAP_W; x++) {
			mapLight[y * LIGHTMAP_W + x] = ALPHA_VALUE;
		}
	}
	// 正解用ライトマップ全体の値を0にする
	for (y = 0; y < LIGHTMAP_H; y++) {
		for (x = 0; x < LIGHTMAP_W; x++) {
			mapAnsLight[y * LIGHTMAP_W + x] = 0;
		}
	}
}

// ライトのマスデータに円のスポットライトを入れる
void SceneLook::SpotLight(int cx, int cy, int cr, int alpha, int typeAns)
{
	int x, y, a;

	// pixel単位からマップ単位に変換
	cx /= LIGHTSIZE_W;
	cy /= LIGHTSIZE_H;
	cr /= LIGHTSIZE_W;

	// 中心座標(cx,cy)を、半径rで囲う正方形を範囲とする
	for (y = cy - cr; y < cy + cr; y++) {
		if (0 <= y && y < LIGHTMAP_H) {		// マップ内に入っているか
			for (x = cx - cr; x < cx + cr; x++) {
				if (0 <= x && x < LIGHTMAP_W) {		// マップ内に入っているか

					// 中心座標(cx,cy)からの距離を求め、アルファ値を決める
					int len = (int)(((cx - x) * (cx - x) + (cy - y) * (cy - y)));

					// crが減衰値なので、len/crでアルファが決まる
					a = len * alpha / (cr * cr);	// sqrt()を使わないので、cr^2で割って処理する
					if (a > alpha) { a = alpha; }

					switch (typeAns)
					{
					case 0:
						// アルファの値で穴をあける
						mapLight[y * LIGHTMAP_W + x] = a;

						break;
					case 1:
						// スポットライトの中心から白くなっていく
						mapAnsLight[y * LIGHTMAP_W + x] = alpha - a;
						break;
					}
				}
			}
		}
	}
}

// 右スティックの入力値の正規化
void SceneLook::NormInput(XINPUT_STATE xinput)
{
	vInputR = VGet(xinput.ThumbLX, -xinput.ThumbLY, 0);
	vUnitR = VNorm(vInputR);
}

// 円の移動
void SceneLook::splMove(XINPUT_STATE xinput)
{
	// 移動距離の計算
	if (abs(xinput.ThumbLX) > 10000 || abs(xinput.ThumbLY) > 10000)
	{
		NormInput(xinput);
		vDirR = VScale(vUnitR, SPOTLIGHT_SPEED);
	}
	else
	{
		vDirR = VGet(0, 0, 0);
	}

	// 移動距離の加算
	vSpotLight = VAdd(vSpotLight, vDirR);
	
	// 移動可能範囲による制限
	// x座標
	if (vSpotLight.x < 0) { vSpotLight.x = 0; }
	else if (vSpotLight.x > SCREEN_W) { vSpotLight.x = SCREEN_W; }
	// y座標
	if (vSpotLight.y < 0) { vSpotLight.y = 0; }
	else if (vSpotLight.y > 806) { vSpotLight.y = 806; }
}

// 円のサイズ変更（拡大縮小）
void SceneLook::splScale(XINPUT_STATE xinput)
{
	// 左トリガーで拡大
	if (xinput.LeftTrigger > 100)
	{
		spotlightSize += LIGHTSIZE_W;
		if (spotlightSize > SPOTLIGHT_SIZE_MAX) { spotlightSize = SPOTLIGHT_SIZE_MAX; }
	}
	// 右トリガーで縮小
	if (xinput.RightTrigger > 100)
	{
		spotlightSize -= LIGHTSIZE_W;
		if (spotlightSize < SPOTLIGHT_SIZE_MIN) { spotlightSize = SPOTLIGHT_SIZE_MIN; }
	}
}

// 睨んだ箇所のチェック
void SceneLook::CheckPoint(float px, float py)
{
	int i;

	// 当たり判定の範囲が円
	if (tblLookPoint[gameChapter].hittype == 0)
	{
		// 怪しい箇所の円内にスポットライトの中心があるかどうか
		if (IsHitPointCircle(px, py,
			tblLookPoint[gameChapter].x, tblLookPoint[gameChapter].y, tblLookPoint[gameChapter].r))
		{
			flgAnswer = 1;	// 正解
		}
		else
		{
			flgAnswer = 2;	// 不正解
		}
	}
	// 当たり判定の範囲が矩形
	else
	{
		// 怪しい箇所の矩形内にスポットライトの中心があるかどうか
		if (IsHitPointBox(px, py,
			tblLookPoint[gameChapter].x, tblLookPoint[gameChapter].y, tblLookPoint[gameChapter].w, tblLookPoint[gameChapter].h))
		{
			flgAnswer = 1;	// 正解
		}
		else
		{
			flgAnswer = 2;	// 不正解
		}
	}

	// 不正解の時、特殊不正解か
	if (flgAnswer == 2)
	{
		// 特殊不正解
		for (i = 0; i < 6; i++)
		{
			if (tblLookEaster[gameChapter][i].hittype == 0)
			{
				// 怪しい箇所の円内にスポットライトの中心があるかどうか
				if (IsHitPointCircle(px, py,
					tblLookEaster[gameChapter][i].x, tblLookEaster[gameChapter][i].y, tblLookEaster[gameChapter][i].r))
				{
					flgAnswer = 3;	// 特殊不正解
					UniqueNoAnsNum = i;
					break;
				}
				else
				{
					flgAnswer = 2;	// 不正解
				}
			}
			else
			{
				// 怪しい箇所の矩形内にスポットライトの中心があるかどうか
				if (IsHitPointBox(px, py,
					tblLookEaster[gameChapter][i].x, tblLookEaster[gameChapter][i].y, tblLookEaster[gameChapter][i].w, tblLookEaster[gameChapter][i].h))
				{
					flgAnswer = 3;	// 特殊不正解
					UniqueNoAnsNum = i;
					break;
				}
				else
				{
					flgAnswer = 2;	// 不正解
				}
			}
		}
	}

	if (flgAnswer == 3 && gameChapter == 2 && UniqueNoAnsNum > 0)
	{
		UniqueNoAnsCnt++;
	}

	// エフェクト・SE
	if (flgAnswer == 1)
	{
		// 正解
		PlaySoundMem(seLookSeikai, DX_PLAYTYPE_BACK);
	}
	else if (flgAnswer >= 2)
	{
		// ハズレ・特殊不正解
		PlaySoundMem(seLookHazure, DX_PLAYTYPE_BACK);

		// エフェクト追加
		gEffect.AddEffect(1, SCREEN_W / 2, SCREEN_H / 2);
		gEffect.shakecnt = 30;
		gEffect.shakespead = 10;
		gHP -= 20;	// HP減少
	}
}

// 怪しい箇所を選択時のセリフ
void SceneLook::lookTalk()
{
	int i, ansNum = 0;
	for (i = 0; i < tblLPSize; i++)
	{
		if (tblLookPoint[i].chapter == gameChapter) { ansNum = i; }
	}

	int drawCnt = (talkCnt / DRAW_MESSAGE_COUNT) * 2;
	std::string message[3];
	const char* messageByte[3];
	switch (flgAnswer)
	{
	case 0:
		message[0] = tblLookPoint[ansNum].lookingMessage;
		messageByte[0] = tblLookPoint[ansNum].lookingMessage.c_str();
		break;
	case 1:
		message[0] = tblLookPoint[ansNum].trueMessage;
		messageByte[0] = tblLookPoint[ansNum].trueMessage.c_str();
		break;
	case 2:
		message[0] = tblLookPoint[ansNum].falseMessage;
		messageByte[0] = tblLookPoint[ansNum].falseMessage.c_str();
		break;
	case 3:
		if (!tblLookEaster[gameChapter][UniqueNoAnsNum].message1.empty())
		{
			message[0] = tblLookEaster[gameChapter][UniqueNoAnsNum].message1;
			messageByte[0] = tblLookEaster[gameChapter][UniqueNoAnsNum].message1.c_str();
		}
		if (!tblLookEaster[gameChapter][UniqueNoAnsNum].message2.empty())
		{
			message[1] = tblLookEaster[gameChapter][UniqueNoAnsNum].message2;
			messageByte[1] = tblLookEaster[gameChapter][UniqueNoAnsNum].message2.c_str();
		}
		if (!tblLookEaster[gameChapter][UniqueNoAnsNum].message3.empty())
		{
			message[2] = tblLookEaster[gameChapter][UniqueNoAnsNum].message3;
			messageByte[2] = tblLookEaster[gameChapter][UniqueNoAnsNum].message3.c_str();
		}
	}
	
	int msize[3];
	for (i = 0; i < 3; i++) { msize[i] = message[i].size(); }
	int CharBytes;

	// 異常特殊不正解
	if (gameChapter == 2 && flgAnswer == 3 && UniqueNoAnsNum > 0)
	{
		if (drawCnt <= 0)
		{
			drawMessage1.clear();
		}
		else if (msize[UniqueNoAnsCnt - 1] > drawCnt)
		{
			CharBytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &messageByte[UniqueNoAnsCnt - 1][drawCnt1]);
			drawCnt1 += CharBytes;
			drawMessage1 = message[UniqueNoAnsCnt - 1].substr(0, drawCnt1);
		}
		else if (msize[UniqueNoAnsCnt - 1] <= drawCnt)
		{
			drawMessage1 = message[UniqueNoAnsCnt - 1];
			drawCnt -= msize[UniqueNoAnsCnt - 1];
			allTalkCnt++;
		}
	}
	// 通常特殊不正解
	else
	{
		if (drawCnt <= 0)
		{
			drawMessage1.clear();
			drawMessage2.clear();
			lineflg = 0;
			drawCnt1 = 0;
			drawCnt2 = 0;
		}
		// 1行目
		else if (messageByte[0][drawCnt1] != '\0')
		{
			CharBytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &messageByte[0][drawCnt1]);
			drawCnt1 += CharBytes;
			drawMessage1 = message[0].substr(0, drawCnt1);
		}
		else
		{
			drawMessage1 = message[0];
			drawCnt -= msize[0];
			if (drawMessage2.empty()) { allTalkCnt++; }
			else { lineflg = 1; }
		}
		if (lineflg == 1)
		{
			// 2行目
			if (messageByte[1][drawCnt2] != '\0')
			{
				CharBytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &messageByte[1][drawCnt2]);
				drawCnt2 += CharBytes;
				drawMessage2 = message[1].substr(0, drawCnt2);
			}
			else
			{
				drawMessage2 = message[1];
				allTalkCnt++;
			}
		}
	}

	talkCnt++;
}

void SceneLook::Input()
{

}

void SceneLook::Process()
{
	switch (step)
	{
	case 0:
		// フェードイン開始
		ColorFadeIn(60);
		step++;
		break;
	case 1:
		if (IsColorFade() == 0)
		{
			// フェードイン終了
			step++;
		}
		break;
	case 2:
		// 通常処理

		int x, y;
		
		switch(flgLook)
		{
		case 0:
			if (abs(gPad.xinput_pad1.ThumbLX) > 10000 || abs(gPad.xinput_pad1.ThumbLY) > 10000)
			{
				flgLook = 1;
				spotlightSize = SCREEN_W;
			}
			break;
		case 1:
			if (spotlightSize > SPOTLIGHT_SIZE_MAX)
			{
				spotlightSize -= (SCREEN_W - SPOTLIGHT_SIZE_MAX) / 30;
			}
			else
			{
				flgLook = 2;
				spotlightSize = SPOTLIGHT_SIZE_MAX;
			}

			SetLightMap();
			// スポットライト
			SpotLight(vSpotLight.x, vSpotLight.y, spotlightSize, ALPHA_VALUE, 0);
			break;
		case 2:
			SetLightMap();

			if (flgAnswer == 1)		// 正解
			{
				// 正解にスポットライトの中心から画面が白くなっていく
				SpotLight(vSpotLight.x, vSpotLight.y, ansLightSize, 255, 1);
				ansLightSize += 40;
			}
			else
			{
				splMove(gPad.xinput_pad1);		// スポットライト移動
				splScale(gPad.xinput_pad1);

				// Bボタンを押すことで怪しい箇所を選択
				if (gPad.gTrg & PAD_INPUT_2)
				{
					CheckPoint(vSpotLight.x, vSpotLight.y);
					talkCnt = 0;
					allTalkCnt = 0;
				}

				// 特殊ゲームオーバー
				if (gameChapter == 2)
				{
					if (UniqueNoAnsCnt == 3 && allTalkCnt == 60)
					{
						PlaySoundMem(seLookDamage, DX_PLAYTYPE_BACK);	// se
						// エフェクト追加
						gEffect.AddEffect(1, SCREEN_W / 2, SCREEN_H / 2);
						gEffect.shakecnt = 30;
						gEffect.shakespead = 10;
						gHP = 0;
					}
					else if (UniqueNoAnsCnt > 3)
					{
						UniqueNoAnsCnt = 3;
						gHP = 0;
					}
				}

				if (flgAnswer != 0 && allTalkCnt == 60)
				{
					flgAnswer = 0;
					talkCnt = 0;
					allTalkCnt = 0;
				}
			}

			// スポットライト
			SpotLight(vSpotLight.x, vSpotLight.y, spotlightSize, ALPHA_VALUE, 0);

			// ライトマップのどのくらいが白くなっているかチェック
			lightCnt = 0;
			for (y = 0; y < LIGHTMAP_H; y++) {
				for (x = 0; x < LIGHTMAP_W; x++) {
					if (mapAnsLight[y * LIGHTMAP_W + x] >= 200) { lightCnt++; }
				}
			}
			if (lightCnt == LIGHTMAP_W * LIGHTMAP_H)
			{
				// 正解による画面遷移
				if (CheckSoundMem(seLookBGM)) { StopSoundMem(seLookBGM); }
				SceneBase* scene = new SceneTalk(gameChapter + 51);
				ChangeScene(scene);
			}

			// 画面揺らし処理
			gEffect.ProcessShake();
			// エフェクト処理
			gEffect.ProcessEffect();

			break;
		}
		// セリフ
		lookTalk();
		break;
	}

	// カラーマスクのフェードインアウト処理
	ColorFadeProcess();

	//体力ヌルヌル変更
	player.LifeProcess();

	//ゲームオーバー確認
	if (gHP <= 0) {
		//ゲームオーバー処理
		if (CheckSoundMem(seLookBGM)) { StopSoundMem(seLookBGM); }
		SceneBase* scene = new SceneGameover(100 + gameChapter);
		ChangeScene(scene);
	}
}

void SceneLook::Draw()
{
	int i, x, y, w, h;
	// 背景
	DrawGraph(gEffect.shakespead * gEffect.shake, 0, tblLookPoint[gameChapter].img, FALSE);

	// ライトマップを上から半透明描画
	int LightMapColor = GetColor(0, 0, 0);
	for (int y = 0; y < LIGHTMAP_H; y++) {
		for (int x = 0; x < LIGHTMAP_W; x++) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, mapLight[y * LIGHTMAP_W + x]);		// 半透明描画指定
			DrawBox(x * LIGHTSIZE_W, y * LIGHTSIZE_H, x * LIGHTSIZE_W + LIGHTSIZE_W, y * LIGHTSIZE_H + LIGHTSIZE_H, LightMapColor, TRUE);	// 黒
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明描画指定

	gEffect.DrawEffect();	// エフェクト描画

	// 正解
	int LightAnsMapColor = GetColor(255, 255, 200);		// 黄
	if (flgAnswer == 1)
	{
		for (int y = 0; y < LIGHTMAP_H; y++) {
			for (int x = 0; x < LIGHTMAP_W; x++) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, mapAnsLight[y * LIGHTMAP_W + x]);		// 半透明描画指定
				DrawBox(x * LIGHTSIZE_W, y * LIGHTSIZE_H, x * LIGHTSIZE_W + LIGHTSIZE_W, y * LIGHTSIZE_H + LIGHTSIZE_H, LightAnsMapColor, TRUE);	// 白
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明描画指定
	}

	DrawGraph(1530, 768, cgLookButtonUI, TRUE);
	ui.DrawTalkUI(reHP, 0); //UI作成

	// 文章
	int bt = 20;						//行間
	int massagefontsize = 62;			// セリフのフォントサイズ
	int namefontsize = 48;				// 名前のフォントサイズ
	int savefontsize = GetFontSize();	// 元のフォントサイズを保存

	// セリフ
	SetFontSize(massagefontsize);
	DrawFormatString(400, 850, GetColor(255, 255, 255), drawMessage1.c_str());
	DrawFormatString(400, 850 + massagefontsize + bt, GetColor(255, 255, 255), drawMessage2.c_str());
	SetFontSize(savefontsize);
	
	// カラーマスクのフェードインアウト描画
	ColorFadeDraw();
}
