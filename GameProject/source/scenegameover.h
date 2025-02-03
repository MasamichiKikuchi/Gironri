#pragma once

#include	"scenebase.h"
#include	"UI.h"
#include	"gamemain.h"
#include	"Player.h"
#include	<iostream>
#include	<vector>
#include	<string>
#include	<fstream>
#include	"nlohmann/json.hpp"

#define GAMEOVER_CHOICE_MAX		(2)			//選択肢の最大


class SceneGameover : public SceneBase {
public:
	SceneGameover(int chapter);				// コンストラクタ
	virtual ~SceneGameover();		// デストラクタ

	void Input() override;		// 入力
	void Process() override;	// 計算
	void Draw() override;		// 描画

	// clace読み込み
	UI ui;
protected:
	int _cgBg[2];			// 背景画像

	// jsonから読み込んだデータ
	struct JsonData {
		std::string draw;
		int drawX, drawY;
		std::string name;
		std::string message1;
		std::string message2;
		//std::string se;

		// ゲームオーバー用コマンド
		// 2:選択「タイトルに戻る」の処理 3:選択「リトライ」の処理
		// 4:ゲームオーバー画像表示
		// 21:背景を少し暗く 22:背景をさらに暗く 23:背景を暗く 24:フラッシュ
		// 51~、61~：戻る場所
		int command;
	};
	JsonData _jsonData[JSON_MAX];

	//エフェクト関連
	int effectcnt;
	int break_efffect[45];

	//テキスト送り
	int text_alpha;
	int cgtext;
	int add;
	int text_flg;		//テキスト画像の出現フラグ


	int messagecnt;	//Jsonの読み込みカウント

	int save_messagecnt[GAMEOVER_CHOICE_MAX];	//選択肢用のカウント保存

	//se
	int se_next;
	int se_choice;

	int savechapter;		//現在のチャプター保存

	int selectcnt;	//現在選んでいる選択肢

	//会話カウント
	int drawCnt1;
	int drawCnt2;
	std::string drawMessage1;				// 描画する文字列（1行）
	std::string drawMessage2;				// 描画する文字列（1行）

	int gameCnt;	// 会話パートのゲームカウンタ


	//ゲームオーバー用追加変数
	int gameoverflg;		//ゲームオーバーフラグ
	int cgarrow;		//選択用矢印
};
