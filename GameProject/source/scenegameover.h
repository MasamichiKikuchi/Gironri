#pragma once

#include	"scenebase.h"
#include	"UI.h"
#include	"gamemain.h"
#include	"Player.h"
#include	<iostream>
#include	<vector>
#include	<string>
#include	<fstream>
#include	"nlohmann/json.hpp"

#define GAMEOVER_CHOICE_MAX		(2)			//�I�����̍ő�


class SceneGameover : public SceneBase {
public:
	SceneGameover(int chapter);				// �R���X�g���N�^
	virtual ~SceneGameover();		// �f�X�g���N�^

	void Input() override;		// ����
	void Process() override;	// �v�Z
	void Draw() override;		// �`��

	// clace�ǂݍ���
	UI ui;
protected:
	int _cgBg[2];			// �w�i�摜

	// json����ǂݍ��񂾃f�[�^
	struct JsonData {
		std::string draw;
		int drawX, drawY;
		std::string name;
		std::string message1;
		std::string message2;
		//std::string se;

		// �Q�[���I�[�o�[�p�R�}���h
		// 2:�I���u�^�C�g���ɖ߂�v�̏��� 3:�I���u���g���C�v�̏���
		// 4:�Q�[���I�[�o�[�摜�\��
		// 21:�w�i�������Â� 22:�w�i������ɈÂ� 23:�w�i���Â� 24:�t���b�V��
		// 51~�A61~�F�߂�ꏊ
		int command;
	};
	JsonData _jsonData[JSON_MAX];

	//�G�t�F�N�g�֘A
	int effectcnt;
	int break_efffect[45];

	//�e�L�X�g����
	int text_alpha;
	int cgtext;
	int add;
	int text_flg;		//�e�L�X�g�摜�̏o���t���O


	int messagecnt;	//Json�̓ǂݍ��݃J�E���g

	int save_messagecnt[GAMEOVER_CHOICE_MAX];	//�I�����p�̃J�E���g�ۑ�

	//se
	int se_next;
	int se_choice;

	int savechapter;		//���݂̃`���v�^�[�ۑ�

	int selectcnt;	//���ݑI��ł���I����

	//��b�J�E���g
	int drawCnt1;
	int drawCnt2;
	std::string drawMessage1;				// �`�悷�镶����i1�s�j
	std::string drawMessage2;				// �`�悷�镶����i1�s�j

	int gameCnt;	// ��b�p�[�g�̃Q�[���J�E���^


	//�Q�[���I�[�o�[�p�ǉ��ϐ�
	int gameoverflg;		//�Q�[���I�[�o�[�t���O
	int cgarrow;		//�I��p���
};
