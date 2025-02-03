#pragma once

#include	"DxLib.h"
#include	<iostream>
#include	<string>
#include	<vector>

// ---審議会メンバー---
#define	ENEMY_MAX		(5)		// 敵最大人数
#define	GIRON_MAX		(6)		// 偽証議論最大回数
#define	TESTIMONY_MAX	(2)		// 1議論の証言数
#define	TW_NUM			(7)		// １議論での１キャラの暴言最大数
#define	TW_LENGTH		(11)	// 暴言最大文字数

struct ENEMY {
	int cg;			// 敵画像
	int X;			// 敵X座標
	int Y;			// 敵Y座標
};
extern struct ENEMY gikai[ENEMY_MAX];	// 敵証言者番号（0：赤, 1：緑, 2：黄, 3：青, 4：ピンク）

// ---会話パート（SceneTalk）---
// アニメーション
// 0：黄, 1：青
extern int cg_anim[5][24];

// エフェクト
extern int break_efffect[45];	// ブレイク（遷移時）

// ---怪しい箇所を睨むパート（SceneLook）---
// 睨む箇所の構造体
struct LOOK_POINT {
	int chapter;				// 章番号
	int img;					// 画像
	float initX, initY;			// スポットライト初期位置
	int hittype;				// 当たり判定の範囲形状タイプ（0：円, 1：矩形）
	int x, y;					// 当たり判定用座標
	int r;						// 当たり判定用サイズ（円：半径）
	int w, h;					// 当たり判定用サイズ（矩形：横縦）

	std::string lookingMessage;	// 睨み中の文章
	std::string trueMessage;	// 正解文章
	std::string falseMessage;	// 不正解文章
};
extern struct LOOK_POINT tblLookPoint[];	// 睨むパートデータテーブル
extern int tblLPSize;						// 睨むパートデータテーブルサイズ

// 特殊不正解の構造体
struct LOOK_POINT_EASTER {
	int chapter;				// 章番号
	int hittype;				// 当たり判定の範囲形状タイプ（0：円, 1：矩形）
	int x, y;					// 当たり判定用座標
	int r;						// 当たり判定用サイズ（円：半径）
	int w, h;					// 当たり判定用サイズ（矩形：横縦）

	std::string message1;	// 文章1
	std::string message2;	// 文章2
	std::string message3;	// 文章3
};
extern struct LOOK_POINT_EASTER tblLookEaster[GIRON_MAX][6];	// 睨むパートイースターエッグデータテーブル
//extern int tblEELSize;										// 特殊不正解データテーブルサイズ

extern int cgLookButtonUI;		// 睨むパートボタンUI

// ---偽証議論パート（SceneGameMain）---

// 動画
extern int mvGiron_ikou;	// 偽証議論移行用動画
extern int mvJishou_ikou;	// 自傷議論移行用動画

// 議論パート（シナリオ：罵詈雑言, 証言）
// 証言（1次元目：各議論, ２次元目：審議会メンバー, ３次元目：１議論での証言数）
extern int cgTestimony[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX];
// 罵詈雑言
// ロード用情報
struct THOUGHTLESS_WORD {
	char imgPath[128];		// 画像パス
	int allNum;				// 画像の分割総数
	int xNum, yNum;			// 横（x）方向に対する分割数, 縦（y）方向に対するに対する分割数
	int xSize, ySize;		// 分割された画像1つの大きさ
};
extern struct THOUGHTLESS_WORD redTW[GIRON_MAX][TW_NUM];		// 赤
extern struct THOUGHTLESS_WORD greenTW[GIRON_MAX][TW_NUM];		// 緑
extern struct THOUGHTLESS_WORD yellowTW[GIRON_MAX][TW_NUM];		// 黄
extern struct THOUGHTLESS_WORD blueTW[GIRON_MAX][TW_NUM];		// 青
extern struct THOUGHTLESS_WORD pinkTW[GIRON_MAX][TW_NUM];		// ピンク
extern struct THOUGHTLESS_WORD setsunaTW[GIRON_MAX][TW_NUM];	// セツナ（自傷議論）
// 画像
extern int cgRedThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];			// 赤
extern int cgGreenThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// 緑
extern int cgYellowThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// 黄
extern int cgBlueThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// 青
extern int cgPinkThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// ピンク
extern int cgSetsunaThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// セツナ（自傷議論）

