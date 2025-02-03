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

// ��D�̒��S�ʒu�i�I�𒆂̃J�[�h�j
int Deck::GetCenterCard()
{
	int i = cards.size() / 2;
	return i;
}

// �J�[�h��X���W�̌v�Z��
float Deck::calcX(int i)
{
	float x = SCREEN_W / 2 + (i - GetCenterCard()) * 300;
	return x;
}

// �����،����������Ă��邩�̊m�F
bool Deck::CheckCard(int number, int ttmcnt)
{
	int i;
	for (i = 0; i < cards.size(); i++)
	{
		// �������Ă���J�[�h�̏،��Ҕԍ��Ɠ����ԍ������邩�ƁA�����،��ł��邩���`�F�b�N
		if (number == cards[i].num && ttmcnt == cards[i].testimonyCnt) { return TRUE; }
	}
	return FALSE;
}

// ��D�ǉ�
void Deck::GetCard(int number, int cgCard, int wordX, int wordY, float wordScale, int wordTtmCnt)
{
	struct CARD setCard = { number, cgCard , VGet(wordX, wordY, 0), wordScale, 1, wordTtmCnt};
	cards.push_back(setCard);		// �f�b�L�̍Ō���ɐV�K�擾�J�[�h��ǉ�
}

// �J�[�h�I��, ���𔻒�
void Deck::SelectCard()
{
	int i;

	switch (gPad.gTrg)
	{
	// ����1�����
	case PAD_INPUT_LEFT:
		cards.push_front(cards.back());
		cards.pop_back();
		PlaySoundMem(seCardSelecting, DX_PLAYTYPE_BACK, TRUE);
		turnCnt = 0;
		break;
	// �E�ɂP�����
	case PAD_INPUT_RIGHT:
		cards.push_back(cards.front());
		cards.pop_front();
		PlaySoundMem(seCardSelecting, DX_PLAYTYPE_BACK, TRUE);
		turnCnt = 0;
		break;
	}
	// �J�[�h����
	if (gPad.gTrg & PAD_INPUT_4)
	{
		if (cards[cards.size() / 2].num == answer_card
			&& cards[cards.size() / 2].testimonyCnt == tblAnsCard[gameChapter].ansCardCnt)		// ����
		{
			flg_ans = 1;
			flg_selectCard = 4;
			PlaySoundMem(seCutin, DX_PLAYTYPE_BACK, TRUE);
		}
		else												// �s����
		{
			flg_ans = 2;
			PlaySoundMem(seHazure, DX_PLAYTYPE_BACK, TRUE);
		}
	}
}

// �J�[�h�̗��Ԃ�
void Deck::TurnCard()
{
	int center = GetCenterCard();			// �I�𒆂̃J�[�h�ʒu
	int tCnt = (int)(turnCnt / 10) - 2;		// �摜�ύX�^�C�~���O
	if (tCnt >= 3)
	{
		cards[center].cg = cgReturnCard[gameChapter][cards[center].num][cards[center].testimonyCnt];	// �����̃J�[�h�摜
	}
	else if (tCnt > 0)
	{
		cards[center].cg = cgTurnCard[tCnt];		// ���Ԃ����̃J�[�h�摜
		if (tCnt == 2)
		{
			PlaySoundMem(seCardTurning, DX_PLAYTYPE_BACK, TRUE);
		}
	}
}

// �c�_���J�[�h���[�V����
void Deck::MotionCard(int flg_gf)
{
	int i;
	int count = 0;

	switch (flg_gf)
	{
	case 0:		// �U�؋c�_�p�[�g
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
	case 1:		// ���_�p�[�g
		// �J�[�h�W�J
		switch (flg_selectCard)
		{
		case 0:		// ��ʊO�Ɉړ�
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
		case 1:		// ��ʓ��Ɉړ�
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
		case 2:		// �W�J
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
		// �J�[�h�I��
		case 3:
			if (flg_ans == 0) { SelectCard(); }
			break;
		}
		break;
	case 2:
		break;
	}
}

// �Q�[���󋵂ɍ��킹�ăJ�[�h��ύX
void Deck::SetDrawCard(int flg_gf)
{
	int i;
	
	switch (flg_gf)
	{
	// �c�_�p�[�g
	case 0:
		for (i = 0; i < cards.size(); i++)
		{
			// �c�_�p�[�g
			cards[i].cg = cgStockCard[gameChapter][cards[i].num][cards[i].testimonyCnt];
			if (cards[i].motionCnt > 0)
			{
				cards[i].cg = cgStockWhiteCard;
			}
		}
		break;
	// ���_�p�[�g
	case 1:
		if (flg_selectCard == 0)
		{
			for (i = 0; i < cards.size(); i++)
			{
				// �c�_�p�[�g
				cards[i].cg = cgStockCard[gameChapter][cards[i].num][cards[i].testimonyCnt];
			}
		}
		else
		{
			for (i = 0; i < cards.size(); i++)
			{
				// �W�J�E�I��
				cards[i].cg = cgCounterCard[gameChapter][cards[i].num][cards[i].testimonyCnt];
			}

			if (flg_selectCard >= 3)
			{
				// �J�[�h�𗠕Ԃ�
				TurnCard();
				turnCnt++;
			}
		}
		break;
	// �t�B�j�b�V���i���ʁj
	case 2:
		
		break;
	}
}

