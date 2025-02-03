#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない

#include	"scenebase.h"
#include	"gamepad.h"
#include	"data.h"
#include	"global.h"

#define MAX_HP		(100 * 6)		//最大HP
#define RECOVERY_HP		(100)		//偽証議論終わりのHP回復値
#define TALK_MISS_HP		(10)	//選択肢間違えたHP減少値
#define MAX_LOGSAVE		(9999)		//バックログの最大保存数
#define JSON_MAX		(999)		// JSON用配列の最大

// ゲーム情報
extern GamePad gPad;			// ゲームパッドの情報
extern Global* gGlobal;

extern int gHP;					// HP
extern int reHP;
extern int gameChapter;			// 章番号

//FPS固定
static int mStartTime;      //測定開始時刻
static int mCount;          //カウンタ
static float mFps;          //fps
static const int N = 60;	//平均を取るサンプル数
static const int FPS = 60;	//設定したFPS

// ログ関連
struct messageLog {
	std::string name;
	std::string message1;
	std::string message2;
	int use;
};
extern struct messageLog logsave[MAX_LOGSAVE];
extern int logflg;	//ログ中か確認のフラグ
extern int log_y;	//ログのY座標
extern int logcnt;

extern int lastchoice_skipflg;
void LogProcess();
void LogDraw();
void LogChange();

// シーン
void ChangeScene(SceneBase* scene);		// Sceneを変更する

// ---フェードイン/フェードアウト---
// カラーマスク用
extern int gColorMaskR, gColorMaskG, gColorMaskB, gColorMaskA;
// カラーマスク指定
void ColorMask(int colorR, int colorG, int colorB, int colorA);

// フェードインアウト用
extern int gColorFadeStR, gColorFadeStG, gColorFadeStB, gColorFadeStA;
extern int gColorFadeEdR, gColorFadeEdG, gColorFadeEdB, gColorFadeEdA;
extern int gFadeFrames, gFadeCnt;
// 指定の色にフェードアウト（カラーマスク使用, alpha = 255 にする）
void ColorFadeOut(int colorR, int colorG, int colorB, int frames);

// 現在のカラーマスクからフェードイン（カラーマスク使用, alpha = 0 にする）
void ColorFadeIn(int frames);

// フェードインアウトは終了したか？
// 戻り値: 1 = フェード中, 0 = フェード終了（もしくは開始前）
int IsColorFade();

// カラーマスクのフェードインアウト処理
void ColorFadeProcess();

// カラーマスクのフェードインアウト描画
void ColorFadeDraw();

// ---ゲームメイン---
void GameMain();	// gamemain.cpp に実体を記述

//FPS固定用
bool Update();
void Wait();