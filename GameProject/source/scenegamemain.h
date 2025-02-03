#pragma once

#include	"scenebase.h"
#include	"winmain.h"
#include	"Word.h"
#include	"Player.h"
#include	"deck.h"
#include	"UI.h"
#include	"Animation.h"
#include	"Scenario.h"
#include	"effect.h"
#include	<iostream>
#include	<vector>

//
// �萔�E�\���̒�`
//
#define	CARD_MAX	(99)			// �J�[�h�z��ő吔
#define PLAYER_GET_LINE (940)		// ���C��
#define WORD_MAX (99)				// �،��z��ő吔
#define BGM_VOLUME	(50)	//BGM�{�����[��	���{�����[���͑S��255�i�K
#define DAMADE_SE_VOLUME	(50)	//�_���[�WSE�{�����[��
#define THOUGHTLESSWORDS_SE_VOLUME	(50)	//�\���o����SE�{�����[��
#define TESTIMONY_SE_VOLUME	(50)	//�،��o����SE�{�����[��
#define SHIELD_SE_VOLUME	(50)	//�K�[�h��SE�{�����[��
#define	CGBGANIM_SPEED	(5)	// �w�i�A�j���[�V�������x
#define	CGBGANIM_PATTERN_MAX	(72)	// �w�i�A�j���[�V�����p�^�[���i�摜�j�ő吔
#define	ENDEFFECT_SPEED	(3)
#define CUTIN_COUNT	(100)// �J�b�g�C���\������
#define REVERSAL_CARD_COUNT (100)// ���]�����J�[�h�̕\������
#define GARD_COUNT (23)// �K�[�h�̑ҋ@����

class Scenario;  // Scenario�N���X�̑O���錾

class SceneGameMain : public SceneBase {
public:
	SceneGameMain(int chapter);				// �R���X�g���N�^
	virtual ~SceneGameMain();		// �f�X�g���N�^

	void Input() override;			// ����
	void Process() override;		// �v�Z
	void Draw() override;			// �`��
	int GetCutinFlag();				//�J�b�g�C���t���O�̃Q�b�^�[
	
	Player player;
	UI ui;
	Animation anim;
protected:
	void AddWord(int wordType, int count, int cgName, int x, int y, int waitTime, int seName, int numName, int ttmCnt);	// �G�ǉ�
	void SetScenario(const std::vector<Scenario::SCENARIO>& scenario);		// �G�̏o���V�i���I
	void SpotLight(int cx, int cy, int cr, int baseA);		// ���C�g�̃}�X�f�[�^�ɉ~�̃X�|�b�g���C�g������

	bool CheckTestimony();		//�V�i���I���Ǝ�D�̏،�����v���Ă��邩�̊m�F
	void GetScenarioTestimony(const std::vector<Scenario::SCENARIO>& scenario);		//�V�i���I���̏،����̎擾

protected:
	// �摜
	int _cgBgAnimcnt;
	int _cgBgAnimpattern;
	int _cgBgJishouAnimpattern;

	// json����ǂݍ��񂾃f�[�^
	struct JsonData {
		std::string draw;
		std::string bg;
		int drawX, drawY, bgY;
		std::string name;
		std::string message1;
		std::string message2;
		std::string voice;

		// �R�}���h�n
		//	2:�I���u�����v�̏��� 31~34:�I���u�s�����v�̏��� 41~44:�s�������̔��� 5:�摜�̏c�ړ� 6:BGM�ύX 7:�Z���t�����ꂫ��܂Ŕ�΂��Ȃ�
		//	21:�w�i�������Â� 22:�w�i������ɈÂ� 23:�w�i���Â� 24:�t���b�V�� 91:�A�C�e���|�b�v�A�b�v�n�܂� 92:�A�C�e���|�b�v�A�b�v�I���
		//	51~�F�ɂރp�[�g 61~�F�U�؋c�_ 71:�^�C�g���� 72:����������
		int command;
	};
	JsonData _jsonData[999];

	int text_flg;
	int messagecnt;	//Json�̓ǂݍ��݃J�E���g
	//��b�J�E���g
	int drawCnt1;
	int drawCnt2;
	std::string drawMessage1;				// �`�悷�镶����i1�s�j
	std::string drawMessage2;				// �`�悷�镶����i1�s�j

	//����
	int gGameCnt;		// �Q�[�����J�E���^�i���t���[��+1�j
	Word words[WORD_MAX];//�،�
	
	// �擾�J�[�h�摜

	// �����̃J�[�h�摜

	// ���Ԃ��p�摜

	Deck myDeck;		// �擾�����،��J�[�h�̃f�b�L
	int have_card;		// �f�b�L���̏،��J�[�h��

	//�h��G�t�F�N�g�֘A
	int lockCnt;
	int blockse;
	int LockInterval;

	//���[�r�[
	int MovieHandle;
	int Movieflg;

	//�e�X�g
	int flamecnt;

	// �X�|�b�g���C�g
	// ���C�g�̃}�X�T�C�Y
	static const int	LIGHTSIZE_W = 8;
	static const int	LIGHTSIZE_H = 8;

	// ���C�g�̃}�X��
	static const int	LIGHTMAP_W = (SCREEN_W / LIGHTSIZE_W);
	static const int	LIGHTMAP_H = (SCREEN_H / LIGHTSIZE_H);
	
	// ���C�g�̃}�X�f�[�^
	int	_mapLight[LIGHTMAP_W * LIGHTMAP_H];

	int flg_gameflow;	// �Q�[���i�s��ԁi0�c�c�_, 1�c���_, 2�c�t�B�j�b�V���j
	int flg_shield;		// �������܂��Ă��邩�i0�c���Ă��Ȃ�, 1�c���Ă���j

	// �|�[�Y�@�\
	bool isPause;

	// �G�t�F�N�g
	Effect gEffect;

	//�t���b�V���֘A
	int flashcnt;
	int flash_alpha;

	// ���_�p�[�g�������G�t�F�N�g
	int endEffectCnt;
	int endEffect_waitCnt;
	int endEffectpattern;

	int cutInFlag;	//�J�b�g�C�����̃t���O
	int cutInCount;	//�J�b�g�C���\��

	int gardCount;	//�K�[�h�̑ҋ@����
	
	Scenario scenario;//�V�i���I�N���X�̃C���X�^���X
	int scenarioTestimonyCnt;//�V�i���I���̏،���

	int counterFlag;//���_�p�[�g�ڍs�̃t���O

	int misDirectionFlagCnt;//���_�p�[�g���s���o�̃t���O�J�E���g

	int gameFinishFlag;//�Q�[���I���̃t���O

	// UI�E���o�摜�p�\����
	struct UIGraph
	{
		float	x, y;		// ���W
		float   scale;		// �摜�̑傫��
	};


	UIGraph counterGraph;		//���_�ڍs���摜
	float frame;	//�C�[�W���O�t���[����
	int alpha;	//�摜�̃A���t�@�l
};
