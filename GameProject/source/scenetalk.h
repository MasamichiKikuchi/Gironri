#pragma once

#include	"scenebase.h"
#include	"gamemain.h"
#include	"UI.h"
#include	"Player.h"
#include	"effect.h"
#include	<iostream>
#include	<vector>
#include	<string>
#include	<fstream>
#include	"nlohmann/json.hpp"

#define CHOICE_MAX		(5)			//選択肢の最大
#define	DRAW_STRING_COUNT	(4)		// 描画タイミングのカウンタ
#define	DRAW_EFFECT_COUNT	(4)		// エフェクトのカウンタ
#define	FRASH_MAX_NUM	(20)		// フラッシュの時間

class SceneTalk : public SceneBase {
public:
	SceneTalk(int chapter);				// コンストラクタ
	virtual ~SceneTalk();		// デストラクタ

	void Input() override;		// 入力
	void Process() override;	// 計算
	void Draw() override;		// 描画

	void savemessage();			//ログ用のメッセージの保存
	// clace読み込み
	Player player;
	UI ui;
protected:
	int _cgBg;			// 背景画像
	int cgchoice[2];	// 選択肢背景 0:内側 1:外側
	int cg_popup;		// ポップアップ
	int cg_chara;
	int cg_UI_talk;

	// アニメーション
	// 0:キイロ 1:青

	int animcnt;
	int animflg;
	int animnum;		// 0:キイロ 1:青

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
	JsonData _jsonData[JSON_MAX];

	//エフェクト関連
	int effectcnt;
	int flashcnt;
	int flash_alpha;

	//テキスト送り画像関係
	int text_alpha;
	int cgtext;
	int add;
	int text_flg;		//テキスト画像の出現フラグ
	//アイテムポップアップ
	int popupflg;
	float popup_size;

	int messagecnt;	//Jsonの読み込みカウント

	int save_messagecnt[CHOICE_MAX];	//選択肢用のカウント保存

	int shakeflg;		//シェイク中かフラグ

	//se関連
	int se_next;
	int se_choice;
	int se_voice;
	int se_selectchoice;

	int savechapter;		//現在のチャプター保存

	int selectcnt;	//現在選んでいる選択肢
	int selectflg;

	//会話カウント
	int drawCnt1;
	int drawCnt2;
	std::string drawMessage1;				// 描画する文字列（1行）
	std::string drawMessage2;				// 描画する文字列（1行）

	//アニメーション名格納用
	std::string Anim0;
	std::string Anim1;
	std::string Anim2;
	std::string Anim3;
	std::string Anim4;

	//BGM名格納用
	std::string BGM0;
	std::string BGM1;
	std::string BGM2;
	std::string BGM3;
	std::string BGM4;

	int gameCnt;	// 会話パートのゲームカウンタ
	int step;		// フェードインアウト用ステップ

	// エフェクト
	Effect gEffect;
};
