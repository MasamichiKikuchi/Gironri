#pragma once

#include	"scenebase.h"
#include	"winmain.h"
#include	"Word.h"
#include	"Player.h"
#include	"deck.h"
#include	"UI.h"
#include	"Animation.h"
#include	"Scenario.h"
#include	"effect.h"
#include	<iostream>
#include	<vector>

//
// 定数・構造体定義
//
#define	CARD_MAX	(99)			// カード配列最大数
#define PLAYER_GET_LINE (940)		// ライン
#define WORD_MAX (99)				// 証言配列最大数
#define BGM_VOLUME	(50)	//BGMボリューム	※ボリュームは全て255段階
#define DAMADE_SE_VOLUME	(50)	//ダメージSEボリューム
#define THOUGHTLESSWORDS_SE_VOLUME	(50)	//暴言出現時SEボリューム
#define TESTIMONY_SE_VOLUME	(50)	//証言出現時SEボリューム
#define SHIELD_SE_VOLUME	(50)	//ガード時SEボリューム
#define	CGBGANIM_SPEED	(5)	// 背景アニメーション速度
#define	CGBGANIM_PATTERN_MAX	(72)	// 背景アニメーションパターン（画像）最大数
#define	ENDEFFECT_SPEED	(3)
#define CUTIN_COUNT	(100)// カットイン表示時間
#define REVERSAL_CARD_COUNT (100)// 反転したカードの表示時間
#define GARD_COUNT (23)// ガードの待機時間

class Scenario;  // Scenarioクラスの前方宣言

class SceneGameMain : public SceneBase {
public:
	SceneGameMain(int chapter);				// コンストラクタ
	virtual ~SceneGameMain();		// デストラクタ

	void Input() override;			// 入力
	void Process() override;		// 計算
	void Draw() override;			// 描画
	int GetCutinFlag();				//カットインフラグのゲッター
	
	Player player;
	UI ui;
	Animation anim;
protected:
	void AddWord(int wordType, int count, int cgName, int x, int y, int waitTime, int seName, int numName, int ttmCnt);	// 敵追加
	void SetScenario(const std::vector<Scenario::SCENARIO>& scenario);		// 敵の出現シナリオ
	void SpotLight(int cx, int cy, int cr, int baseA);		// ライトのマスデータに円のスポットライトを入れる

	bool CheckTestimony();		//シナリオ内と手札の証言が一致しているかの確認
	void GetScenarioTestimony(const std::vector<Scenario::SCENARIO>& scenario);		//シナリオ内の証言数の取得

protected:
	// 画像
	int _cgBgAnimcnt;
	int _cgBgAnimpattern;
	int _cgBgJishouAnimpattern;

	// jsonから読み込んだデータ
	struct JsonData {
		std::string draw;
		std::string bg;
		int drawX, drawY, bgY;
		std::string name;
		std::string message1;
		std::string message2;
		std::string voice;

		// コマンド系
		//	2:選択「正解」の処理 31~34:選択「不正解」の処理 41~44:不正解時の発言 5:画像の縦移動 6:BGM変更 7:セリフが流れきるまで飛ばせない
		//	21:背景を少し暗く 22:背景をさらに暗く 23:背景を暗く 24:フラッシュ 91:アイテムポップアップ始まり 92:アイテムポップアップ終わり
		//	51~：睨むパート 61~：偽証議論 71:タイトルへ 72:自傷推理へ
		int command;
	};
	JsonData _jsonData[999];

	int text_flg;
	int messagecnt;	//Jsonの読み込みカウント
	//会話カウント
	int drawCnt1;
	int drawCnt2;
	std::string drawMessage1;				// 描画する文字列（1行）
	std::string drawMessage2;				// 描画する文字列（1行）

	//音声
	int gGameCnt;		// ゲーム中カウンタ（毎フレーム+1）
	Word words[WORD_MAX];//証言
	
	// 取得カード画像

	// 正解のカード画像

	// 裏返し用画像

	Deck myDeck;		// 取得した証言カードのデッキ
	int have_card;		// デッキ内の証言カード数

	//防御エフェクト関連
	int lockCnt;
	int blockse;
	int LockInterval;

	//ムービー
	int MovieHandle;
	int Movieflg;

	//テスト
	int flamecnt;

	// スポットライト
	// ライトのマスサイズ
	static const int	LIGHTSIZE_W = 8;
	static const int	LIGHTSIZE_H = 8;

	// ライトのマス数
	static const int	LIGHTMAP_W = (SCREEN_W / LIGHTSIZE_W);
	static const int	LIGHTMAP_H = (SCREEN_H / LIGHTSIZE_H);
	
	// ライトのマスデータ
	int	_mapLight[LIGHTMAP_W * LIGHTMAP_H];

	int flg_gameflow;	// ゲーム進行状態（0…議論, 1…反論, 2…フィニッシュ）
	int flg_shield;		// 盾をかまえているか（0…していない, 1…している）

	// ポーズ機能
	bool isPause;

	// エフェクト
	Effect gEffect;

	//フラッシュ関連
	int flashcnt;
	int flash_alpha;

	// 反論パート正解時エフェクト
	int endEffectCnt;
	int endEffect_waitCnt;
	int endEffectpattern;

	int cutInFlag;	//カットイン中のフラグ
	int cutInCount;	//カットイン表示

	int gardCount;	//ガードの待機時間
	
	Scenario scenario;//シナリオクラスのインスタンス
	int scenarioTestimonyCnt;//シナリオ内の証言数

	int counterFlag;//反論パート移行のフラグ

	int misDirectionFlagCnt;//反論パート失敗演出のフラグカウント

	int gameFinishFlag;//ゲーム終了のフラグ

	// UI・演出画像用構造体
	struct UIGraph
	{
		float	x, y;		// 座標
		float   scale;		// 画像の大きさ
	};


	UIGraph counterGraph;		//反論移行時画像
	float frame;	//イージングフレーム数
	int alpha;	//画像のアルファ値
};
