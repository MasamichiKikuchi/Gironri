#include	"scenegametitle.h"
#include	"DxLib.h"
#include	"winmain.h"
#include	"gamemain.h"
#include	"scenegamemain.h"
#include	"SceneLastChoice.h"
#include	"scenetalk.h"
#include	"scenelook.h"
#include	"mymath.h"
#include	"SceneCredit.h"
#include	"scenegametutorial.h"
#include	"SceneGameover.h"

SceneGameTitle::SceneGameTitle()
{
	_cgBg = LoadGraph("res/title/CG_start.png");
	_cgBgUI = LoadGraph("res/title/CG_start_UI.png");
	alpha = 0;
	frame = 0;
	pushKeyFlag = 0;
	step = 0;
	gHP = MAX_HP;		//体力を全回復
	reHP = MAX_HP;
	lastchoice_skipflg = 0;

	//　全てのlogsaveを消す
	for (int i = 0; i < MAX_LOGSAVE; i++) {
		logsave[i].use = 0;
	}

	PlaySoundMem(seTitleBGM, DX_PLAYTYPE_LOOP);
}

SceneGameTitle::~SceneGameTitle()
{
	DeleteGraph(_cgBg);
	DeleteGraph(_cgBgUI);
	if (CheckSoundMem(seTitleBGM)) { StopSoundMem(seTitleBGM); }
}

void SceneGameTitle::Input()
{
	// 何もしない
}

void SceneGameTitle::Process()
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
			//キーが押された
			if (pushKeyFlag == 1)
			{
				//高速で点滅
				alpha = EasingInOutSine(frame, 0.0f, 255.0f, 4.0f);
				//一定フレーム経過したら
				if (frame >= 28)
				{
					// フェードアウト開始
					ColorFadeOut(0, 0, 0, 60);
					step++;
				}
			}
			//キーが押されていない
			else
			{
				//ゆっくり点滅
				alpha = EasingInOutSine(frame, 0.0f, 255.0f, 100.0f);
			}
			
			// 読み込みが終了しているのでキー入力を受け付ける
			if (gPad.gTrg & PAD_INPUT_2 && pushKeyFlag == 0)
			{
				//フレーム数リセット
				frame = 0;
				//キーが押された
				pushKeyFlag = 1;
				PlaySoundMem(seDecide, DX_PLAYTYPE_BACK);
			}
			//フレーム数加算
			frame += 1.0f;
		}
		break;
	case 3:
		//高速で点滅
		alpha = EasingInOutSine(frame, 0.0f, 255.0f, 3.0f);
		//フレーム数加算
		frame += 1.0f;
		if (IsColorFade() == 0)
		{
			// フェードアウト終了
			
			//SceneBase* scene = new SceneTalk(99);
			SceneBase* scene = new SceneGameMain(5);
			ChangeScene(scene);
		}
	}

	// カラーマスクのフェードインアウト処理
	ColorFadeProcess();
}

void SceneGameTitle::Draw()
{
	//背景
	DrawGraph(0, 0, _cgBg, FALSE);
	//文字
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(700, 835, _cgBgUI, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明描画指定

	// カラーマスクのフェードインアウト描画
	ColorFadeDraw();
}
