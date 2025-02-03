#pragma once

#include	"DxLib.h"

#define	XINPUT_BUTTON_MAX	(16)	// XInput�̃{�^����

class GamePad {
public:
	GamePad();				// �R���X�g���N�^
	virtual ~GamePad();		// �f�X�g���N�^

	virtual void Input();	// ���͍X�V
public:
	// �L�[�{�[�h���Q�[���p�b�h1�̂ǂ���ł��g����ꍇ
	int gKey;
	int gTrg;
	int gRel;

	// �Q�[���p�b�h1�p�̏ꍇ
	XINPUT_STATE xinput_pad1;

	// XInput�p
	int gXKey[XINPUT_BUTTON_MAX];
	int gXTrg[XINPUT_BUTTON_MAX];
	int gXRel[XINPUT_BUTTON_MAX];
};
