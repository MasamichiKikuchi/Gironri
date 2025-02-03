#pragma once

#include	"DxLib.h"
#include	<iostream>
#include	<string>
#include	<vector>

// ---�R�c����o�[---
#define	ENEMY_MAX		(5)		// �G�ő�l��
#define	GIRON_MAX		(6)		// �U�؋c�_�ő��
#define	TESTIMONY_MAX	(2)		// 1�c�_�̏،���
#define	TW_NUM			(7)		// �P�c�_�ł̂P�L�����̖\���ő吔
#define	TW_LENGTH		(11)	// �\���ő啶����

struct ENEMY {
	int cg;			// �G�摜
	int X;			// �GX���W
	int Y;			// �GY���W
};
extern struct ENEMY gikai[ENEMY_MAX];	// �G�،��Ҕԍ��i0�F��, 1�F��, 2�F��, 3�F��, 4�F�s���N�j

// ---��b�p�[�g�iSceneTalk�j---
// �A�j���[�V����
// 0�F��, 1�F��
extern int cg_anim[5][24];

// �G�t�F�N�g
extern int break_efffect[45];	// �u���C�N�i�J�ڎ��j

// ---�������ӏ����ɂރp�[�g�iSceneLook�j---
// �ɂމӏ��̍\����
struct LOOK_POINT {
	int chapter;				// �͔ԍ�
	int img;					// �摜
	float initX, initY;			// �X�|�b�g���C�g�����ʒu
	int hittype;				// �����蔻��͈̔͌`��^�C�v�i0�F�~, 1�F��`�j
	int x, y;					// �����蔻��p���W
	int r;						// �����蔻��p�T�C�Y�i�~�F���a�j
	int w, h;					// �����蔻��p�T�C�Y�i��`�F���c�j

	std::string lookingMessage;	// �ɂݒ��̕���
	std::string trueMessage;	// ���𕶏�
	std::string falseMessage;	// �s���𕶏�
};
extern struct LOOK_POINT tblLookPoint[];	// �ɂރp�[�g�f�[�^�e�[�u��
extern int tblLPSize;						// �ɂރp�[�g�f�[�^�e�[�u���T�C�Y

// ����s�����̍\����
struct LOOK_POINT_EASTER {
	int chapter;				// �͔ԍ�
	int hittype;				// �����蔻��͈̔͌`��^�C�v�i0�F�~, 1�F��`�j
	int x, y;					// �����蔻��p���W
	int r;						// �����蔻��p�T�C�Y�i�~�F���a�j
	int w, h;					// �����蔻��p�T�C�Y�i��`�F���c�j

	std::string message1;	// ����1
	std::string message2;	// ����2
	std::string message3;	// ����3
};
extern struct LOOK_POINT_EASTER tblLookEaster[GIRON_MAX][6];	// �ɂރp�[�g�C�[�X�^�[�G�b�O�f�[�^�e�[�u��
//extern int tblEELSize;										// ����s�����f�[�^�e�[�u���T�C�Y

extern int cgLookButtonUI;		// �ɂރp�[�g�{�^��UI

// ---�U�؋c�_�p�[�g�iSceneGameMain�j---

// ����
extern int mvGiron_ikou;	// �U�؋c�_�ڍs�p����
extern int mvJishou_ikou;	// �����c�_�ڍs�p����

// �c�_�p�[�g�i�V�i���I�F�l�i�G��, �،��j
// �،��i1�����ځF�e�c�_, �Q�����ځF�R�c����o�[, �R�����ځF�P�c�_�ł̏،����j
extern int cgTestimony[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX];
// �l�i�G��
// ���[�h�p���
struct THOUGHTLESS_WORD {
	char imgPath[128];		// �摜�p�X
	int allNum;				// �摜�̕�������
	int xNum, yNum;			// ���ix�j�����ɑ΂��镪����, �c�iy�j�����ɑ΂���ɑ΂��镪����
	int xSize, ySize;		// �������ꂽ�摜1�̑傫��
};
extern struct THOUGHTLESS_WORD redTW[GIRON_MAX][TW_NUM];		// ��
extern struct THOUGHTLESS_WORD greenTW[GIRON_MAX][TW_NUM];		// ��
extern struct THOUGHTLESS_WORD yellowTW[GIRON_MAX][TW_NUM];		// ��
extern struct THOUGHTLESS_WORD blueTW[GIRON_MAX][TW_NUM];		// ��
extern struct THOUGHTLESS_WORD pinkTW[GIRON_MAX][TW_NUM];		// �s���N
extern struct THOUGHTLESS_WORD setsunaTW[GIRON_MAX][TW_NUM];	// �Z�c�i�i�����c�_�j
// �摜
extern int cgRedThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];			// ��
extern int cgGreenThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// ��
extern int cgYellowThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// ��
extern int cgBlueThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// ��
extern int cgPinkThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// �s���N
extern int cgSetsunaThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// �Z�c�i�i�����c�_�j

