#pragma once
#include "DxLib.h"

class UI{
public:
	UI();			// コンストラクタ
	virtual ~UI();	// デストラクタ


	void DrawGamemainUI(int HP);		// ゲームメイン中UI
	void DrawTalkUI(int HP, int nameflg);			// 会話パート中UI

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