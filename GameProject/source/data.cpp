#include	"data.h"
#include	"winmain.h"

// ---審議会メンバー---
struct ENEMY gikai[ENEMY_MAX];

// ---会話パート（SceneTalk）---
// アニメーション
// 0：黄, 1：青
int cg_anim[5][24];

// エフェクト
int break_efffect[45];	// ブレイク（遷移時）

// ---怪しい箇所を睨むパート（SceneLook）---
// 睨むパートデータテーブル
struct LOOK_POINT tblLookPoint[] = {
	// chapter,	img,	initX, initY,				hittype,		x, y,			r			w, h,		lookingMessage,								trueMessage,	falseMessage
	// 章番号,	画像,	スポットライト初期位置,			当たり判定タイプ,	当たり判定用座標,	サイズ（円）	サイズ（矩形）	睨み中の文章,									正解文章,			不正解
	{	0,		-1,		SCREEN_W / 2, SCREEN_H / 2,	0,				 853, 419,		123,		 -1,  -1,	"ユウのナイフではないといえる証拠を見つけよう。",	"見つけた！！",	"ユウのナイフなら、私の名前が書いてあるはず......"},
	{	1,		-1,		SCREEN_W / 2, SCREEN_H / 2,	0,				 477, 318,		122,		 -1,  -1,	"手がかりになるものを見つけよう。",				"見つけた！！",	"これは手がかりにはならない......"},
	{	2,		-1,		SCREEN_W / 2, SCREEN_H / 2,	0,				 844, 716,		108,		 -1,  -1,	"霧雨を納得させるための材料を見つけよう。",		"見つけた！！",	"これでは納得させられないだろう......"},
	{	3,		-1,		SCREEN_W / 2, SCREEN_H / 2,	1,				 510, 570,		 -1,		585, 125,	"有栖川ハルの情報を確認しよう。",				"見つけた！！",	"確認すべき情報はこれじゃない......"},
	{	4,		-1,		SCREEN_W / 2, SCREEN_H / 2,	1,				1119, 606,		 -1,		282, 167,	"手紙と筆跡が一致する生徒手帳を見つけよう。",		"見つけた！！",	"これは違うみたい......"},
	{	5,		-1,		960, 760,					0,				1020, 487,		123,		 -1,  -1,	"楠木が動揺していたといえる根拠を見つけよう。",	"見つけた！！",	"これは根拠にならない......"},
};
int tblLPSize = sizeof(tblLookPoint) / sizeof(tblLookPoint[0]);		// 睨むパートデータテーブルサイズ

// 睨むパート特殊不正解データテーブル
struct LOOK_POINT_EASTER tblLookEaster[GIRON_MAX][6] = {
	// chapter,	hittype,		x, y,			r			w, h,		message1, message2, message3
	// 章番号,	当たり判定タイプ,	当たり判定用座標,	サイズ（円）	サイズ（矩形）	睨み中の文章1, 2, 3
	{{	0,		1,				 986, 367,		  0,		460, 287,	"ユウと交換した思い出のナイフ。", "折り畳み式で、刃にお互いの名前を彫っている。"}},

	{{	1,		0,				1625, 333,		244,		 -1,  -1,	"なぜ彼女は殺されたのだろう？"},
	{	1,		0,				 293, 519,		135,		 -1,  -1,	"......近くに見覚えのあるものが落ちている。"},
	{	1,		0,				 732, 444,		144,		 -1,  -1,	"......近くに見覚えのあるものが落ちている。"},
	{	1,		0,				1182, 247,		165,		 -1,  -1,	"深く刺さるナイフが痛々しい。", "だが、目立った違和感はない。"}},

	{{	2,		0,				 928,  35,		100,		 -1,  -1,	"すごい剣幕だ......目を合わせられない。"},
	{	2,		0,				1030, 527,		134,		 -1,  -1,	"......今はこんなところに注目している場合ではない。", "...私よりも大きい......", "おい！何をじろじろ見ている！変態！"},
	{	2,		0,				 672, 560,		100,		 -1,  -1,	"......今はこんなところに注目している場合ではない。", "...私よりも大きい......", "おい！何をじろじろ見ている！変態！"}},
	