extern int cgCounter;	//反論への遷移(土台)
extern int cgCounter_x;	//反論への遷移(ｘボタン)

extern int cgCutIn[30];		//カットイン
extern int cgPlayguide;		//操作説明
extern int cgGironButtonUI;		// 議論パートボタンUI
extern int cgHanronButtonUI;	// 反論パートボタンUI

// 反論パート
extern int cgStockCard[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX];		// 取得カードの画像（1次元目：各議論, ２次元目：審議会メンバー, ３次元目：１議論での証言数）
extern int cgCounterCard[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX];		// 反論カードの画像（1次元目：各議論, ２次元目：審議会メンバー, ３次元目：１議論での証言数）

extern int cgReturnCard[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX];		// 反転カードの画像（1次元目：各議論, ２次元目：審議会メンバー, ３次元目：１議論での証言数）

struct ANSWER_CARD {
	int answerNum;		// 正解のカードを飛ばす審議会委員の番号
	int ansCardCnt;		// 証言者の何番目の発言か
};
extern struct ANSWER_CARD tblAnsCard[];		// 正解データテーブル
extern int tblACSize;						// 正解データテーブルサイズ

// 取得前の手札配置の画像（黒）・取得直後の手札配置の画像（白）
extern int cgStockBrankCard;
extern int cgStockWhiteCard;

// 裏返し用画像
#define	TURN_CARD_MAX	(3)	// 裏返し用画像の最大枚数
extern std::vector<int> cgTurnCard;

extern int deckMax[GIRON_MAX];		// 各偽証議論での手札の所持可能最大数

// 反論パート正解時エフェクト
#define ENDEFFECT_PATTERN_MAX			(72)	// 偽証議論
#define JISYOU_ENDEFFECT_PATTERN_MAX	(72)	// 自傷議論

extern std::vector<int> cgEndEffect;		// 偽証議論
extern std::vector<int> cgJisyou_EndEffect;	// 自傷議論

// 間違った場合の画像
extern int cgHanronMiss;		// 偽証議論
extern int cgJishouHanronMiss;	// 自傷議論

//
// SE・BGM
//
// ---タイトル画面---
extern int seTitleBGM;	// BGM

// ---会話パート---
extern int seBGM[5];	// BGM

// ---怪しい箇所を睨むパート---
extern int seLookClear;		// 
extern int seLookDamage;	// ダメージ
extern int seLookHazure;	// ハズレ
extern int seLookSeikai;	// 正解
extern int seLookBGM;		// BGM

// ---偽証議論パート---
//音声
extern int seDamage; //ダメージ音
extern int seBGM1; //BGM1
extern int seBGM2; //BGM2
extern int seTestimonyBreak; //証言ガード時
extern int seGetTestimony; //証言取得時
extern int seCardGathering; //証言移動時
extern int seCardOpening; //証言展開時
extern int seCardSelecting; //証言選択変更
extern int seHazure; //偽証言選択時
extern int seCutin; //カットイン時
extern int seCardTurning; //証言反転時
extern int seHitTestimony; //正解証言ヒット時
extern int seGard; //暴言ガード時
extern int seRedLaugh;		// 赤笑い声
extern int seGreenLaugh;	// 緑笑い声
extern int seYellowLaugh;	// 黄笑い声
extern int seBlueLaugh;		// 青笑い声
extern int sePinkLaugh;		// ピンク笑い声
extern int seSetsunaRough;	// セツナ笑い声
extern int seSay;			//セリフ音
extern int seCutinVoice;	// カットインボイス
extern int seDecide;			//決定音

// ---自傷推理---
extern int jisyou_cgBg[72];
extern int se_choiceBGM[6];

// ---クレジット---
extern int _cgBgCredit;
extern int seCregit;

// ---ゲームオーバー画面---
extern int seGameOverBGM;	// BGM
extern int seCursor;		//カーソル音

//
// エフェクト
//

#define EFFECT_TYPE_MAX	(4)	// エフェクトのタイプの最大数
extern int cgEffect[EFFECT_TYPE_MAX][16];	// ダメージエフェクト

// 防御エフェクト
extern int LockEffect[5][11];

// 防御回復エフェクト
extern int gateReset[10];
