#include	"DxLib.h"
#include	"winmain.h"
#include	"gamemain.h"
#include	"scenebase.h"
#include	"sceneinit.h"
#include	"data.h"
#include	"mymath.h"


// ゲーム情報
GamePad gPad;
// グローバル情報
Global* gGlobal;

int gHP;			// 主人公HP
int reHP;
int gameChapter;	// ゲーム章番号

// Sceneポインタ
SceneBase* gScene;					// ポインタなのでnewするまで実体は無い

// Sceneの切り替え用
SceneBase* gNewScene;				// NULL以外がセットされていたら、シーンを切り替える

// Sceneの変更
void ChangeScene(SceneBase* scene)
{
	gNewScene = scene;		// 次のSceneをセット
}

int lastchoice_skipflg = 0;

//ログ
int logflg;	//ログ中か確認のフラグ
int log_y;	//ログのY座標
int logcnt;

struct messageLog logsave[MAX_LOGSAVE];

//ログ表示中の処理
void LogProcess()
{
	//ログの処理
	int n = 0;
	for (int i = 0; i < MAX_LOGSAVE; i++) {
		if (logsave[i].use == 1) {
			n++;
		}
		else
		{
			break;
		}
	}
	int messagebt = 300;	//一言ごとの間隔
	int speed = 12;			//スクロールの速さ
	if (gPad.gKey & PAD_INPUT_2) {
		logcnt++;
		if (logcnt > 60) {
			speed = 30 + ((logcnt - 60) * 2);	//ボタンを長押しspeedをだんだん早く
		}
		else
		{
			speed = 30;
		}
	}
	else
	{
		logcnt = 0;
	}
	if (gPad.gKey & PAD_INPUT_DOWN) { log_y -= speed; }							//下ボタンスクロール
	if (gPad.gKey & PAD_INPUT_UP) { log_y += speed; }							//上ボタンスクロール
	if (log_y > 0) { log_y = 0; logcnt = 0; }												//スクロール上限
	if ((-n * messagebt) + 850 > log_y) { log_y = (-n * messagebt) + 850; logcnt = 0; }		//スクロール下限
}
//ログ表示中の描画
void LogDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	int savefontsize;
	savefontsize = GetFontSize();	//元のフォントサイズを保存
	int massagefontsize = 62;		//フォントサイズ
	int bt = 10;					//行間
	int namefontsize = 48;
	int messagebt = 300;
	//メッセージ描画
	for (int i = 0; i < MAX_LOGSAVE; i++) {
		if (logsave[i].use == 1) {
			if (((i * messagebt) + log_y < SCREEN_H) && (massagefontsize + massagefontsize + bt + (i * messagebt) + log_y > 0)) {
				SetFontSize(namefontsize);
				DrawFormatString(150, 40 + (i * messagebt) + log_y, GetColor(255, 255, 255), logsave[i].name.c_str());
				SetFontSize(massagefontsize);
				DrawFormatString(400, (i * messagebt) + log_y, GetColor(255, 255, 255), logsave[i].message1.c_str());							//一行目
				DrawFormatString(400, massagefontsize + bt + (i * messagebt) + log_y, GetColor(255, 255, 255), logsave[i].message2.c_str());	//二行目
			}
		}
		else
		{
			break;
		}
	}
	SetFontSize(savefontsize);	//フォントサイズを戻す
}

//ログの使用状況を変更
void LogChange()
{
	logflg = 1 - logflg;		//ログフラグの反転
	int messagebt = 300;	//一言ごとの間隔
	int n = 0;
	for (int i = 0; i < MAX_LOGSAVE; i++) {
		if (logsave[i].use == 1) { n++; }
		else { break; }
	}
	log_y = (-n * messagebt) + 850;	//初期位置の設定
}

// カラーマスク用
int gColorMaskR = 0, gColorMaskG = 0, gColorMaskB = 0, gColorMaskA = 0;
// 指定の色をカラーマスク
void ColorMask(int colorR, int colorG, int colorB, int colorA)
{
	gColorMaskR = colorR;
	gColorMaskG = colorG;
	gColorMaskB = colorB;
	gColorMaskA = colorA;
}

