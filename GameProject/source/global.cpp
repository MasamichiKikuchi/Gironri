#include	"DxLib.h"
#include	"global.h"
#include	<string>

Global::Global()
{
	// �ϐ�������
	
	// ---��b�p�[�g�iSceneTalk�j---
	// �A�j���[�V����
	for (int n = 0; n < 5; n++) {
		for (int i = 0; i < 24; i++) {
			cg_anim[n][i] = -1;
		}
	}
	
	// �G�t�F�N�g
	for (int i = 0; i < 45; i++)
	{
		break_efffect[i] = -1;
	}

	// ---�������ӏ����ɂރp�[�g---
	for (int i = 0; i < tblLPSize; i++)
	{
		tblLookPoint[i].img = -1;
	}

	// ---�U�؋c�_�p�[�g�iSceneGameMain�j---

	// �c�_�p�[�g
	// �،�
	for (int i = 0; i < GIRON_MAX; i++)
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			for (int k = 0; k < TESTIMONY_MAX; k++)
			{
				cgTestimony[i][j][k] = -1;
			}
		}
	}
	// �l�i�G��
	for (int i = 0; i < GIRON_MAX; i++)
	{
		for (int j = 0; j < TW_NUM; j++)
		{
			for (int k = 0; k < TW_LENGTH; k++)
			{
				cgRedThoughtlessWords[i][j][k] = -1;		// ��
				cgGreenThoughtlessWords[i][j][k] = -1;		// ��
				cgYellowThoughtlessWords[i][j][k] = -1;		// ��
				cgBlueThoughtlessWords[i][j][k] = -1;		// ��
				cgPinkThoughtlessWords[i][j][k] = -1;		// �s���N
				cgSetsunaThoughtlessWords[i][j][k] = -1;	// �Z�c�i�i�����c�_�j
			}
		}
	}

	// ���_�p�[�g
	for (int i = 0; i < GIRON_MAX; i++)
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			for (int k = 0; k < TESTIMONY_MAX; k++)
			{
				cgStockCard[i][j][k] = -1;
				cgCounterCard[i][j][k] = -1;
			}
		}
	}

	//
	// SE�EBGM
	//
	
	// ---�U�؋c�_�p�[�g---
	//����
	seDamage = -1;
	seBGM1 = -1;
	seBGM2 = -1;

	//
	// �G�t�F�N�g
	//
	
	// �h��G�t�F�N�g
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 11; j++) { LockEffect[i][j] = -1; }
	}
}

