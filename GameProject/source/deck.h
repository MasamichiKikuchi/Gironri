#pragma once

#include	"DxLib.h"
#include	<iostream>
#include	<deque>
#include	<vector>

#define	ENEMY_MAX	(5)		// �G�ő�l��
#define	CARD_SPEED	(10 * 2.5)	// �J�[�h�̑��x
#define	DECREASE_SCALE (0.005 * 2.5)		//�J�[�h�̏������Ȃ�x��
#define	ENEMY_HIT_X	(10)	//�G�̓�����͈́iX���W�j
#define	ENEMY_HIT_Y	(10)	//�G�̓�����͈́iY���W�j
#define	DECK_CARD_X	(1830)	// �c�_�p�[�g���̎�D�̈ʒu�ix���W�j
#define	DECK_CARD_Y	(801)	// �c�_�p�[�g���̎�D�̈ʒu�iy���W�j

class Deck {
public:
	Deck();		// �R���X�g���N�^
	~Deck();	// �f�X�g���N�^

	int GetCenterCard();						// ��D�̒��S�ʒu�i�I�𒆂̃J�[�h�j
	bool CheckCard(int number, int ttmCnt);		// �����،����������Ă��邩�̊m�F
	void GetCard(int number, int cgCard, int wordX, int wordY, float wordScale, int wordTtmCnt);	// ��D�ǉ�
	void SelectCard();							// �J�[�h�I��, ���𔻒�
	void TurnCard();							// �J�[�h�̗��Ԃ�
	void MotionCard(int flg_gf);				// �c�_���J�[�h���[�V����
	void SetDrawCard(int flg_gf);	// �Q�[���󋵂ɍ��킹�ăJ�[�h��ύX
	void DrawCard(int flg_gf);		// �J�[�h�\��
	void MoveCard(int &flg_gf);					// �J�[�h�̈ړ�
	void SetCutInFlag(int cutInFlag);			// �J�b�g�C�����t���O�̎擾

protected:
	float calcX(int i);		// �J�[�h��X���W�̌v�Z��

public:
	struct CARD {
		int num;			// �J�[�h�،��Ҕԍ��i0�F��, 1�F��, 2�F��, 3�F��, 4�F�s���N�j
		int cg;				// �J�[�h�摜
		VECTOR pos;			// �J�[�h�̑傫��
		float scale;		// �J�[�h�̑傫��
		int motionCnt;		// ���[�V�����J�E���g
		int testimonyCnt;	// �،��J�E���g
		float direction;	// �ړ�����p�x
		float speed;		// �ړ����鑬��
	};
	std::deque<CARD> cards;		// ��D

	int answer_card;	// �����̃J�[�h
	int flg_ans;		// ���𔻒�t���O�i0�F�I��, 1�F����, 2�F�s�����j
	int flg_selectCard;	// �J�[�h���I���ł��邩�ǂ����i0�F��ʊO�Ɉړ�, 1�F��ʓ��Ɉړ�, 2�F�W�J, 3�F�I��, 4�F�����j
	int cardMoveFlag;	// �J�[�h���ړ��\��
	int deckCutInflag;  // �J�b�g�C�������̔��ʃt���O
	int cardSelectEffectFlag;	// �J�[�h�I�����̉��o�t���O

protected:
	int getCnt;				// �擾���̃J�[�h�J�E���g
	int turnCnt;			// ���]���̃J�[�h�J�E���g
	float frame;
};
