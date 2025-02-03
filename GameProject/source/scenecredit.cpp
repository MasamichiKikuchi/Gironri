#include	"SceneCredit.h"
#include	"DxLib.h"
#include	"winmain.h"
#include	"gamemain.h"
#include	"scenegamemain.h"
#include	"scenegametitle.h"
#include	"SceneLastChoice.h"
#include	"scenetalk.h"
#include	"scenelook.h"
#include	"mymath.h"
#include	"scenegametutorial.h"

SceneCredit::SceneCredit()
{
	step = 0;
	Bgy = SCREEN_H;
	PlaySoundMem(seCregit, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(255 * BGM_VOLUME / 100, seCregit);
}

SceneCredit::~SceneCredit()
{
	if (CheckSoundMem(seCregit)) { StopSoundMem(seCregit); }
}

void SceneCredit::Input()
{
	// 何もしない
}

void SceneCredit::Process()
{
	switch (step)
	{
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
		}
		break;
	case 2:
		// 通常処理
		// グローバルデータの読み込みは終了しているか？
		if (gGlobal->IsLoadFinish() != 0)
		{
			int speed;
			if (gPad.gKey & PAD_INPUT_2) { speed = -36; }
			else if (gPad.gKey & PAD_INPUT_3) { speed = 8; }
			else { speed = -4; }
			Bgy += speed;

			// 読み込みが終了しているのでキー入力を受け付ける
			if (Bgy < -15541 + SCREEN_H)
			{
				// フェードアウト開始
				ColorFadeOut(0, 0, 0, 300);
				step++;
			}
		}
		break;
	case 3:
		if (IsColorFade() == 0)
		{
			// フェードアウト終了
			SceneBase* scene = new SceneGameTitle();
			//SceneBase* scene = new SceneGameTutorial();
			//SceneBase* scene = new SceneTalk(99);
			ChangeScene(scene);
		}
	}

	// カラーマスクのフェードインアウト処理
	ColorFadeProcess();
}

void SceneCredit::Draw()
{
	DrawGraph(0, Bgy, _cgBgCredit, FALSE);

	//DrawFormatString(100, 100, GetColor(255, 255, 255), "Bgy:%d",Bgy);

	// グローバルデータの読み込みは終了しているか？
	if (gGlobal->IsLoadFinish() != 0)
	{
		// 読み込みが終了しているのでキー入力を受け付ける
		//DrawFormatString(500, 600, GetColor(rand() % 256, rand() % 256, rand() % 256), "Finished Load!! Push Any Button!!");
	}
	else
	{
		// 読み込み中,,,ロードデータの残り数を表示
		//DrawFormatString(500, 600, GetColor(255, 255, 255), "Now Loading...( %d )", GetASyncLoadNum());
	}

	// カラーマスクのフェードインアウト描画
	ColorFadeDraw();
}
