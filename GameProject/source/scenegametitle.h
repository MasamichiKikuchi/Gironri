#pragma once

#include	"scenebase.h"

class SceneGameTitle : public SceneBase {
public:
	SceneGameTitle();				// コンストラクタ
	virtual ~SceneGameTitle();		// デストラクタ

	void Input() override;			// 入力
	void Process() override;		// 計算
	void Draw() override;			// 描画

protected:
	int _cgBg;						// 背景画像
	int _cgBgUI;					// 文字
	int step;						// フェードインアウト用ステップ
	int alpha;						// 画像アルファ値
	int frame;						// イージングフレーム数
	int pushKeyFlag;				// ボタンが押されたかのフラグ
};
