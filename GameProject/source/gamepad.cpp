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
	// �L�[���́A�g���K���́A�����[�X���͂𓾂�
	int keyold = gKey;
	gKey = GetJoypadInputState(DX_INPUT_PAD1);		// �L�[���͂��擾
	gTrg = (gKey ^ keyold) & gKey;
	gRel = (gKey ^ keyold) & ~gKey;

	// XInput�ł̓��͒l�擾
	int Xkeyold[XINPUT_BUTTON_MAX];
	for (int i = 0; i < XINPUT_BUTTON_MAX; i++)
	{
		Xkeyold[i] = xinput_pad1.Buttons[i];
	}

	GetJoypadXInputState(DX_INPUT_PAD1, &xinput_pad1);			// pad1�̓��͒l���擾

	for (int i = 0; i < XINPUT_BUTTON_MAX; i++)
	{
		// XInput�ł̃L�[���́A�g���K���́A�����[�X���͂𓾂�
		gXKey[i] = xinput_pad1.Buttons[i];
		gXTrg[i] = (gXKey[i] ^ Xkeyold[i]) & gXKey[i];
		gXRel[i] = (gXKey[i] ^ Xkeyold[i]) & ~gXKey[i];
	}
}