	{{	3,		1,				1119, 243,		 -1,		252, 381,	"大きいリボンが特徴的だ。", "なぜポンチョを着ているのだろう。"},
	{	3,		1,				 512, 243,		 -1,		582, 113,	"有栖川ハル......", "名前を聞けば、誰でも女性だと思うだろう。"},
	{	3,		1,				 512, 449,		 -1,		582, 113,	"まだ１年生なのに審査会に所属している。", "良家出身の令嬢なのだろう"}},

	{{	4,		1,				1119, 259,		 -1,		282, 167,	"生徒会長。字が綺麗だ。", "だが、脅迫文の筆跡とは一致しないだろう。"},
	{	4,		1,				1119,  86,		 -1,		282, 167,	"意外と可愛らしい文字だ。", "だが、脅迫文の筆跡とは一致しないだろう。"},
	{	4,		1,				1119, 432,		 -1,		282, 167,	"几帳面そうな字だ。", "だが、脅迫文の筆跡とは一致しないだろう。"},
	{	4,		1,				 520,  81,		 -1,		543, 427,	"特徴のある文字だ。", "この筆跡と合致する人を探そう。"},
	{	4,		1,				 520, 512,		 -1,		543, 268,	"「お前の秘密をバラす」", "有栖川が男であるという秘密を指している。"}},

	{{	5,		1,				 731, 864,		 -1,		490, 216,	"......まあまあね。"},
	{	5,		1,				 846, 245,		 -1,		364, 120,	"眼鏡のフチまで緑とは......", "もしかして、ラッキーカラーなのだろうか。"}}
};
//int tblEELSize = sizeof(tblLookEaster) / sizeof(tblLookEaster[0]);		// 特殊不正解データテーブルサイズ

int cgLookButtonUI;		// 睨むパートボタンUI

// ---偽証議論パート（SceneGameMain）---

int mvGiron_ikou;	// 偽証議論移行用動画
int mvJishou_ikou;	// 自傷議論移行用動画

// 議論パート（シナリオ：罵詈雑言, 証言）
// 
// 1次元目（GIRON_MAX）は偽証議論回数
// 2次元目（ENEMY_MAX）は審議会メンバーの種類（0：赤, 1：緑, 2：黄, 3：青, 4：ピンク）
// 3次元目（TESTIMONY_MAX）は1議論での審議会メンバーの1人の発言
// 証言
int cgTestimony[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX];