// フェードインアウト用
int gColorFadeStR, gColorFadeStG, gColorFadeStB, gColorFadeStA;
int gColorFadeEdR, gColorFadeEdG, gColorFadeEdB, gColorFadeEdA;
int gFadeFrames = 0, gFadeCnt = 0;
// 指定の色にフェードアウト（カラーマスク使用, alpha = 255 にする）
void ColorFadeOut(int colorR, int colorG, int colorB, int frames)
{
	// フェード開始値
	gColorFadeStR = gColorMaskR;
	gColorFadeStG = gColorMaskG;
	gColorFadeStB = gColorMaskB;
	gColorFadeStA = gColorMaskA;
	// フェード到達値
	gColorFadeEdR = colorR;
	gColorFadeEdG = colorG;
	gColorFadeEdB = colorB;
	gColorFadeEdA = 255;
	// フェードカウンタ
	gFadeFrames = frames;
	gFadeCnt = 0;
}
// 現在のカラーマスクからフェードイン（カラーマスク使用, alpha = 0 にする）
void ColorFadeIn(int frames)
{
	// フェード開始値
	gColorFadeStR = gColorMaskR;
	gColorFadeStG = gColorMaskG;
	gColorFadeStB = gColorMaskB;
	gColorFadeStA = gColorMaskA;
	// フェード到達値
	gColorFadeEdR = gColorMaskR;
	gColorFadeEdG = gColorMaskG;
	gColorFadeEdB = gColorMaskB;
	gColorFadeEdA = 0;
	// フェードカウンタ
	gFadeFrames = frames;
	gFadeCnt = 0;
}

// フェードインアウトは終了したか？
// 戻り値: 1 = フェード中, 0 = フェード終了（もしくは開始前）
int IsColorFade()
{
	if (gFadeCnt < gFadeFrames)
	{
		return 1;
	}
	return 0;
}

// カラーマスクのフェードインアウト処理
void ColorFadeProcess()
{
	if (IsColorFade() != 0)
	{
		gFadeCnt++;
		gColorMaskR = EasingLinear(gFadeCnt, gColorFadeStR, gColorFadeEdR, gFadeFrames);
		gColorMaskG = EasingLinear(gFadeCnt, gColorFadeStG, gColorFadeEdG, gFadeFrames);
		gColorMaskB = EasingLinear(gFadeCnt, gColorFadeStB, gColorFadeEdB, gFadeFrames);
		gColorMaskA = EasingLinear(gFadeCnt, gColorFadeStA, gColorFadeEdA, gFadeFrames);
	}
}

// カラーマスクのフェードインアウト描画
void ColorFadeDraw()
{
	if (gColorMaskA > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, gColorMaskA);	// 半透明モード
		DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(gColorMaskR, gColorMaskG, gColorMaskB), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, gColorMaskA);
	}
}

// アプリの初期化
// 起動時に1回だけ実行される
void AppInit() {
	//----------------フォント読み込み----------------------------
	//
	LPCSTR font_path = "res/font/Corporate-Mincho-ver3.otf"; // 読み込むフォントファイルのパス
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}

	// ********** ここから読み込んだフォントを利用できる **********
	ChangeFont("コーポレート明朝 ver3 Medium", DX_CHARSET_DEFAULT);

	//----------------------------------------------------------

	gHP = MAX_HP;
	gameChapter = 0;

	gGlobal = new Global();				// グローバル情報の作成

	gNewScene = NULL;					// 次のSceneを初期化する
	gScene = new SceneInit();		// Sceneの実態を作る
}


// アプリの解放
// 終了時に1回だけ実行される
void AppRelease() {
	delete gScene;			// Sceneを削除する
	delete gGlobal;			// グローバル情報の削除
}

//
// フレーム処理。1フレームに1回ずつ実行される
//

// フレーム処理：入力
void FrameInput() {
	// キー入力、トリガ入力、リリース入力、pad1の入力値を得る
	gPad.Input();

	// Sceneの入力呼び出し
	gScene->Input();
}

// フレーム処理：計算
void FrameProcess() {
	// Sceneの計算呼び出し
	gScene->Process();
}

// フレーム処理：描画
void FrameDraw() {

	ClearDrawScreen();						// 画面を初期化する

	// Sceneの描画呼び出し
	gScene->Draw();
	//開発用
	int massagefontsize = 32;		//フォントサイズ
	int savefontsize;
	savefontsize = GetFontSize();
	SetFontSize(savefontsize);

	ScreenFlip();							// 裏画面の内容を表画面に反映させる
}

bool Update() {
	if (mCount == 0) { //1フレーム目なら時刻を記憶
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60フレーム目なら平均を計算する
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void Wait() {
	int tookTime = GetNowCount() - mStartTime;	//かかった時間
	int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
	if (waitTime > 0) {
		Sleep(waitTime);	//待機
	}
}

void GameMain()
{
	AppInit();	// 初期化

	// 1フレームループを組む ----------------------------------------------------------
	while (ProcessMessage() == 0)		// プログラムが終了するまでループ
	{
		// シーンを切り替えるか？
		if (gNewScene != NULL) {
			delete gScene;		// 今のシーンを削除する
			gScene = gNewScene;	// 受け取ったシーンをポインタセット
			gNewScene = NULL;	// 次のシーンを初期化する
		}
		
		FrameInput();	// 入力
		FrameProcess();	// 計算
		FrameDraw();	// 描画
		Update();		//更新
		Wait();			//FPS固定
	}

	AppRelease();	// 解放
}