extern int cgCounter;	//���_�ւ̑J��(�y��)
extern int cgCounter_x;	//���_�ւ̑J��(���{�^��)

extern int cgCutIn[30];		//�J�b�g�C��
extern int cgPlayguide;		//�������
extern int cgGironButtonUI;		// �c�_�p�[�g�{�^��UI
extern int cgHanronButtonUI;	// ���_�p�[�g�{�^��UI

// ���_�p�[�g
extern int cgStockCard[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX];		// �擾�J�[�h�̉摜�i1�����ځF�e�c�_, �Q�����ځF�R�c����o�[, �R�����ځF�P�c�_�ł̏،����j
extern int cgCounterCard[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX];		// ���_�J�[�h�̉摜�i1�����ځF�e�c�_, �Q�����ځF�R�c����o�[, �R�����ځF�P�c�_�ł̏،����j

extern int cgReturnCard[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX];		// ���]�J�[�h�̉摜�i1�����ځF�e�c�_, �Q�����ځF�R�c����o�[, �R�����ځF�P�c�_�ł̏،����j

struct ANSWER_CARD {
	int answerNum;		// �����̃J�[�h���΂��R�c��ψ��̔ԍ�
	int ansCardCnt;		// �،��҂̉��Ԗڂ̔�����
};
extern struct ANSWER_CARD tblAnsCard[];		// �����f�[�^�e�[�u��
extern int tblACSize;						// �����f�[�^�e�[�u���T�C�Y

// �擾�O�̎�D�z�u�̉摜�i���j�E�擾����̎�D�z�u�̉摜�i���j
extern int cgStockBrankCard;
extern int cgStockWhiteCard;

// ���Ԃ��p�摜
#define	TURN_CARD_MAX	(3)	// ���Ԃ��p�摜�̍ő喇��
extern std::vector<int> cgTurnCard;

extern int deckMax[GIRON_MAX];		// �e�U�؋c�_�ł̎�D�̏����\�ő吔

// ���_�p�[�g�������G�t�F�N�g
#define ENDEFFECT_PATTERN_MAX			(72)	// �U�؋c�_
#define JISYOU_ENDEFFECT_PATTERN_MAX	(72)	// �����c�_

extern std::vector<int> cgEndEffect;		// �U�؋c�_
extern std::vector<int> cgJisyou_EndEffect;	// �����c�_

// �Ԉ�����ꍇ�̉摜
extern int cgHanronMiss;		// �U�؋c�_
extern int cgJishouHanronMiss;	// �����c�_

//
// SE�EBGM
//
// ---�^�C�g�����---
extern int seTitleBGM;	// BGM

// ---��b�p�[�g---
extern int seBGM[5];	// BGM

// ---�������ӏ����ɂރp�[�g---
extern int seLookClear;		// 
extern int seLookDamage;	// �_���[�W
extern int seLookHazure;	// �n�Y��
extern int seLookSeikai;	// ����
extern int seLookBGM;		// BGM

// ---�U�؋c�_�p�[�g---
//����
extern int seDamage; //�_���[�W��
extern int seBGM1; //BGM1
extern int seBGM2; //BGM2
extern int seTestimonyBreak; //�،��K�[�h��
extern int seGetTestimony; //�،��擾��
extern int seCardGathering; //�،��ړ���
extern int seCardOpening; //�،��W�J��
extern int seCardSelecting; //�،��I��ύX
extern int seHazure; //�U�،��I����
extern int seCutin; //�J�b�g�C����
extern int seCardTurning; //�،����]��
extern int seHitTestimony; //�����،��q�b�g��
extern int seGard; //�\���K�[�h��
extern int seRedLaugh;		// �ԏ΂���
extern int seGreenLaugh;	// �Ώ΂���
extern int seYellowLaugh;	// ���΂���
extern int seBlueLaugh;		// �΂���
extern int sePinkLaugh;		// �s���N�΂���
extern int seSetsunaRough;	// �Z�c�i�΂���
extern int seSay;			//�Z���t��
extern int seCutinVoice;	// �J�b�g�C���{�C�X
extern int seDecide;			//���艹

// ---��������---
extern int jisyou_cgBg[72];
extern int se_choiceBGM[6];

// ---�N���W�b�g---
extern int _cgBgCredit;
extern int seCregit;

// ---�Q�[���I�[�o�[���---
extern int seGameOverBGM;	// BGM
extern int seCursor;		//�J�[�\����

//
// �G�t�F�N�g
//

#define EFFECT_TYPE_MAX	(4)	// �G�t�F�N�g�̃^�C�v�̍ő吔
extern int cgEffect[EFFECT_TYPE_MAX][16];	// �_���[�W�G�t�F�N�g

// �h��G�t�F�N�g
extern int LockEffect[5][11];

// �h��񕜃G�t�F�N�g
extern int gateReset[10];