// 罵詈雑言
// ロード用情報
//		{imgPath[128],													allNum,	xNum, yNum,	xSize, ySize}
//		{画像パス,														分割総数,	分割数(x,y),	サイズ}
// 赤
struct THOUGHTLESS_WORD redTW[GIRON_MAX][TW_NUM] = {
	// 1回目の偽証議論
	{
		{"res/thoughtless_words/giron1/red_thoughtless_words.png",		6 * 1,	6, 1,		200, 200},
	},
	// 2回目の偽証議論
	{
		{"res/thoughtless_words/giron2/barizougon_R1.png",				10 * 1,	10, 1,		200, 200},
		{"res/thoughtless_words/giron2/barizougon_R2.png",				6 * 1,	6, 1,		200, 200},
	},
	// 3回目の偽証議論
	{
		{"res/thoughtless_words/giron3/barizougon_R.png",				9 * 1,	9, 1,		200, 200},
	},
	// 4回目の偽証議論
	{
		{"res/thoughtless_words/giron4/barizougon_R1.png",				10 * 1,	10, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_R2.png",				10 * 1,	10, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_R3.png",				9 * 1,	9, 1,		200, 200},
	},
	// 5回目の偽証議論
	{
		{"res/thoughtless_words/giron5/barizougon_R1.png",				8 * 1,	8, 1,		200, 200},
		{"res/thoughtless_words/giron5/barizougon_R2.png",				10 * 1,	10, 1,		200, 200},
	},
	// 6回目の偽証議論
	{
		
	}
};
// 緑
struct THOUGHTLESS_WORD greenTW[GIRON_MAX][TW_NUM] = {
	{

	},
	{
		{"res/thoughtless_words/giron2/barizougon_G1.png",				5 * 1,	5, 1,		200, 200},
		{"res/thoughtless_words/giron2/barizougon_G2.png",				9 * 1,	9, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron3/barizougon_G.png",				4 * 1,	4, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron4/barizougon_G1.png",				3 * 1,	3, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_G2.png",				8 * 1,	8, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_G3.png",				9 * 1,	9, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron5/barizougon_G1.png",				8 * 1,	8, 1,		200, 200},
	},
	{

	}
};
// 黄
struct THOUGHTLESS_WORD yellowTW[GIRON_MAX][TW_NUM] = {
	{
		{"res/thoughtless_words/giron1/yellow_thoughtless_words.png",	11 * 1,	11, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron2/barizougon_Y1.png",				9 * 1,	9, 1,		200, 200},
		{"res/thoughtless_words/giron2/barizougon_Y2.png",				10 * 1,	10, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron3/barizougon_Y.png",				10 * 1,	10, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron4/barizougon_Y1.png",				9 * 1,	9, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_Y2.png",				10 * 1,	10, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_Y3.png",				6 * 1,	6, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron5/barizougon_Y1.png",				10 * 1,	10, 1,		200, 200},
		{"res/thoughtless_words/giron5/barizougon_Y2.png",				10 * 1,	10, 1,		200, 200},
	},
	{

	}
};
// 青
struct THOUGHTLESS_WORD blueTW[GIRON_MAX][TW_NUM] = {
	{
		{"res/thoughtless_words/giron1/blue_thoughtless_words.png",		8 * 1,	8, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron2/barizougon_B1.png",				9 * 1,	9, 1,		200, 200},
		{"res/thoughtless_words/giron2/barizougon_B2.png",				9 * 1,	9, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron3/barizougon_B.png",				4 * 1,	4, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron4/barizougon_B1.png",				10 * 1,	10, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_B2.png",				9 * 1,	9, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_B3.png",				7 * 1,	7, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron5/barizougon_B1.png",				10 * 1,	10, 1,		200, 200},
		{"res/thoughtless_words/giron5/barizougon_B2.png",				10 * 1,	10, 1,		200, 200},
	},
	{

	}
};
// ピンク
struct THOUGHTLESS_WORD pinkTW[GIRON_MAX][TW_NUM] = {
	{
		{"res/thoughtless_words/giron1/pink_thoughtless_words.png",		3 * 1,	3, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron2/barizougon_P1.png",				10 * 1,	10, 1,		200, 200},
		{"res/thoughtless_words/giron2/barizougon_P2.png",				10 * 1,	10, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron3/barizougon_P.png",				6 * 1,	6, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron4/barizougon_P1.png",				7 * 1,	7, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_P2.png",				6 * 1,	6, 1,		200, 200},
		{"res/thoughtless_words/giron4/barizougon_P3.png",				7 * 1,	7, 1,		200, 200},
	},
	{
		{"res/thoughtless_words/giron5/barizougon_P1.png",				9 * 1,	9, 1,		200, 200},
		{"res/thoughtless_words/giron5/barizougon_P2.png",				7 * 1,	7, 1,		200, 200},
	},
	{

	}
};
// セツナ（自傷議論）
struct THOUGHTLESS_WORD setsunaTW[GIRON_MAX][TW_NUM] = {
	{

	},
	{

	},
	{

	},
	{

	},
	{

	},
	{
		{"res/thoughtless_words/giron6/barizougon_S1.png",		5 * 1,	5, 1,		200, 200},
		{"res/thoughtless_words/giron6/barizougon_S2.png",		5 * 1,	5, 1,		200, 200},
		{"res/thoughtless_words/giron6/barizougon_S3.png",		4 * 1,	4, 1,		200, 200},
		{"res/thoughtless_words/giron6/barizougon_S4.png",		6 * 1,	6, 1,		200, 200},
		{"res/thoughtless_words/giron6/barizougon_S5.png",		6 * 1,	6, 1,		200, 200},
		{"res/thoughtless_words/giron6/barizougon_S6.png",		9 * 1,	9, 1,		200, 200},
		{"res/thoughtless_words/giron6/barizougon_S7.png",		3 * 1,	3, 1,		200, 200},
	}
};

// 画像
// 1次元目（GIRON_MAX）は偽証議論回数
// 2次元目（TW_NUM）はその議論で使用する暴言の種類
// 3次元目（TW_LENGTH）は―文字の画像
int cgRedThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// 赤
int cgGreenThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// 緑
int cgYellowThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// 黄
int cgBlueThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// 青
int cgPinkThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];		// ピンク
int cgSetsunaThoughtlessWords[GIRON_MAX][TW_NUM][TW_LENGTH];	// セツナ（自傷議論）

int cgCounter;	//反論への遷移(土台)
int cgCounter_x;	//反論への遷移(ｘボタン)

int cgCutIn[30];	// カットイン

int cgPlayguide;		//操作説明

int cgGironButtonUI;	// 議論パートボタンUI
int cgHanronButtonUI;	// 反論パートボタンUI

// 反論パート
// 
// 1次元目（GIRON_MAX）は偽証議論回数
// 2次元目（ENEMY_MAX）は審議会メンバーの種類（0：赤, 1：緑, 2：黄, 3：青, 4：ピンク）
// 3次元目（TESTIMONY_MAX）は1議論での発言数
int cgStockCard[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX];		// 取得カードの画像
int cgCounterCard[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX];		// 反論カードの画像

int cgReturnCard[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX];		// 反転カードの画像

// 正解データテーブル
struct ANSWER_CARD tblAnsCard[] = {
	// answerNum,		ansCardCnt,
	// 審議会委員の番号, 	何番目の発言,
	{	4,				0},
	{	2,				0},
	{	0,				0},
	{	-1,				-1},
	{	1,				1},
	{	2,				0},
};
int tblACSize = sizeof(tblAnsCard) / sizeof(tblAnsCard[0]);		// 正解データテーブルサイズ

// 取得前の手札配置の画像（黒）・取得直後の手札配置の画像（白）
int cgStockBrankCard;
int cgStockWhiteCard;

// 裏返し用画像
std::vector<int> cgTurnCard;

int deckMax[GIRON_MAX] = { 2, 3, 4, 0, 4, 5 };		// 各偽証議論での手札の所持可能最大数

// 反論パート正解時エフェクト
std::vector<int> cgEndEffect;			// 偽証議論
std::vector<int> cgJisyou_EndEffect;	// 自傷議論

// 間違った場合の画像
int cgHanronMiss;		// 偽証議論
int cgJishouHanronMiss;	// 自傷議論

//
// SE・BGM
//

// ---タイトル---
int seTitleBGM;	// BGM

// ---会話パート---
int seBGM[5];	// BGM

// ---怪しい箇所を睨むパート---
int seLookClear;	// 
int seLookDamage;	// ダメージ
int seLookHazure;	// ハズレ
int seLookSeikai;	// 正解
int seLookBGM;		// BGM

// ---偽証議論パート---
//音声
int seDamage; //ダメージ音
int seBGM1; //BGM1
int seBGM2; //BGM2
int seTestimonyBreak; //証言ガード時
int seGetTestimony; //証言取得時
int seCardGathering; //証言移動時
int seCardOpening; //証言展開時
int seCardSelecting; //証言選択変更
int seHazure; //偽証言選択時
int seCutin; //カットイン時
int seCardTurning; //証言反転時
int seHitTestimony; //正解証言ヒット時
int seGard;//暴言ガード時
int seRedLaugh;		// 赤笑い声
int seGreenLaugh;	// 緑笑い声
int seYellowLaugh;	// 黄笑い声
int seBlueLaugh;	// 青笑い声
int sePinkLaugh;	// ピンク笑い声
int seSetsunaRough;	// セツナ笑い声
int seSay;			//セリフ音
int seCutinVoice;	// カットインボイス
int seDecide;		//決定音
int seCursor;		//カーソル音

// ---自傷推理---
int jisyou_cgBg[72];
int se_choiceBGM[6];

// ---クレジット---
int _cgBgCredit;
int seCregit;

// ---ゲームオーバー画面---
int seGameOverBGM;	// BGM

//
// エフェクト
//

int cgEffect[EFFECT_TYPE_MAX][16];	// ダメージエフェクト

// 防御エフェクト
int LockEffect[5][11];

int gateReset[10];
