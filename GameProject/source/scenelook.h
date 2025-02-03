#pragma once

#include	"scenebase.h"
#include	"winmain.h"
#include	"gamemain.h"
#include	"UI.h"
#include	"effect.h"
#include	"Player.h"
#include	<iostream>
#include	<vector>
#include	<string>

#define	ALPHA_VALUE	(150)	// アルファ値
#define	SPOTLIGHT_SPEED	(7)	// スポットライトの移動速度
#define	SPOTLIGHT_SIZE_MAX	(150)	// スポットライトの最大サイズ
#define	SPOTLIGHT_SIZE_MIN	(10)	// スポットライトの最小サイズ
#define	DRAW_MESSAGE_COUNT	(2)	// 描画タイミングのカウンタ
#define LOOK_BGM_VOLUME	(70)	// BGMボリューム	※ボリュームは全て255段階
#define LOOK_SE_VOLUME	(70)	// SEボリューム

class SceneLook : public SceneBase {
public:
	SceneLook(int chapter);
	virtual ~SceneLook();

	void Input() override;
	void Process() override;
	void Draw() override;

protected:
	//int _cgBg;		// 背景

	int flgAnswer;		// 睨んだ箇所が正解か（初期：0, 正解：1, 不正解：2, 特殊不正解：3）

	// ---スポットライト---
	// ライトのマスサイズ
	static const int LIGHTSIZE_W = 2;
	static const int LIGHTSIZE_H = 2;

	// ライトのマス数
	static const int LIGHTMAP_W = (SCREEN_W / LIGHTSIZE_W);
	static const int LIGHTMAP_H = (SCREEN_H / LIGHTSIZE_H);

	// ライトのマスデータ
	int mapLight[LIGHTMAP_W * LIGHTMAP_H];
	int mapAnsLight[LIGHTMAP_W * LIGHTMAP_H];	// 正解用

	// スポットライトの位置, サイズ
	VECTOR vSpotLight;
	int spotlightSize;
	int ansLightSize;	// 正解用ライトのサイズ

	// ライトマップの値のセット
	void SetLightMap();
	// ライトのマスデータに円のスポットライトを入れる
	void SpotLight(int cx, int cy, int cr, int alpha, int typeAns);

	// ---操作関係---
	VECTOR vInputR;		// 右スティックの入力値
	VECTOR vUnitR;		// 右スティック入力値によるの単位ベクトル
	VECTOR vDirR;		// 移動量

	// ---文章---
	std::string drawMessage1;				// 描画する文字列（1行目）
	std::string drawMessage2;				// 描画する文字列（2行目）
	std::string drawMessage3;				// 描画する文字列（3行目）
	int talkCnt;		// セリフ発言カウンタ
	int flgAllTalk;	// セリフ全文表示するか（0：しない, 1：する）
	int allTalkCnt;	// 全文表示カウント
	int lineflg;	// 2行目判定
	int drawCnt1;	// 1行目会話カウント
	int drawCnt2;	// 2行目会話カウント

	//---関数---
	void NormInput(XINPUT_STATE xinput);	// 右スティックの入力値の正規化
	void splMove(XINPUT_STATE xinput);		// 円の移動
	void splScale(XINPUT_STATE xinput);		// 円のサイズ変更（拡大縮小）
	void CheckPoint(float px, float py);	// 睨んだ箇所のチェック
	void lookTalk();						// 怪しい箇所を選択時のセリフ

	UI ui;		// UI関連

	Effect gEffect;		// エフェクト

	Player player;

	int lightCnt;		// ライトマスカウント
	int step;			// フェードインアウト用ステップ

	int UniqueNoAnsNum;
	int UniqueNoAnsCnt;
	int flgLook;		// 決定ボタン有効判定フラグ（0：無効（開始時）, 1：無効（エフェクト中）, 2：有効）
};
