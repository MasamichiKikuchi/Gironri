#pragma once

#include	"Animation.h"
#include	"data.h"
#include	<vector>

#define	CGBGANIM_PATTERN_MAX	(72)	// 偽証議論の背景アニメーションパターン（画像）最大数
#define	CG_JISHOU_BGANIM_PATTERN_MAX	(75)	// 自傷議論の背景アニメーションパターン（画像）最大数
#define DAMAGE_EFFECT_ANINAM_NAM (8)// ダメージエフェクトのアニメーション数
#define DAMAGE_DIRECTION_ANINAM_NAM (3)// ダメージ演出のアニメーション数

class Global {
public:
	Global();			// コンストラクタ
	virtual ~Global();	// デストラクタ

	void Load();		// 読み込み
	int IsLoadFinish();	// 読み込みが終了してたら1、まだなら0

protected:
	Animation anim;

public:
	// ---怪しい箇所を睨むパート（SceneLook）---
	
	// ---偽証議論パート（SceneGameMain）---
	std::vector<int> _cgBg;			// 背景(偽証議論)
	std::vector<int> _cgJishouBg;	// 背景(自傷議論)
};
