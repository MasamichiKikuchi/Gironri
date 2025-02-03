#pragma once

#include	"DxLib.h"

#define	XINPUT_BUTTON_MAX	(16)	// XInputのボタン数

class GamePad {
public:
	GamePad();				// コンストラクタ
	virtual ~GamePad();		// デストラクタ

	virtual void Input();	// 入力更新
public:
	// キーボード＆ゲームパッド1のどちらでも使える場合
	int gKey;
	int gTrg;
	int gRel;

	// ゲームパッド1用の場合
	XINPUT_STATE xinput_pad1;

	// XInput用
	int gXKey[XINPUT_BUTTON_MAX];
	int gXTrg[XINPUT_BUTTON_MAX];
	int gXRel[XINPUT_BUTTON_MAX];
};
