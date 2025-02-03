#include	"effect.h"
#include	"DxLib.h"
#include	"data.h"

Effect::Effect()
{
	shake = 0;
	shakecnt = 0;
	shakespead = 6;
	bgflg = 0;
}

Effect::~Effect()
{

}

// �G�t�F�N�g���̏�����
void Effect::InitEffect()
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		effect[i].use = 0;
	}
}

// �G�t�F�N�g�ǉ�
void Effect::AddEffect(int type, int x, int y)
{
	int i;
	// �g���Ă��Ȃ��z���T��
	for (i = 0; i < EFFECT_MAX; i++)
	{
		if (effect[i].use == 0)
		{
			// �g���Ă��Ȃ��B�������g��
			effect[i].use = 1;
			effect[i].x = x;
			effect[i].y = y;
			effect[i].animcnt = 0;
			effect[i].type = type;
			switch (type) {
			case 0:	// �_���[�W�G�t�F�N�g
				effect[i].animspeed = 6;
				effect[i].animnum = 8;
				effect[i].scale = 0.3;
				break;

			case 1:	// �_���[�W���o
				effect[i].animspeed = 5;
				effect[i].animnum = 9;
				effect[i].scale = 1.0;
				break;
			case 2:	// �K�[�h���J�[�h���o
				effect[i].animspeed = 2;
				effect[i].animnum = 10;
				effect[i].scale = 1.0;
				break;
			case 3:	// �K�[�h���_���[�W���o
				effect[i].animspeed = 3;
				effect[i].animnum = 8;
				effect[i].scale = 0.75;
				break;
			}

			break;
		}
	}
}

// �G�t�F�N�g����
void Effect::ProcessEffect()
{
	int i;
	for (i = 0; i < EFFECT_MAX; i++)
	{
		// ���̃G�t�F�N�g�͎g�p�����H
		if (effect[i].use == 1)
		{
			effect[i].animcnt++;

			if (effect[i].animcnt / effect[i].animspeed >= effect[i].animnum) {
				// �Ō�܂ōĐ����ꂽ�̂ŏI��
				effect[i].use = 0;
			}
		}
	}
}

// �G�t�F�N�g�`��
void Effect::DrawEffect()
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		// ���̃G�t�F�N�g�͎g�p�����H
		if (effect[i].use == 1)
		{

			DrawRotaGraph(effect[i].x, effect[i].y, effect[i].scale, 0.0f, cgEffect[effect[i].type][effect[i].animcnt / effect[i].animspeed], TRUE, 0);
		}
	}
}

void Effect::ProcessShake()
{
	int bgcnt = 3;
	if (shakecnt <= 0) {
		shake = 0;
	}
	else {
		shakecnt--;
		if (bgflg == 1) {
			shake++;
			if (shake > bgcnt) {
				bgflg = 2;
			}
		}
		else {
			shake--;
			if (shake < -bgcnt) {
				bgflg = 1;
			}
		}
	}
}
