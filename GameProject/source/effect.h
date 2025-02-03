#pragma once

#define	EFFECT_MAX	(30)	// エフェクトの最大数

class Effect {
public:
	Effect();	// コンストラクタ
	~Effect();	// デストラクタ

	void InitEffect();							// エフェクト情報の初期化
	void AddEffect(int type, int x, int y);		// エフェクト追加
	void ProcessEffect();						// エフェクト処理
	void DrawEffect();							// エフェクト描画

	void ProcessShake();						// 画面揺らし処理

	// エフェクト構造体
	struct EFFECT
	{
		int		use;		// この配列を使用するか（0:使用しない, 1:使用する）
		int		type;		// 動作タイプ
		int		x, y;		// 座標
		int		animcnt;	// アニメーションカウンタ
		int		animspeed;	// アニメーション速度
		int		animnum;	// アニメーションパターン数
		float   scale;		// 画像の大きさ
	};
	// エフェクト情報
	EFFECT effect[EFFECT_MAX];

	// 画面揺らし関連
	int shake;			//背景揺らし幅
	int bgflg;			//揺らしフラグ
	int shakecnt;		//揺らす時間
	int shakespead;		//揺らしスピード
};
