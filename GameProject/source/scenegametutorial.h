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
#define TUTORIAL_BGM_VOLUME	(50)	// BGMボリューム
#define DAMADE_SE_VOLUME	(50)	//ダメージSEボリューム
#define THOUGHTLESSWORDS_SE_VOLUME	(50)	//暴言出現時SEボリューム
#define TESTIMONY_SE_VOLUME	(50)	//証言出現時SEボリューム
#define SHIELD_SE_VOLUME	(50)	//ガード時SEボリューム
#define	CGBGANIM_SPEED	(5)	// 背景アニメーション速度
#define	CGBGANIM_PATTERN_MAX	(72)	// 背景アニメーションパターン（画像）最大数
#define	ENDEFFECT_SPEED	(3)
#define CUTIN_COUNT	(100)// カットイン表示時間
#define REVERSAL_CARD_COUNT (100)// 反転したカードの表示時間
#define GARD_COUNT (45)// ガードの待機時間

class Scenario;  // Scenarioクラスの前方宣言

class SceneGameTutorial : public SceneBase {
public:
	SceneGameTutorial();				// コンストラクタ
	virtual ~SceneGameTutorial();		// デストラクタ

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
	int chapterNum; //チャプター番号(ゲームシーン用)
	// 画像
	int _cgBgAnimcnt;
	int _cgBgAnimpattern;

	// 議論パート
	int cgCounter;	//反論への遷移(土台)
	int cgCounter_x;	//反論への遷移(ｘボタン)

	//音声

	int gGameCnt;		// ゲーム中カウンタ（毎フレーム+1）
	Word words[WORD_MAX];//証言

	// 取得カード画像

	// 反論カード画像
	int cgHanronMiss;	//反論パートで失敗した時の画像

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

	int text_flg;

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

	// UI・演出画像用構造体
	struct UIGraph
	{
		float	x, y;		// 座標
		float   scale;		// 画像の大きさ
	};


	UIGraph counterGraph;		//反論移行時画像
	float frame;	//イージングフレーム数
	int alpha;	//画像のアルファ値

	//------チュートリアル系------
	int tutorial_num;
	int tutorial_cnt;
	int tutorial_flg;
	int cgchara;

	protected:
		// jsonから読み込んだデータ
		struct JsonData {
			std::string draw;
			int drawX, drawY;
			std::string name;
			std::string message1;
			std::string message2;
			//std::string voice;

			// コマンド系
			// 2:選択「正解」の処理 31~34:選択「不正解」の処理 41~44:不正解時の発言 5:画像の縦移動
			// 21:背景を少し暗く 22:背景をさらに暗く 23:背景を暗く 24:フラッシュ 91:アイテムポップアップ始まり 92:アイテムポップアップ終わり
			// 51~：睨むパート 61~：偽証議論	
			int command;
		};
		JsonData _jsonData[JSON_MAX];

		//テキスト送り
		int text_alpha;
		int cgtext;
		int add;
		//se
		int se_next;
		int se_choice;

		int messagecnt;	//Jsonの読み込みカウント

		int selectcnt;	//現在選んでいる選択肢

		//会話カウント
		int drawCnt1;
		int drawCnt2;
		std::string drawMessage1;				// 描画する文字列（1行）
		std::string drawMessage2;				// 描画する文字列（1行）

		int gameCnt;	// 会話パートのゲームカウンタ
};
