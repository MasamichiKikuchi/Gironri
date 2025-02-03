#pragma once

#include	"scenebase.h"
#include	"gamemain.h"
#include	"UI.h"
#include	"Player.h"
#include	"effect.h"
#include	<iostream>
#include	<vector>
#include	<string>
#include	<fstream>
#include	"nlohmann/json.hpp"

#define CHOICE_MAX		(5)			//�I�����̍ő�
#define	DRAW_STRING_COUNT	(4)		// �`��^�C�~���O�̃J�E���^
#define	DRAW_EFFECT_COUNT	(4)		// �G�t�F�N�g�̃J�E���^
#define	FRASH_MAX_NUM	(20)		// �t���b�V���̎���

class SceneTalk : public SceneBase {
public:
	SceneTalk(int chapter);				// �R���X�g���N�^
	virtual ~SceneTalk();		// �f�X�g���N�^

	void Input() override;		// ����
	void Process() override;	// �v�Z
	void Draw() override;		// �`��

	void savemessage();			//���O�p�̃��b�Z�[�W�̕ۑ�
	// clace�ǂݍ���
	Player player;
	UI ui;
protected:
	int _cgBg;			// �w�i�摜
	int cgchoice[2];	// �I�����w�i 0:���� 1:�O��
	int cg_popup;		// �|�b�v�A�b�v
	int cg_chara;
	int cg_UI_talk;

	// �A�j���[�V����
	// 0:�L�C�� 1:��

	int animcnt;
	int animflg;
	int animnum;		// 0:�L�C�� 1:��

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
	JsonData _jsonData[JSON_MAX];

	//�G�t�F�N�g�֘A
	int effectcnt;
	int flashcnt;
	int flash_alpha;

	//�e�L�X�g����摜�֌W
	int text_alpha;
	int cgtext;
	int add;
	int text_flg;		//�e�L�X�g�摜�̏o���t���O
	//�A�C�e���|�b�v�A�b�v
	int popupflg;
	float popup_size;

	int messagecnt;	//Json�̓ǂݍ��݃J�E���g

	int save_messagecnt[CHOICE_MAX];	//�I�����p�̃J�E���g�ۑ�

	int shakeflg;		//�V�F�C�N�����t���O

	//se�֘A
	int se_next;
	int se_choice;
	int se_voice;
	int se_selectchoice;

	int savechapter;		//���݂̃`���v�^�[�ۑ�

	int selectcnt;	//���ݑI��ł���I����
	int selectflg;

	//��b�J�E���g
	int drawCnt1;
	int drawCnt2;
	std::string drawMessage1;				// �`�悷�镶����i1�s�j
	std::string drawMessage2;				// �`�悷�镶����i1�s�j

	//�A�j���[�V�������i�[�p
	std::string Anim0;
	std::string Anim1;
	std::string Anim2;
	std::string Anim3;
	std::string Anim4;

	//BGM���i�[�p
	std::string BGM0;
	std::string BGM1;
	std::string BGM2;
	std::string BGM3;
	std::string BGM4;

	int gameCnt;	// ��b�p�[�g�̃Q�[���J�E���^
	int step;		// �t�F�[�h�C���A�E�g�p�X�e�b�v

	// �G�t�F�N�g
	Effect gEffect;
};
