#include	"data.h"
#include	"winmain.h"

// ---�R�c����o�[---
struct ENEMY gikai[ENEMY_MAX];

// ---��b�p�[�g�iSceneTalk�j---
// �A�j���[�V����
// 0�F��, 1�F��
int cg_anim[5][24];

// �G�t�F�N�g
int break_efffect[45];	// �u���C�N�i�J�ڎ��j

// ---�������ӏ����ɂރp�[�g�iSceneLook�j---
// �ɂރp�[�g�f�[�^�e�[�u��
struct LOOK_POINT tblLookPoint[] = {
	// chapter,	img,	initX, initY,				hittype,		x, y,			r			w, h,		lookingMessage,								trueMessage,	falseMessage
	// �͔ԍ�,	�摜,	�X�|�b�g���C�g�����ʒu,			�����蔻��^�C�v,	�����蔻��p���W,	�T�C�Y�i�~�j	�T�C�Y�i��`�j	�ɂݒ��̕���,									���𕶏�,			�s����
	{	0,		-1,		SCREEN_W / 2, SCREEN_H / 2,	0,				 853, 419,		123,		 -1,  -1,	"���E�̃i�C�t�ł͂Ȃ��Ƃ�����؋��������悤�B",	"�������I�I",	"���E�̃i�C�t�Ȃ�A���̖��O�������Ă���͂�......"},
	{	1,		-1,		SCREEN_W / 2, SCREEN_H / 2,	0,				 477, 318,		122,		 -1,  -1,	"�肪����ɂȂ���̂������悤�B",				"�������I�I",	"����͎肪����ɂ͂Ȃ�Ȃ�......"},
	{	2,		-1,		SCREEN_W / 2, SCREEN_H / 2,	0,				 844, 716,		108,		 -1,  -1,	"���J��[�������邽�߂̍ޗ��������悤�B",		"�������I�I",	"����ł͔[���������Ȃ����낤......"},
	{	3,		-1,		SCREEN_W / 2, SCREEN_H / 2,	1,				 510, 570,		 -1,		585, 125,	"�L����n���̏����m�F���悤�B",				"�������I�I",	"�m�F���ׂ����͂��ꂶ��Ȃ�......"},
	{	4,		-1,		SCREEN_W / 2, SCREEN_H / 2,	1,				1119, 606,		 -1,		282, 167,	"�莆�ƕM�Ղ���v���鐶�k�蒠�������悤�B",		"�������I�I",	"����͈Ⴄ�݂���......"},
	{	5,		-1,		960, 760,					0,				1020, 487,		123,		 -1,  -1,	"��؂����h���Ă����Ƃ����鍪���������悤�B",	"�������I�I",	"����͍����ɂȂ�Ȃ�......"},
};
int tblLPSize = sizeof(tblLookPoint) / sizeof(tblLookPoint[0]);		// �ɂރp�[�g�f�[�^�e�[�u���T�C�Y

// �ɂރp�[�g����s�����f�[�^�e�[�u��
struct LOOK_POINT_EASTER tblLookEaster[GIRON_MAX][6] = {
	// chapter,	hittype,		x, y,			r			w, h,		message1, message2, message3
	// �͔ԍ�,	�����蔻��^�C�v,	�����蔻��p���W,	�T�C�Y�i�~�j	�T�C�Y�i��`�j	�ɂݒ��̕���1, 2, 3
	{{	0,		1,				 986, 367,		  0,		460, 287,	"���E�ƌ��������v���o�̃i�C�t�B", "�܂��ݎ��ŁA�n�ɂ��݂��̖��O�𒤂��Ă���B"}},

	{{	1,		0,				1625, 333,		244,		 -1,  -1,	"�Ȃ��ޏ��͎E���ꂽ�̂��낤�H"},
	{	1,		0,				 293, 519,		135,		 -1,  -1,	"......�߂��Ɍ��o���̂�����̂������Ă���B"},
	{	1,		0,				 732, 444,		144,		 -1,  -1,	"......�߂��Ɍ��o���̂�����̂������Ă���B"},
	{	1,		0,				1182, 247,		165,		 -1,  -1,	"�[���h����i�C�t���ɁX�����B", "�����A�ڗ�������a���͂Ȃ��B"}},

	{{	2,		0,				 928,  35,		100,		 -1,  -1,	"������������......�ڂ����킹���Ȃ��B"},
	{	2,		0,				1030, 527,		134,		 -1,  -1,	"......���͂���ȂƂ���ɒ��ڂ��Ă���ꍇ�ł͂Ȃ��B", "...�������傫��......", "�����I�������낶�댩�Ă���I�ϑԁI"},
	{	2,		0,				 672, 560,		100,		 -1,  -1,	"......���͂���ȂƂ���ɒ��ڂ��Ă���ꍇ�ł͂Ȃ��B", "...�������傫��......", "�����I�������낶�댩�Ă���I�ϑԁI"}},
	
