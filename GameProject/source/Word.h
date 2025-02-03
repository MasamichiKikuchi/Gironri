#pragma once
#include "ObjectBase.h"
#include "DxLib.h"

//�e�r�S���ӏ��@�t�@�C���S��

#define	THOUGHTLESSWORDS_SPEED_CHAPT0	(6)			// �\���̃X�s�[�h�@�`���[�g���A��
#define	THOUGHTLESSWORDS_SPEED_CHAPT1	(6)			// �\���̃X�s�[�h�@�`���v�^�[1
#define	THOUGHTLESSWORDS_SPEED_CHAPT2	(8)			// �\���̃X�s�[�h�@�`���v�^�[2
#define	THOUGHTLESSWORDS_SPEED_CHAPT3	(6)			// �\���̃X�s�[�h�@�`���v�^�[3
#define	THOUGHTLESSWORDS_SPEED_CHAPT4	(8)			// �\���̃X�s�[�h�@�`���v�^�[4
#define	THOUGHTLESSWORDS_SPEED_CHAPT5	(6)			// �\���̃X�s�[�h�@�`���v�^�[5
#define	THOUGHTLESSWORDS_SCALE	(0.005)		// �\���̊g�嗦
#define	TESTIMONY_SPEED_CHAPT0	(3)			// �،��̃X�s�[�h�@�`���[�g���A��
#define	TESTIMONY_SPEED_CHAPT1	(3)			// �،��̃X�s�[�h�@�`���v�^�[1
#define	TESTIMONY_SPEED_CHAPT2	(3)			// �،��̃X�s�[�h�@�`���v�^�[2
#define	TESTIMONY_SPEED_CHAPT3	(3)			// �،��̃X�s�[�h�@�`���v�^�[3
#define	TESTIMONY_SPEED_CHAPT4	(3)			// �،��̃X�s�[�h�@�`���v�^�[4
#define	TESTIMONY_SPEED_CHAPT5	(3)			// �،��̃X�s�[�h�@�`���v�^�[5
#define	TESTIMONY_SCALE	(0.0025)		// �،��̊g�嗦

class Word : public ObjectBase {
public:
	Word();			// �R���X�g���N�^
	virtual ~Word();	// �f�X�g���N�^
	void Move(int wordType, int chapter);	//���t�𓮂���
	void EraseWord();	//���t������
	int wordType;	// ���̌��t�̎�ށi0:���g�p, 1:�\��, 2:�،�,�j
	int use;		// ���̌��t���g�p���邩�i0:�g�p���Ȃ�, 1:�g�p����j
	float scale;		//���t�̑傫��
	int cgName;	//�摜�n���h��
	int count; //�o���̃^�C�~���O
	int waitTime; //�o�����瓮���o������
	int seName; //����
	int numName;	// �،��Ҕԍ��i0�F��, 1�F��, 2�F��, 3�F��, 4�F�s���N�j
	int testimonyCnt;	// �،��J�E���g
	
protected:
	
};