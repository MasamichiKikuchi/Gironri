#pragma once

#include	"scenebase.h"
#include	"UI.h"
#include	"Player.h"
#include	"gamemain.h"
#include	<iostream>
#include	<vector>
// nlohmannでjsonを扱うテスト
// 「source/include」 をプロジェクトのプロパティ「追加のインクルードディレクトリ」に追加しておく
#include	<string>
#include	<fstream>
#include	"nlohmann/json.hpp"

#define LAST_CHOICE_MAX		(2)			//選択肢の最大

class SceneLastChoice : public SceneBase {
public:
	SceneLastChoice(int chapter);				// コンストラクタ
	virtual ~SceneLastChoice();		// デストラクタ

	void Input() override;		// 入力
	void Process() override;	// 計算
	void Draw() override;		// 描画

	void savemessage();
	void Flash();

	// clace読み込み
	Player player;
	UI ui;
protected:
	int _cgBg;
	int cgchoice[2];	// 選択肢背景 0:内側 1:外側
	int cg_popup;		// ポップアップ
	int cg_chara;
	int cgChoiceBg;
	int cgCorrectEffect[15];//正解時エフェクト
	int cg_UI_talk[2];

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

		//	コマンド系
		//	1:不正解時の文章始まり 2:選択「途中正解」の処理 3:選択「不正解」の処理 4:選択「全問正解」の処理 5:画像の縦移動 6:BGM変更 31:「不正解」時の会話
		//	21:背景を少し暗く 22:背景をさらに暗く 23:背景を暗く 24:フラッシュ 91:アイテムポップアップ始まり 92:アイテムポップアップ終わり
		//	71:タイトルへ 72:最初から
		int command;
	};
	JsonData _jsonData[JSON_MAX];

	//エフェクト関連
	int effectcnt;
	int flashcnt;
	int flash_alpha;
	int blackflg;
	int backTalkpartflg;

	//テキスト送り画像関係
	int text_alpha;
	int cgtext;
	int add;
	int text_flg;		//テキスト画像の出現フラグ

	int CorrectEffectflg;
	int CorrectEffectcnt;
	int CorrectEffectnum;

	//アイテムポップアップ
	int popupflg;
	float popup_size;

	int messagecnt;	//Jsonの読み込みカウント

	int save_messagecnt[LAST_CHOICE_MAX];	//選択肢用のカウント保存

	int canskip_UI_flg;

	//se
	int se_next;
	int se_choice;
	int se_voice;

	int savechapter;		//現在のチャプター保存

	int selectcnt;	//現在選んでいる選択肢


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
};