	{{	3,		1,				1119, 243,		 -1,		252, 381,	"�傫�����{���������I���B", "�Ȃ��|���`���𒅂Ă���̂��낤�B"},
	{	3,		1,				 512, 243,		 -1,		582, 113,	"�L����n��......", "���O�𕷂��΁A�N�ł��������Ǝv�����낤�B"},
	{	3,		1,				 512, 449,		 -1,		582, 113,	"�܂��P�N���Ȃ̂ɐR����ɏ������Ă���B", "�ǉƏo�g�̗ߏ�Ȃ̂��낤"}},

	{{	4,		1,				1119, 259,		 -1,		282, 167,	"���k��B�����Y�킾�B", "�����A�������̕M�ՂƂ͈�v���Ȃ����낤�B"},
	{	4,		1,				1119,  86,		 -1,		282, 167,	"�ӊO�Ɖ��炵���������B", "�����A�������̕M�ՂƂ͈�v���Ȃ����낤�B"},
	{	4,		1,				1119, 432,		 -1,		282, 167,	"�{���ʂ����Ȏ����B", "�����A�������̕M�ՂƂ͈�v���Ȃ����낤�B"},
	{	4,		1,				 520,  81,		 -1,		543, 427,	"�����̂��镶�����B", "���̕M�Ղƍ��v����l��T�����B"},
	{	4,		1,				 520, 512,		 -1,		543, 268,	"�u���O�̔閧���o�����v", "�L���삪�j�ł���Ƃ����閧���w���Ă���B"}},

	{{	5,		1,				 731, 864,		 -1,		490, 216,	"......�܂��܂��ˁB"},
	{	5,		1,				 846, 245,		 -1,		364, 120,	"�ዾ�̃t�`�܂ŗ΂Ƃ�......", "���������āA���b�L�[�J���[�Ȃ̂��낤���B"}}
};
//int tblEELSize = sizeof(tblLookEaster) / sizeof(tblLookEaster[0]);		// ����s�����f�[�^�e�[�u���T�C�Y

int cgLookButtonUI;		// �ɂރp�[�g�{�^��UI

// ---�U�؋c�_�p�[�g�iSceneGameMain�j---

int mvGiron_ikou;	// �U�؋c�_�ڍs�p����
int mvJishou_ikou;	// �����c�_�ڍs�p����

// �c�_�p�[�g�i�V�i���I�F�l�i�G��, �،��j
// 
// 1�����ځiGIRON_MAX�j�͋U�؋c�_��
// 2�����ځiENEMY_MAX�j�͐R�c����o�[�̎�ށi0�F��, 1�F��, 2�F��, 3�F��, 4�F�s���N�j
// 3�����ځiTESTIMONY_MAX�j��1�c�_�ł̐R�c����o�[��1�l�̔���
// �،�
int cgTestimony[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX];

