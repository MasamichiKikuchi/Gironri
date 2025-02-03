#pragma once

class SceneBase {
public:
	SceneBase();				// コンストラクタ
	virtual ~SceneBase();		// デストラクタ

	virtual void Input();		// 入力
	virtual void Process();		// 計算
	virtual void Draw();		// 描画

protected:
};