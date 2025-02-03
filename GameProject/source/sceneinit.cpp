#include	"sceneinit.h"
#include	"DxLib.h"
#include	"winmain.h"
#include	"gamemain.h"
#include	"scenegametitle.h"
#include	"mymath.h"

SceneInit::SceneInit()
{
	cgBg[0] = LoadGraph("res/CG_teamlogo.png");
	cgBg[1] = LoadGraph("res/CG_AMG_logo.png");
	step = 0;
	
	// グローバルデータのロード
	SetUseASyncLoadFlag(TRUE);	// 非同期読み込みを行う
	gGlobal->Load();
	SetUseASyncLoadFlag(FALSE);	// 非同期読み込みを終了する

	ColorMask(0, 0, 0, 255);
}

SceneInit::~SceneInit()
{
	DeleteGraph(cgBg[0]);
	DeleteGraph(cgBg[1]);
}

void SceneInit::Input()
{

}

void SceneInit::Process()
{
	switch (step)
	{
	// ロゴ1開始
	case 0:
		// フェードイン開始
		ColorFadeIn(60);
		step++;
		break;
	case 1:
		if (IsColorFade() == 0)
		{
			// フェードイン終了
			step++;
			stepCnt = 0;
		}
		break;
	case 2:
		// 通常処理
		stepCnt++;
		if (stepCnt > 60)
		{
			// フェードアウト開始
			ColorFadeOut(0, 0, 0, 60);
			stepCnt = 0;
			step++;
		}
		break;
	//ロゴ2開始
	case 3:
		if (IsColorFade() == 0)
		{
			// フェードイン開始
			ColorFadeIn(60);
			step++;
		}
		break;
	case 4:
		if (IsColorFade() == 0)
		{
			// フェードイン終了
			step++;
			stepCnt = 0;
		}
		break;
	case 5:
		// 通常処理
		stepCnt++;
		if (stepCnt > 60)
		{
			// フェードアウト開始
			ColorFadeOut(0, 0, 0, 60);
			stepCnt = 0;
			step++;
		}
		break;
	case 6:
		if (IsColorFade() == 0)
		{
			// フェードアウト終了
			SceneBase* scene = new SceneGameTitle();
			ChangeScene(scene);
		}
		break;
	}

	// カラーマスクのフェードインアウト処理
	ColorFadeProcess();
}

void SceneInit::Draw()
{
	// ロゴ表示（0：チーム, 1：AMG）
	if (step > 3)
	{
		DrawGraph(0, 0, cgBg[0], FALSE);
	}
	else
	{
		DrawGraph(0, 0, cgBg[1], FALSE);
	}

	// カラーマスクのフェードインアウト描画
	ColorFadeDraw();
}