Global::~Global()
{
	// �f�[�^���
	
	// �R�c����o�[
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		DeleteGraph(gikai[i].cg);
	}

	// ---��b�p�[�g�iSceneTalk�j---
	// �A�j���[�V����
	for (int n = 0; n < 5; n++) {
		for (int i = 0; i < 24; i++) {
			DeleteGraph(cg_anim[n][i]);
		}
	}

	// �G�t�F�N�g
	for (int i = 0; i < 45; i++)
	{
		DeleteGraph(break_efffect[i]);
	}

	// ---�������ӏ����ɂރp�[�g�iSceneLook�j---
	for (int i = 0; i < tblLPSize; i++)
	{
		if (tblLookPoint[i].img != -1) { DeleteGraph(tblLookPoint[i].img); }
	}

	DeleteGraph(cgLookButtonUI);	// �ɂރp�[�g�{�^��UI

	// ---�U�؋c�_�p�[�g�iSceneGameMain�j---
	
	//�@����
	DeleteGraph(mvGiron_ikou);
	DeleteGraph(mvJishou_ikou);
	
	// �w�i
	for (int i = 0; i < CGBGANIM_PATTERN_MAX; i++) { DeleteGraph(_cgBg[i]); }
	for (int i = 0; i < CG_JISHOU_BGANIM_PATTERN_MAX; i++) { DeleteGraph(_cgJishouBg[i]); }

	//�J�b�g�C��
	for (int i = 0; i < 30; i++) { DeleteGraph(cgCutIn[i]); }

	// �c�_�p�[�g
	// �،�
	for (int i = 0; i < GIRON_MAX; i++)
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			for (int k = 0; k < TESTIMONY_MAX; k++) { DeleteGraph(cgTestimony[i][j][k]); }
		}
	}
	// �l�i�G��
	for (int i = 0; i < GIRON_MAX; i++)
	{
		for (int j = 0; j < TW_NUM; j++)
		{
			for (int k = 0; k < TW_LENGTH; k++)
			{
				DeleteGraph(cgRedThoughtlessWords[i][j][k]);		// ��
				DeleteGraph(cgGreenThoughtlessWords[i][j][k]);		// ��
				DeleteGraph(cgYellowThoughtlessWords[i][j][k]);		// ��
				DeleteGraph(cgBlueThoughtlessWords[i][j][k]);		// ��
				DeleteGraph(cgPinkThoughtlessWords[i][j][k]);		// �s���N
				DeleteGraph(cgSetsunaThoughtlessWords[i][j][k]);	// �Z�c�i�i�����c�_�j
			}
		}
	}

	DeleteGraph(cgCounter);		//���_�ւ̑J��(�y��)
	DeleteGraph(cgCounter_x);	//���_�ւ̑J��(���{�^��)

	DeleteGraph(cgPlayguide);	//�������

	// ���_�p�[�g
	for (int i = 0; i < GIRON_MAX; i++)
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			for (int k = 0; k < TESTIMONY_MAX; k++)
			{
				DeleteGraph(cgStockCard[i][j][k]);
				DeleteGraph(cgCounterCard[i][j][k]);
				DeleteGraph(cgReturnCard[i][j][k]);
			}
		}
	}

	// �擾�O�̎�D�z�u�̉摜�i���j�E�擾����̎�D�z�u�̉摜�i���j
	DeleteGraph(cgStockBrankCard);
	DeleteGraph(cgStockWhiteCard);

	// ���Ԃ��p�摜
	cgTurnCard.clear();

	// ���_�p�[�g�������G�t�F�N�g
	//�U�؋c�_
	for (int i = 0; i < ENDEFFECT_PATTERN_MAX; i++)
	{
		DeleteGraph(cgEndEffect[i]);
	}
	//�����c�_
	for (size_t i = 0; i < JISYOU_ENDEFFECT_PATTERN_MAX; i++)
	{
		DeleteGraph(cgJisyou_EndEffect[i]);
	}

	// �Ԉ�����ꍇ�̉摜
	//�U�؋c�_
	DeleteGraph(cgHanronMiss);
	DeleteGraph(cgJishouHanronMiss);

	//
	// SE�EBGM
	//
	
	// ---��b�p�[�g---
	for (int i = 0; i < 5; i++) {
		DeleteSoundMem(seBGM[i]);
	}

	// ---�������ӏ����ɂރp�[�g---
	DeleteSoundMem(seLookClear);
	DeleteSoundMem(seLookDamage);
	DeleteSoundMem(seLookHazure);
	DeleteSoundMem(seLookSeikai);

	// ---�U�؋c�_�p�[�g---
	//����
	DeleteSoundMem(seDamage);
	DeleteSoundMem(seBGM1);
	DeleteSoundMem(seBGM2);
	DeleteSoundMem(seTestimonyBreak);
	DeleteSoundMem(seGetTestimony);
	DeleteSoundMem(seCardGathering);
	DeleteSoundMem(seCardOpening);
	DeleteSoundMem(seCardSelecting);
	DeleteSoundMem(seHazure);
	DeleteSoundMem(seCutin);
	DeleteSoundMem(seCardTurning);
	DeleteSoundMem(seHitTestimony);
	DeleteSoundMem(seGard);
	DeleteSoundMem(seRedLaugh);
	DeleteSoundMem(seGreenLaugh);
	DeleteSoundMem(seYellowLaugh);
	DeleteSoundMem(seBlueLaugh);
	DeleteSoundMem(sePinkLaugh);
	DeleteSoundMem(seSetsunaRough);
	DeleteSoundMem(seSay);
	DeleteSoundMem(seCutinVoice);
	DeleteSoundMem(seTitleBGM);
	DeleteSoundMem(seDecide);
	DeleteSoundMem(seCursor);
	DeleteSoundMem(seGameOverBGM);

	// ---���������p�[�g---
	for (int i = 0; i < 6; i++) {
		DeleteSoundMem(se_choiceBGM[i]);
	}

	//
	// �G�t�F�N�g
	//
	
	// �_���[�W�G�t�F�N�g
	for (int i = 0; i < EFFECT_TYPE_MAX; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			DeleteGraph(cgEffect[i][j]);
		}
	}

	// �h��G�t�F�N�g
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 11; j++) { DeleteGraph(LockEffect[i][j]); }
	}

	// �h��񕜃G�t�F�N�g
	for (int i = 0; i < 9; i++)
	{
		DeleteGraph(gateReset[i]);
	}

	// �����������w�i
	for (int i = 0; i < 72; i++)
	{
		DeleteGraph(jisyou_cgBg[i]);
	}
}