// �J�[�h�\��
void Deck::DrawCard(int flg_gf)
{
	int i, j;
	int center = GetCenterCard();		// �I�𒆂̃J�[�h�ʒu
	switch (flg_gf)
	{
	case 0:		// �c�_�p�[�g
		for (i = 0; i < deckMax[gameChapter]; i++)
		{
			// ��D�̋󂫕\��
			// �،�����ɓ���Ă���ꍇ�A���̈ʒu�ɂ͕\�����Ȃ�
			if (i >= cards.size()) { DrawRotaGraph(DECK_CARD_X, DECK_CARD_Y - i * 116, 1.0f, 0.0f, cgStockBrankCard, TRUE, 0); }
		}
		for (j = 0; j < cards.size(); j++)
		{
			DrawRotaGraph(cards[j].pos.x, cards[j].pos.y, cards[j].scale, 0.0f, cards[j].cg, TRUE, 0);
		}
		break;
	case 1:		// ���_�p�[�g
		// �J�[�h�W�J��
		if (flg_selectCard < 3)
		{
			for (i = 0; i < cards.size(); i++)
			{
				DrawRotaGraph(cards[i].pos.x, cards[i].pos.y, cards[i].scale, 0.0f, cards[i].cg, TRUE, 0);
			}
		}
		// �I����
		else
		{
			for (i = 0; i < cards.size(); i++)
			{
				// �J�[�h�̈ʒu���Z�b�g
				if (cardMoveFlag != 1)
				{
					cards[i].pos.x = calcX(i);
					cards[center].pos.x = SCREEN_W / 2;
					cards[i].pos.y = 900;
					cards[i].scale = 1.0f;
				}
				// �I�𒆂̃J�[�h�͑傫���\��
				if (i == center)
				{
					DrawRotaGraph(cards[i].pos.x, cards[i].pos.y, cards[i].scale, 0.0f, cards[i].cg, TRUE, 0);
				}
				// �I�����Ă��Ȃ��J�[�h�͏����������\��
				else
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
					DrawRotaGraph(cards[i].pos.x, cards[i].pos.y, cards[i].scale - 0.3f, 0.0f, cards[i].cg, TRUE, 0);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
				}
			}
		}
		break;
	case 2:		// �I��
		// �s����
		if (flg_ans == 2)
		{
			for (i = 0; i < cards.size(); i++)
			{
				// �I�𒆂̃J�[�h�͑傫���\��
				if (i == center)
				{
					DrawRotaGraph(cards[i].pos.x, cards[i].pos.y, cards[i].scale, 0.0f, cards[i].cg, TRUE, 0);
				}
				// �I�����Ă��Ȃ��J�[�h�͏����������\��
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

// �J�[�h�̈ړ�
void Deck::MoveCard(int &flg_gf)
{
	int center = GetCenterCard();		//�I�𒆂̃J�[�h�ʒu
	cards[center].speed = CARD_SPEED;

	if (cards[center].scale >= 0)cards[center].scale -= DECREASE_SCALE;		//���X�ɏ������Ȃ�

	float rad;
	int target;

	//�J�[�h�̔�ԕ�����ݒ�
	for (int j = 0; j < ENEMY_MAX; j++)
	{
		if (j == cards[center].num)
		{
			rad = atan2(gikai[j].Y - cards[center].pos.y, gikai[j].X - cards[center].pos.x);
			target = j;
		}
	}

	// �p�x��radian����degree�ɕϊ�
	cards[center].direction = RadToDeg(rad);
	// ���݂̊p�x�Ńx�N�g�������
	VECTOR vDir = VGet(0, 0, 0);
	// �p�x��degree����radian�ɕϊ�
	float rad_2 = DegToRad(cards[center].direction);
	vDir.x = cos(rad_2);
	vDir.y = sin(rad_2);
	// ������x�N�g����P�ʃx�N�g���ɂ���
	VECTOR vUnit = VNorm(vDir);
	// �ړ��x�N�g�������
	VECTOR vMove = VScale(vUnit, cards[center].speed);
	// �ړ��x�N�g�����ʒu�ɉ��Z����
	cards[center].pos = VAdd(cards[center].pos, vMove);

	if ((cards[center].pos.x > gikai[target].X - ENEMY_HIT_X && cards[center].pos.x < gikai[target].X + ENEMY_HIT_X) && (cards[center].pos.y > gikai[target].Y - ENEMY_HIT_Y && cards[center].pos.y < gikai[target].Y + ENEMY_HIT_Y))
	{
		cardMoveFlag = 0; 		//�ړI�n�ɒ������瓮���Ȃ��Ȃ�
		flg_gf = 2;		//�V�[���؂�ւ�
	}
}

void Deck::SetCutInFlag(int cutInFlag)
{
	deckCutInflag = cutInFlag;
}
