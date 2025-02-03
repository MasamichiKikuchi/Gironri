#pragma once
#include "DxLib.h"

class UI{
public:
	UI();			// �R���X�g���N�^
	virtual ~UI();	// �f�X�g���N�^


	void DrawGamemainUI(int HP);		// �Q�[�����C����UI
	void DrawTalkUI(int HP, int nameflg);			// ��b�p�[�g��UI

protected:
	//UI
	int cgUI_buck;
	int cgUI_IPout;
	int cgUI_IPin;
	int cgUI_impulse;
	int cgUI_mental;
	int cgUI_mentalgage_out;
	int cgUI_mentalgage_in;
	int cgUI_mentalgage_limit_out;
	int cgUI_mentalgage_limit_in;
	int cgUI_message;
	int cgUI_message_noname;
};