// �ǂݍ���
void Global::Load()
{
	// �摜
	
	// �R�c����o�[�̐ݒ�
	gikai[0].cg = LoadGraph("res/enemy/red.png");
	gikai[1].cg = LoadGraph("res/enemy/green.png");
	gikai[2].cg = LoadGraph("res/enemy/yellow.png");
	gikai[3].cg = LoadGraph("res/enemy/blue.png");
	gikai[4].cg = LoadGraph("res/enemy/pink.png");
	
	// ---��b�p�[�g�iSceneTalk�j---
	// �A�j���[�V����
	// 0�F��, 1�F��
	for (int n = 0; n < 24; n++)
	{
		std::string img = "res/talkpart/kiiro/kiiro_anime";
		img += std::to_string(n + 1);
		img += ".png";
		cg_anim[0][n] = LoadGraph(img.c_str());
	}
	for (int n = 0; n < 24; n++)
	{
		std::string img = "res/talkpart/blue_anim/mizuiro_anime";
		img += std::to_string(n + 1);
		img += ".png";
		cg_anim[1][n] = LoadGraph(img.c_str());
	}
	for (int n = 0; n < 24; n++)
	{
		std::string img = "res/talkpart/midori/midori_anime";
		img += std::to_string(n + 1);
		img += ".png";
		cg_anim[2][n] = LoadGraph(img.c_str());
	}
	for (int n = 0; n < 24; n++)
	{
		std::string img = "res/talkpart/aka/aka_anime";
		img += std::to_string(n + 1);
		img += ".png";
		cg_anim[3][n] = LoadGraph(img.c_str());
	}
	for (int n = 0; n < 24; n++)
	{
		std::string img = "res/talkpart/pink/pink_anime";
		img += std::to_string(n + 1);
		img += ".png";
		cg_anim[4][n] = LoadGraph(img.c_str());
	}

	// �G�t�F�N�g
	for (int n = 0; n < 10; n++)
	{
		std::string img = "res/break/effect_break_00";
		img += std::to_string(n + 1);
		img += ".png";
		break_efffect[n] = LoadGraph(img.c_str());
	}

	for (int n = 10; n < 45; n++)
	{
		std::string img = "res/break/effect_break_0";
		img += std::to_string(n + 1);
		img += ".png";
		break_efffect[n] = LoadGraph(img.c_str());
	}

	// ---�������ӏ����ɂރp�[�g�iSceneLook�j---
	char lookImgPath[][128] = {
		"res/lookdata/part1.png",
		"res/lookdata/part2.png",
		"res/lookdata/part3.png",
		"res/lookdata/part4.png",
		"res/lookdata/part5.png",
		"res/lookdata/part6.png",
	};
	for (int i = 0; i < tblLPSize; i++)
	{
		//cgLook[i] = LoadGraph(lookImgPath[i]);
		tblLookPoint[i].img = LoadGraph(lookImgPath[i]);
	}

	cgLookButtonUI = LoadGraph("res/lookdata/UI_niramu.png");	// �ɂރp�[�g�{�^��UI

	// ---�U�؋c�_�p�[�g�iSceneGameMain�j---
	// �w�i�摜�̃��[�v�ł̃��[�h
	std::string img_path;
	// �U�؋c�_
	img_path = "res/cgBg_Gironpart_jpg/gironpart";
	anim.GetCG(img_path, 1, CGBGANIM_PATTERN_MAX, _cgBg);	// jpg�摜

	//�����c�_
	img_path = "res/cgBg_JisyouGironpart_jpg/girongame_setuna";
	anim.GetCG(img_path, 1, CG_JISHOU_BGANIM_PATTERN_MAX, _cgJishouBg);	// jpg�摜

	// �J�b�g�C��
	//efectType 0:�_���[�W�G�t�F�N�g 1:�_���[�W���o 2:�K�[�h���o
	for (int i = 0; i < 30; i++)
	{
		img_path = "res/effect/cutin/cutin" + std::to_string(i) + ".png";
		cgCutIn[i] = LoadGraph(img_path.c_str());
	}

	// �c�_�p�[�g
	// �،��̉摜�p�X�i��, ��, ��, ��, �s���N�̏��Ԃ�, �Ȃ��ꍇ�͋�""�Ɂj
	std::string testimonyPath[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX] = {
		// 1��ڂ̋U�؋c�_
		{
			{"res/cards/giron1/card_red.png",	""},	// ��
			{"",								""},	// ��
			{"",								""},	// ��
			{"",								""},	// ��
			{"res/cards/giron1/card_pink.png",	""}		// �s���N
		},
		// 2��ڂ̋U�؋c�_
		{
			{"res/cards/giron2/card_r.png",	""},
			{"",							""},
			{"res/cards/giron2/card_y.png",	""},
			{"",							""},
			{"res/cards/giron2/card_p.png",	""}
		},
		// 3��ڂ̋U�؋c�_
		{
			{"res/cards/giron3/card_r.png",	""},
			{"res/cards/giron3/card_g.png",	""},
			{"res/cards/giron3/card_y.png",	""},
			{"res/cards/giron3/card_b.png",	""},
			{"",							""}
		},
		// 4��ڂ̋U�؋c�_
		{
			{"",	""},
			{"",	""},
			{"",	""},
			{"",	""},
			{"",	""}
		},
		// 5��ڂ̋U�؋c�_
		{
			{"",														""},
			{"res/cards/giron5/card_g.png",	"res/cards/giron5/card_g2.png"},
			{"",														""},
			{"res/cards/giron5/card_b.png",								""},
			{"res/cards/giron5/card_p.png",								""}
		},
		// 6��ڂ̋U�؋c�_
		{
			{"res/cards/giron6/card_1.png",""},
			{"res/cards/giron6/card_2.png",""},
			{"res/cards/giron6/card_3.png",""},
			{"res/cards/giron6/card_4.png",""},
			{"res/cards/giron6/card_5.png",""}
		}
	};
	// �،��̉摜�̃��[�h
	for (int i = 0; i < GIRON_MAX; i++)
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			for (int k = 0; k < TESTIMONY_MAX; k++)
			{
				if (!testimonyPath[i][j][k].empty()) { cgTestimony[i][j][k] = LoadGraph(testimonyPath[i][j][k].c_str()); }
			}
		}
	}

	// �l�i�G��
	for (int i = 0; i < GIRON_MAX; i++)
	{
		for (int j = 0; j < TW_NUM; j++)
		{
			// ��
			LoadDivGraph(redTW[i][j].imgPath, redTW[i][j].allNum, redTW[i][j].xNum, redTW[i][j].yNum,
				redTW[i][j].xSize, redTW[i][j].ySize, cgRedThoughtlessWords[i][j]);
			// ��
			LoadDivGraph(greenTW[i][j].imgPath, greenTW[i][j].allNum, greenTW[i][j].xNum, greenTW[i][j].yNum,
				greenTW[i][j].xSize, greenTW[i][j].ySize, cgGreenThoughtlessWords[i][j]);
			// ��
			LoadDivGraph(yellowTW[i][j].imgPath, yellowTW[i][j].allNum, yellowTW[i][j].xNum, yellowTW[i][j].yNum,
				yellowTW[i][j].xSize, yellowTW[i][j].ySize, cgYellowThoughtlessWords[i][j]);
			// ��
			LoadDivGraph(blueTW[i][j].imgPath, blueTW[i][j].allNum, blueTW[i][j].xNum, blueTW[i][j].yNum,
				blueTW[i][j].xSize, blueTW[i][j].ySize, cgBlueThoughtlessWords[i][j]);
			// �s���N
			LoadDivGraph(pinkTW[i][j].imgPath, pinkTW[i][j].allNum, pinkTW[i][j].xNum, pinkTW[i][j].yNum,
				pinkTW[i][j].xSize, pinkTW[i][j].ySize, cgPinkThoughtlessWords[i][j]);
			// �Z�c�i�i�����c�_�j
			LoadDivGraph(setsunaTW[i][j].imgPath, setsunaTW[i][j].allNum, setsunaTW[i][j].xNum, setsunaTW[i][j].yNum,
				setsunaTW[i][j].xSize, setsunaTW[i][j].ySize, cgSetsunaThoughtlessWords[i][j]);
		}
	}

	cgCounter = LoadGraph("res/Scenegamemain/cutin_counter.png");		//���_�ւ̑J��(�y��)
	cgCounter_x = LoadGraph("res/Scenegamemain/cutin_counter_X.png");	//���_�ւ̑J��(���{�^��)

	cgPlayguide = LoadGraph("res/Scenegamemain/guide_play.png");		//�������

	cgGironButtonUI = LoadGraph("res/Scenegamemain/UI_guard.png");		// �c�_�p�[�g�{�^��UI
	cgHanronButtonUI = LoadGraph("res/Scenegamemain/UI_hanron.png");	// ���_�p�[�g�{�^��UI

	// ���_�p�[�g
	// �擾�J�[�h�̉摜�p�X�i��, ��, ��, ��, �s���N�̏��Ԃ�, �Ȃ��ꍇ�͋�""�Ɂj
	std::string stockCardPath[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX] = {
		// 1��ڂ̋U�؋c�_
		{
			{"res/cards/giron1/stockcard_red.png",	""},	// ��
			{"",									""},	// ��
			{"",									""},	// ��
			{"",									""},	// ��
			{"res/cards/giron1/stockcard_pink.png",	""}		// �s���N
		},
		// 2��ڂ̋U�؋c�_
		{
			{"res/cards/giron2/stock_card_r.png",	""},
			{"",									""},
			{"res/cards/giron2/stock_card_y.png",	""},
			{"",									""},
			{"res/cards/giron2/stock_card_p.png",	""}
		},
		// 3��ڂ̋U�؋c�_
		{
			{"res/cards/giron3/stock_card_r.png",	""},
			{"res/cards/giron3/stock_card_g.png",	""},
			{"res/cards/giron3/stock_card_y.png",	""},
			{"res/cards/giron3/stock_card_b.png",	""},
			{"",									""}
		},
		// 4��ڂ̋U�؋c�_
		{
			{"",									""},
			{"",									""},
			{"",									""},
			{"",									""},
			{"",									""}
		},
		// 5��ڂ̋U�؋c�_
		{
			{"",																	""},
			{"res/cards/giron5/stock_card_g.png",	"res/cards/giron5/stock_card_g2.png"},
			{"",																	""},
			{"res/cards/giron5/stock_card_b.png",									""},
			{"res/cards/giron5/stock_card_p.png",									""}
		},
		// 6��ڂ̋U�؋c�_
		{
			{"res/cards/giron6/stock_card_1.png",	""},
			{"res/cards/giron6/stock_card_2.png",	""},
			{"res/cards/giron6/stock_card_3.png",	""},
			{"res/cards/giron6/stock_card_4.png",	""},
			{"res/cards/giron6/stock_card_5.png",	""}
		}
	};
	// ���_�J�[�h�̉摜�p�X�i��, ��, ��, ��, �s���N�̏��Ԃ�, �Ȃ��ꍇ�͋�""�Ɂj
	std::string counterCardPath[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX] = {
		// 1��ڂ̋U�؋c�_
		{
			{"res/cards/giron1/countercard_red.png",	""},	// ��
			{"",										""},	// ��
			{"",										""},	// ��
			{"",										""},	// ��
			{"res/cards/giron1/countercard_pink.png",	""}		// �s���N
		},
		// 2��ڂ̋U�؋c�_
		{
			{"res/cards/giron2/counter_card_r.png",	""},
			{"",									""},
			{"res/cards/giron2/counter_card_y.png",	""},
			{"",									""},
			{"res/cards/giron2/counter_card_p.png",	""}
		},
		// 3��ڂ̋U�؋c�_
		{
			{"res/cards/giron3/counter_card_r.png",	""},
			{"res/cards/giron3/counter_card_g.png",	""},
			{"res/cards/giron3/counter_card_y.png",	""},
			{"res/cards/giron3/counter_card_b.png",	""},
			{"",									""}
		},
		// 4��ڂ̋U�؋c�_
		{
			{"",									""},
			{"",									""},
			{"",									""},
			{"",									""},
			{"",									""}
		},
		// 5��ڂ̋U�؋c�_
		{
			{"",																		""},
			{"res/cards/giron5/counter_card_g.png",	"res/cards/giron5/counter_card_g2.png"},
			{"",																		""},
			{"res/cards/giron5/counter_card_b.png",										""},
			{"res/cards/giron5/counter_card_p.png",										""}
		},
		// 6��ڂ̋U�؋c�_
		{
			{"res/cards/giron6/counter_card_1.png",	""},
			{"res/cards/giron6/counter_card_2.png",	""},
			{"res/cards/giron6/counter_card_3.png",	""},
			{"res/cards/giron6/counter_card_4.png",	""},
			{"res/cards/giron6/counter_card_5.png",	""}
		}
	};
	// ���]�J�[�h�̉摜�p�X�i��, ��, ��, ��, �s���N�̏��Ԃ�, �Ȃ��ꍇ�͋�""�Ɂj
	std::string returnCardPath[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX] = {
		// 1��ڂ̋U�؋c�_
		{
			{"res/cards/giron1/countercard_return_red.png",		""},	// ��
			{"",												""},	// ��
			{"",												""},	// ��
			{"",												""},	// ��
			{"res/cards/giron1/countercard_return_pink.png",	""}		// �s���N
		},
		// 2��ڂ̋U�؋c�_
		{
			{"res/cards/giron2/return_card_r.png",	""},
			{"",									""},
			{"res/cards/giron2/return_card_y.png",	""},
			{"",									""},
			{"res/cards/giron2/return_card_p.png",	""}
		},
		// 3��ڂ̋U�؋c�_
		{
			{"res/cards/giron3/return_card_r.png",	""},
			{"res/cards/giron3/return_card_g.png",	""},
			{"res/cards/giron3/return_card_y.png",	""},
			{"res/cards/giron3/return_card_b.png",	""},
			{"",									""}
		},
		// 4��ڂ̋U�؋c�_
		{
			{"",									""},
			{"",									""},
			{"",									""},
			{"",									""},
			{"",									""}
		},
		// 5��ڂ̋U�؋c�_
		{
			{"",																		""},
			{"res/cards/giron5/return_card_g.png",	"res/cards/giron5/return_card_g2.png"},
			{"",																		""},
			{"res/cards/giron5/return_card_b.png",										""},
			{"res/cards/giron5/return_card_p.png",										""}
		},
		// 6��ڂ̋U�؋c�_
		{
			{"res/cards/giron6/return_card_1.png",	""},
			{"res/cards/giron6/return_card_2.png",	""},
			{"res/cards/giron6/return_card_3.png",	""},
			{"res/cards/giron6/return_card_4.png",	""},
			{"res/cards/giron6/return_card_5.png",	""}
		}
	};
	// �擾�E���_�E���]�J�[�h�摜�̃��[�h
	for (int i = 0; i < GIRON_MAX; i++)
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			for (int k = 0; k < TESTIMONY_MAX; k++)
			{
				if (!stockCardPath[i][j][k].empty()) { cgStockCard[i][j][k] = LoadGraph(stockCardPath[i][j][k].c_str()); }
				if (!counterCardPath[i][j][k].empty()) { cgCounterCard[i][j][k] = LoadGraph(counterCardPath[i][j][k].c_str()); }
				if (!returnCardPath[i][j][k].empty()) { cgReturnCard[i][j][k] = LoadGraph(returnCardPath[i][j][k].c_str()); }
			}
		}
	}

	// �擾�O�̎�D�z�u�̉摜�i���j�E�擾����̎�D�z�u�̉摜�i���j
	cgStockBrankCard = LoadGraph("res/cards/stock/stockcard_brank.png");
	cgStockWhiteCard = LoadGraph("res/cards/stock/stockcard_white.png");

	// ���Ԃ��p�摜
	img_path = "res/cards/counter/card_turn";
	anim.GetCG(img_path, 0, TURN_CARD_MAX, cgTurnCard);	// png�摜

	// ���_�p�[�g�������G�t�F�N�g
	// �U�؋c�_
	img_path = "res/Gironpartover/gironover";
	anim.GetCG(img_path, 1, ENDEFFECT_PATTERN_MAX, cgEndEffect);	// jpg�摜
	//�����c�_
	img_path = "res/Jisyoupartover/jisyou";
	anim.GetCG(img_path, 1, JISYOU_ENDEFFECT_PATTERN_MAX, cgJisyou_EndEffect);	// jpg�摜
	
	// �Ԉ�����ꍇ�̉摜
	//�U�؋c�_
	cgHanronMiss = LoadGraph("res/Scenegamemain/gisyou_miss_text.png");
	//�����c�_
	cgJishouHanronMiss = LoadGraph("res/Scenegamemain/jisyou_miss_text.png");

	//
	// SE�EBGM
	//
	// ---�^�C�g��---
	seTitleBGM = LoadSoundMem("res/sound/title_fo.mp3");

	// ---��b�p�[�g---
	seBGM[0] = LoadSoundMem("res/sound/kaiwa.mp3");
	seBGM[1] = LoadSoundMem("res/sound/kaiwa_bad.mp3");
	seBGM[2] = LoadSoundMem("res/sound/kaiwa_gironclear_fo.mp3");
	seBGM[3] = LoadSoundMem("res/sound/kaiwa_true.mp3");

	// ---�������ӏ����ɂރp�[�g---
	seLookClear = LoadSoundMem("res/se/seLook/se_clear.mp3");
	seLookDamage = LoadSoundMem("res/se/seLook/se_damage.mp3");
	seLookHazure = LoadSoundMem("res/se/seLook/se_hazure.mp3");
	seLookSeikai = LoadSoundMem("res/se/seLook/se_seikai.mp3");
	seLookBGM = LoadSoundMem("res/se/seLook/look.mp3");

	// ---�U�؋c�_�p�[�g---
	//����
	seDamage = LoadSoundMem("res/sound/damage.mp3");
	seBGM1 = LoadSoundMem("res/sound/giron_bgm_oneloop.mp3");
	seBGM2 = LoadSoundMem("res/sound/gisyou-giron_cut.mp3");
	seTestimonyBreak = LoadSoundMem("res/se/se_testimony_break2.mp3");
	seGetTestimony = LoadSoundMem("res/se/se_get_testimony_db.mp3");
	seCardGathering = LoadSoundMem("res/se/se_card_gathering.mp3");
	seCardOpening = LoadSoundMem("res/se/se_card_opening.mp3");
	seCardSelecting = LoadSoundMem("res/se/se_card_selecting.mp3");
	seHazure = LoadSoundMem("res/se/se_hazure2.mp3");
	seCutin = LoadSoundMem("res/se/se_cutin.mp3");
	seCardTurning = LoadSoundMem("res/se/se_card_turning_dbcut.mp3"); //�،����]��
	seHitTestimony = LoadSoundMem("res/se/se_hit_testimony2.mp3"); //�����،��q�b�g��
	seGard = LoadSoundMem("res/se/se_gard.mp3");
	seRedLaugh = LoadSoundMem("res/voice/r_1.wav");
	seGreenLaugh = LoadSoundMem("res/voice/g_1.wav");
	seYellowLaugh = LoadSoundMem("res/voice/y_1.wav");
	seBlueLaugh = LoadSoundMem("res/voice/b_1.wav");
	sePinkLaugh = LoadSoundMem("res/voice/p_1.wav");
	seSetsunaRough = LoadSoundMem("res/voice/s_22.wav");
	seSay = LoadSoundMem("res/sound/sound.mp3");
	seCutinVoice = LoadSoundMem("res/voice/s_13_2.wav");
	seDecide = LoadSoundMem("res/se/se_seikai.mp3");
	seCursor = LoadSoundMem("res/se/se_cursor_move.mp3");

	// ---���������p�[�g---
	for (int n = 0; n < 72; n++)
	{
		std::string img = "res/JishouChoicepart/jisyou_BG/zisyou_BG" + std::to_string(n) + ".jpg";
		jisyou_cgBg[n] = LoadGraph(img.c_str());
	}
	se_choiceBGM[0] = LoadSoundMem("res/sound/jisyouBGM/maou_bgm_piano17_q1.mp3");
	se_choiceBGM[1] = LoadSoundMem("res/sound/jisyouBGM/maou_bgm_piano17_q2.mp3");
	se_choiceBGM[2] = LoadSoundMem("res/sound/jisyouBGM/maou_bgm_piano17_q3.mp3");
	se_choiceBGM[3] = LoadSoundMem("res/sound/jisyouBGM/maou_bgm_piano17_q4.mp3");
	se_choiceBGM[4] = LoadSoundMem("res/sound/jisyouBGM/maou_bgm_piano17_q5.mp3");
	se_choiceBGM[5] = LoadSoundMem("res/sound/jisyouBGM/maou_bgm_piano17_q6.mp3");


	// ---�N���W�b�g---
	_cgBgCredit = LoadGraph("res/CG_credit.png");
	seCregit = LoadSoundMem("res/sound/endcredit.mp3");

	// ---�Q�[���I�[�o�[���---
	seGameOverBGM = LoadSoundMem("res/sound/gameover_timeshift.mp3");;	// BGM;

	//���ʒ���
	ChangeVolumeSoundMem(255 * 70 / 100, sePinkLaugh);
	ChangeVolumeSoundMem(255 * 60 / 100, seCursor);
	ChangeVolumeSoundMem(255 * 75 / 100, seDecide);
	ChangeVolumeSoundMem(255 * 70 / 100, seCardTurning);

	//����
	mvGiron_ikou = LoadGraph("res/movie/haikei_ikou.mp4");
	mvJishou_ikou = LoadGraph("res/movie/jishou_seni.mp4");

	//
	// �G�t�F�N�g
	//

	// �_���[�W�G�t�F�N�g
	std::string effect_path;
	//efectType 0:�_���[�W�G�t�F�N�g 1:�_���[�W���o 2:�K�[�h���o
	for (int efectType = 0; efectType < EFFECT_TYPE_MAX; efectType++)
	{
		switch (efectType)
		{
		case 0:
			for (int i = 0; i < DAMAGE_EFFECT_ANINAM_NAM; i++)
			{
				effect_path = "res/effect/damage_effect_000" + std::to_string(i) + ".png";
				cgEffect[efectType][i] = LoadGraph(effect_path.c_str());
			}
			break;
		case 1:

			for (int i = 0; i < DAMAGE_DIRECTION_ANINAM_NAM; i++)
			{

				effect_path = "res/effect/effect_damage_0" + std::to_string(i) + ".png";
				cgEffect[efectType][i] = LoadGraph(effect_path.c_str());
				if (i == DAMAGE_DIRECTION_ANINAM_NAM - 1)
				{
					for (int ii = 0; ii < DAMAGE_DIRECTION_ANINAM_NAM; ii++)
					{
						effect_path = "res/effect/effect_damage_0" + std::to_string(i - ii) + ".png";
						cgEffect[efectType][i + ii] = LoadGraph(effect_path.c_str());
					}
				}
			}
			break;
		case 2:
			for (int i = 0; i < 10; i++)
			{
				effect_path = "res/card_break/10" + std::to_string(i) + ".png";
				cgEffect[efectType][i] = LoadGraph(effect_path.c_str());
			}
			break;
		case 3:
			for (int i = 0; i < 8; i++)
			{
				LoadDivGraph("res/effect/hit_effect.png", 5, 5, 1, 250, 250, cgEffect[efectType]);
			}
			break;
		}
	}

	// �h��G�t�F�N�g
	for (int n = 0; n < 10; n++)
	{
		std::string img = "res/gate/gate/gate" + std::to_string(n) + ".png";
		LockEffect[0][n + 1] = LoadGraph(img.c_str());
	}
	for (int p = 1; p < 5; p++) {
		for (int n = 0; n < 10; n++)
		{
			std::string img = "res/gate/gate_breaking_00" + std::to_string(p) + "/gate" + std::to_string(n) + ".png";
			LockEffect[p][n + 1] = LoadGraph(img.c_str());
		}
	}

	// �h��񕜃G�t�F�N�g
	for (int i = 0; i < 9; i++)
	{
		effect_path = "res/gate/reset/gate_reset_" + std::to_string(i) + ".png";
		gateReset[i] = LoadGraph(effect_path.c_str());
	}
}

// �ǂݍ��݂��I�����Ă���1�A�܂��Ȃ�0
int Global::IsLoadFinish()
{
	if (GetASyncLoadNum() > 0)
	{
		return 0;	// �ǂݍ��݂��܂��r��
	}
	return 1;		// �ǂݍ��ݏI�����Ă�
}
