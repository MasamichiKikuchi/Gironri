#include	"gamepad.h"
#include	"DxLib.h"
#include	"winmain.h"
#include	"gamemain.h"

GamePad::GamePad()
{
	gKey = 0;
	gTrg = 0;
	gRel = 0;
}

GamePad::~GamePad()
{

}

void GamePad::Input()
{
	// キー入力、トリガ入力、リリース入力を得る
	int keyold = gKey;
	gKey = GetJoypadInputState(DX_INPUT_PAD1);		// キー入力を取得
	gTrg = (gKey ^ keyold) & gKey;
	gRel = (gKey ^ keyold) & ~gKey;

	// XInputでの入力値取得
	int Xkeyold[XINPUT_BUTTON_MAX];
	for (int i = 0; i < XINPUT_BUTTON_MAX; i++)
	{
		Xkeyold[i] = xinput_pad1.Buttons[i];
	}

	GetJoypadXInputState(DX_INPUT_PAD1, &xinput_pad1);			// pad1の入力値を取得

	for (int i = 0; i < XINPUT_BUTTON_MAX; i++)
	{
		// XInputでのキー入力、トリガ入力、リリース入力を得る
		gXKey[i] = xinput_pad1.Buttons[i];
		gXTrg[i] = (gXKey[i] ^ Xkeyold[i]) & gXKey[i];
		gXRel[i] = (gXKey[i] ^ Xkeyold[i]) & ~gXKey[i];
	}
}
