#include "UI.h"
#include "winmain.h"
#include "gamemain.h"
#include "scenegamemain.h"

UI::UI()
{
	//UI
	cgUI_buck = LoadGraph("res/UI/UI_back.png");
	cgUI_IPout = LoadGraph("res/UI/UI_IP_limit_outside.png");
	cgUI_IPin = LoadGraph("res/UI/UI_IP_limit_inside.png");
	cgUI_impulse = LoadGraph("res/UI/UI_impulse.png");
	cgUI_mental = LoadGraph("res/UI/UI_mental.png");
	cgUI_mentalgage_out = LoadGraph("res/UI/UI_mental_limit_outside.png");
	cgUI_mentalgage_in = LoadGraph("res/UI/UI_mental_limit_inside.png");
	cgUI_mentalgage_limit_out = LoadGraph("res/UI/UI_mental_secondlimit_outside.png");
	cgUI_mentalgage_limit_in = LoadGraph("res/UI/UI_mental_secondlimit_inside.png");
	cgUI_message = LoadGraph("res/UI/UI_message.png");
	cgUI_message_noname = LoadGraph("res/UI/UI_message_noname.png");
}

UI::~UI() 
{

}

void UI::DrawGamemainUI(int HP)
{
	DrawGraph(0, 1015, cgUI_buck, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	DrawRectGraph(155, 1042, 0, 0, 0 + (HP * 1611 / MAX_HP), 14, cgUI_mentalgage_in, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawRectGraph(155, 1042, 0, 0, 0 + (gHP * 1611 / MAX_HP), 14, cgUI_mentalgage_in, true);
	DrawGraph(167, 1047, cgUI_mental, true);
}

void UI::DrawTalkUI(int HP, int nameflg)		//nameflgÇ™ÇOÇ»ÇÁñºëOÇ»ÇµÅAÇPÇ»ÇÁñºëOÇ†ÇË
{
	DrawGraph(0, 1015, cgUI_buck, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	DrawRectGraph(155, 1042, 0, 0, 0 + (HP * 1611 / MAX_HP), 14, cgUI_mentalgage_in, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawRectGraph(155, 1042, 0, 0, 0 + (gHP * 1611 / MAX_HP), 14, cgUI_mentalgage_in, true);
	DrawGraph(167, 1047, cgUI_mental, true);
	if (nameflg == 1) {
		DrawGraph(0, 826, cgUI_message, true);
	}
	else
	{
		DrawGraph(0, 826, cgUI_message_noname, true);
	}
}