// �l�i�G��
// ���[�h�p���
//		{imgPath[128],													allNum,	xNum, yNum,	xSize, ySize}
//		{�摜�p�X,														��������,	������(x,y),	�T�C�Y}
// ��
struct THOUGHTLESS_WORD redTW[GIRON_MAX][TW_NUM] = {
	// 1��ڂ̋U�؋c�_
	{
		{"res/thoughtless_words/giron1/red_thoughtless_words.png",		6 * 1,	6, 1,		200, 200},
	},
	// 2��ڂ̋U�؋c�_
	{
		{"res/thoughtless_words/giron2/barizougon_R1.png",				10 * 1,	10, 1,		200, 200},
		{"res/thoughtless_words/giron2/barizougon_R2.png",				6 * 1,	6, 1,		200, 200},
	},
	// 3��ڂ̋U�؋c�_
	{
		{"res/thoughtless_words/giron3/barizougon_R.png",				9 * 1,	9, 1,		200, 200},
	},
	// 4��ڂ̋U�؋c�_
	{
		{"res/thoughtless_words/giron4/barizougon_R1.png",				10 * 1,	10, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_R2.png",				10 * 1,	10, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_R3.png",				9 * 1,	9, 1,		200, 200},
	},
	// 5��ڂ̋U�؋c�_
	{
		{"res/thoughtless_words/giron5/barizougon_R1.png",				8 * 1,	8, 1,		200, 200},
		{"res/thoughtless_words/giron5/barizougon_R2.png",				10 * 1,	10, 1,		200, 200},
	},
	// 6��ڂ̋U�؋c�_
	{
		
	}
};
// ��
struct THOUGHTLESS_WORD greenTW[GIRON_MAX][TW_NUM] = {
	{

	},
	{
		{"res/thoughtless_words/giron2/barizougon_G1.png",				5 * 1,	5, 1,		200, 200},
		{"res/thoughtless_words/giron2/barizougon_G2.png",				9 * 1,	9, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron3/barizougon_G.png",				4 * 1,	4, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron4/barizougon_G1.png",				3 * 1,	3, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_G2.png",				8 * 1,	8, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_G3.png",				9 * 1,	9, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron5/barizougon_G1.png",				8 * 1,	8, 1,		200, 200},
	},
	{

	}
};
// ��
struct THOUGHTLESS_WORD yellowTW[GIRON_MAX][TW_NUM] = {
	{
		{"res/thoughtless_words/giron1/yellow_thoughtless_words.png",	11 * 1,	11, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron2/barizougon_Y1.png",				9 * 1,	9, 1,		200, 200},
		{"res/thoughtless_words/giron2/barizougon_Y2.png",				10 * 1,	10, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron3/barizougon_Y.png",				10 * 1,	10, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron4/barizougon_Y1.png",				9 * 1,	9, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_Y2.png",				10 * 1,	10, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_Y3.png",				6 * 1,	6, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron5/barizougon_Y1.png",				10 * 1,	10, 1,		200, 200},
		{"res/thoughtless_words/giron5/barizougon_Y2.png",				10 * 1,	10, 1,		200, 200},
	},
	{

	}
};
// ��
struct THOUGHTLESS_WORD blueTW[GIRON_MAX][TW_NUM] = {
	{
		{"res/thoughtless_words/giron1/blue_thoughtless_words.png",		8 * 1,	8, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron2/barizougon_B1.png",				9 * 1,	9, 1,		200, 200},
		{"res/thoughtless_words/giron2/barizougon_B2.png",				9 * 1,	9, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron3/barizougon_B.png",				4 * 1,	4, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron4/barizougon_B1.png",				10 * 1,	10, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_B2.png",				9 * 1,	9, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_B3.png",				7 * 1,	7, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron5/barizougon_B1.png",				10 * 1,	10, 1,		200, 200},
		{"res/thoughtless_words/giron5/barizougon_B2.png",				10 * 1,	10, 1,		200, 200},
	},
	{

	}
};
// �s���N
struct THOUGHTLESS_WORD pinkTW[GIRON_MAX][TW_NUM] = {
	{
		{"res/thoughtless_words/giron1/pink_thoughtless_words.png",		3 * 1,	3, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron2/barizougon_P1.png",				10 * 1,	10, 1,		200, 200},
		{"res/thoughtless_words/giron2/barizougon_P2.png",				10 * 1,	10, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron3/barizougon_P.png",				6 * 1,	6, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron4/barizougon_P1.png",				7 * 1,	7, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_P2.png",				6 * 1,	6, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_P3.png",				7 * 1,	7, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron5/barizougon_P1.png",				9 * 1,	9, 1,		200, 200},
		{"res/thoughtless_words/giron5/barizougon_P2.png",				7 * 1,	7, 1,		200, 200},
	},
	{

	}
};
// �Z�c�i�i�����c�_�j
struct THOUGHTLESS_WORD setsunaTW[GIRON_MAX][TW_NUM] = {
	{

	},
	{

	},
	{

	},
	{

	},
	{

	},
	{
		{"res/thoughtless_words/giron6/barizougon_S1.png",		5 * 1,	5, 1,		200, 200},
		{"res/thoughtless_words/giron6/barizougon_S2.png",		5 * 1,	5, 1,		200, 200},
		{"res/thoughtless_words/giron6/barizougon_S3.png",		4 * 1,	4, 1,		200, 200},
		{"res/thoughtless_words/giron6/barizougon_S4.png",		6 * 1,	6, 1,		200, 200},
		{"res/thoughtless_words/giron6/barizougon_S5.png",		6 * 1,	6, 1,		200, 200},
		{"res/thoughtless_words/giron6/barizougon_S6.png",		9 * 1,	9, 1,		200, 200},
		{"res/thoughtless_words/giron6/barizougon_S7.png",		3 * 1,	3, 1,		200, 200},
	}
};

// �摜
// 1�����ځiGIRON_MAX�j�͋U�؋c�_��
// 2�����ځiTW_NUM�j�͂��̋c�_�Ŏg�p����\���̎��
// 3�����ځiTW_LENGTH�j�́\�����̉摜
int cgRedThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// ��
int cgGreenThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// ��
int cgYellowThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// ��
int cgBlueThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// ��
int cgPinkThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// �s���N
int cgSetsunaThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];	// �Z�c�i�i�����c�_�j

int cgCounter;	//���_�ւ̑J��(�y��)
int cgCounter_x;	//���_�ւ̑J��(���{�^��)

int cgCutIn[30];	// �J�b�g�C��

int cgPlayguide;		//�������

int cgGironButtonUI;	// �c�_�p�[�g�{�^��UI
int cgHanronButtonUI;	// ���_�p�[�g�{�^��UI

// ���_�p�[�g
// 
// 1�����ځiGIRON_MAX�j�͋U�؋c�_��
// 2�����ځiENEMY_MAX�j�͐R�c����o�[�̎�ށi0�F��, 1�F��, 2�F��, 3�F��, 4�F�s���N�j
// 3�����ځiTESTIMONY_MAX�j��1�c�_�ł̔�����
int cgStockCard[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX];		// �擾�J�[�h�̉摜
int cgCounterCard[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX];		// ���_�J�[�h�̉摜

int cgReturnCard[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX];		// ���]�J�[�h�̉摜

// �����f�[�^�e�[�u��
struct ANSWER_CARD tblAnsCard[] = {
	// answerNum,		ansCardCnt,
	// �R�c��ψ��̔ԍ�, 	���Ԗڂ̔���,
	{	4,				0},
	{	2,				0},
	{	0,				0},
	{	-1,				-1},
	{	1,				1},
	{	2,				0},
};
int tblACSize = sizeof(tblAnsCard) / sizeof(tblAnsCard[0]);		// �����f�[�^�e�[�u���T�C�Y

// �擾�O�̎�D�z�u�̉摜�i���j�E�擾����̎�D�z�u�̉摜�i���j
int cgStockBrankCard;
int cgStockWhiteCard;

// ���Ԃ��p�摜
std::vector<int> cgTurnCard;

int deckMax[GIRON_MAX] = { 2, 3, 4, 0, 4, 5 };		// �e�U�؋c�_�ł̎�D�̏����\�ő吔

// ���_�p�[�g�������G�t�F�N�g
std::vector<int> cgEndEffect;			// �U�؋c�_
std::vector<int> cgJisyou_EndEffect;	// �����c�_

// �Ԉ�����ꍇ�̉摜
int cgHanronMiss;		// �U�؋c�_
int cgJishouHanronMiss;	// �����c�_

//
// SE�EBGM
//

// ---�^�C�g��---
int seTitleBGM;	// BGM

// ---��b�p�[�g---
int seBGM[5];	// BGM

// ---�������ӏ����ɂރp�[�g---
int seLookClear;	// 
int seLookDamage;	// �_���[�W
int seLookHazure;	// �n�Y��
int seLookSeikai;	// ����
int seLookBGM;		// BGM

// ---�U�؋c�_�p�[�g---
//����
int seDamage; //�_���[�W��
int seBGM1; //BGM1
int seBGM2; //BGM2
int seTestimonyBreak; //�،��K�[�h��
int seGetTestimony; //�،��擾��
int seCardGathering; //�،��ړ���
int seCardOpening; //�،��W�J��
int seCardSelecting; //�،��I��ύX
int seHazure; //�U�،��I����
int seCutin; //�J�b�g�C����
int seCardTurning; //�،����]��
int seHitTestimony; //�����،��q�b�g��
int seGard;//�\���K�[�h��
int seRedLaugh;		// �ԏ΂���
int seGreenLaugh;	// �Ώ΂���
int seYellowLaugh;	// ���΂���
int seBlueLaugh;	// �΂���
int sePinkLaugh;	// �s���N�΂���
int seSetsunaRough;	// �Z�c�i�΂���
int seSay;			//�Z���t��
int seCutinVoice;	// �J�b�g�C���{�C�X
int seDecide;		//���艹
int seCursor;		//�J�[�\����

// ---��������---
int jisyou_cgBg[72];
int se_choiceBGM[6];

// ---�N���W�b�g---
int _cgBgCredit;
int seCregit;

// ---�Q�[���I�[�o�[���---
int seGameOverBGM;	// BGM

//
// �G�t�F�N�g
//

int cgEffect[EFFECT_TYPE_MAX][16];	// �_���[�W�G�t�F�N�g

// �h��G�t�F�N�g
int LockEffect[5][11];

int gateReset[10];
