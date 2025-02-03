#pragma once

#include	"scenebase.h"

class SceneCredit : public SceneBase {
public:
	SceneCredit();				// コンストラクタ
	virtual ~SceneCredit();		// デストラクタ

	void Input() override;			// 入力
	void Process() override;		// 計算
	void Draw() override;			// 描画

protected:
	int step;						// フェードインアウト用ステップ
	int Bgy;
};
