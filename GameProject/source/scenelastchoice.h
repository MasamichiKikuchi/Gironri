#pragma once

#include	"scenebase.h"
#include	"UI.h"
#include	"Player.h"
#include	"gamemain.h"
#include	<iostream>
#include	<vector>
// nlohmann��json�������e�X�g
// �usource/include�v ���v���W�F�N�g�̃v���p�e�B�u�ǉ��̃C���N���[�h�f�B���N�g���v�ɒǉ����Ă���
#include	<string>
#include	<fstream>
#include	"nlohmann/json.hpp"

#define LAST_CHOICE_MAX		(2)			//�I�����̍ő�

class SceneLastChoice : public SceneBase {
public:
	SceneLastChoice(int chapter);				// �R���X�g���N�^
	virtual ~SceneLastChoice();		// �f�X�g���N�^

	void Input() override;		// ����
	void Process() override;	// �v�Z
	void Draw() override;		// �`��

	void savemessage();
	void Flash();

	// clace�ǂݍ���
	Player player;
	UI ui;
protected:
	int _cgBg;
	int cgchoice[2];	// �I�����w�i 0:���� 1:�O��
	int cg_popup;		// �|�b�v�A�b�v
	int cg_chara;
	int cgChoiceBg;
	int cgCorrectEffect[15];//�������G�t�F�N�g
	int cg_UI_talk[2];

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

		//	�R�}���h�n
		//	1:�s�������̕��͎n�܂� 2:�I���u�r�������v�̏��� 3:�I���u�s�����v�̏��� 4:�I���u�S�␳���v�̏��� 5:�摜�̏c�ړ� 6:BGM�ύX 31:�u�s�����v���̉�b
		//	21:�w�i�������Â� 22:�w�i������ɈÂ� 23:�w�i���Â� 24:�t���b�V�� 91:�A�C�e���|�b�v�A�b�v�n�܂� 92:�A�C�e���|�b�v�A�b�v�I���
		//	71:�^�C�g���� 72:�ŏ�����
		int command;
	};
	JsonData _jsonData[JSON_MAX];

	//�G�t�F�N�g�֘A
	int effectcnt;
	int flashcnt;
	int flash_alpha;
	int blackflg;
	int backTalkpartflg;

	//�e�L�X�g����摜�֌W
	int text_alpha;
	int cgtext;
	int add;
	int text_flg;		//�e�L�X�g�摜�̏o���t���O

	int CorrectEffectflg;
	int CorrectEffectcnt;
	int CorrectEffectnum;

	//�A�C�e���|�b�v�A�b�v
	int popupflg;
	float popup_size;

	int messagecnt;	//Json�̓ǂݍ��݃J�E���g

	int save_messagecnt[LAST_CHOICE_MAX];	//�I�����p�̃J�E���g�ۑ�

	int canskip_UI_flg;

	//se
	int se_next;
	int se_choice;
	int se_voice;

	int savechapter;		//���݂̃`���v�^�[�ۑ�

	int selectcnt;	//���ݑI��ł���I����


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
};
