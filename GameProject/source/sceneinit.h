#pragma once

#include	"scenebase.h"

class SceneInit : public SceneBase {
public:
	SceneInit();				// コンストラクタ
	virtual ~SceneInit();		// デストラクタ

	void Input() override;			// 入力
	void Process() override;		// 計算
	void Draw() override;			// 描画

protected:
	int cgBg[2];		// 背景画像
	int step;	// フェードインアウト用ステップ
	int stepCnt;	// ステップカウンタ
};
