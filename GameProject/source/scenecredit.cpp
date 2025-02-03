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
	// �������Ȃ�
}

void SceneCredit::Process()
{
	switch (step)
	{
	case 0:
		// �t�F�[�h�C���J�n
		ColorFadeIn(60);
		step++;
		break;
	case 1:
		if (IsColorFade() == 0)
		{
			// �t�F�[�h�C���I��
			step++;
		}
		break;
	case 2:
		// �ʏ폈��
		// �O���[�o���f�[�^�̓ǂݍ��݂͏I�����Ă��邩�H
		if (gGlobal->IsLoadFinish() != 0)
		{
			int speed;
			if (gPad.gKey & PAD_INPUT_2) { speed = -36; }
			else if (gPad.gKey & PAD_INPUT_3) { speed = 8; }
			else { speed = -4; }
			Bgy += speed;

			// �ǂݍ��݂��I�����Ă���̂ŃL�[���͂��󂯕t����
			if (Bgy < -15541 + SCREEN_H)
			{
				// �t�F�[�h�A�E�g�J�n
				ColorFadeOut(0, 0, 0, 300);
				step++;
			}
		}
		break;
	case 3:
		if (IsColorFade() == 0)
		{
			// �t�F�[�h�A�E�g�I��
			SceneBase* scene = new SceneGameTitle();
			//SceneBase* scene = new SceneGameTutorial();
			//SceneBase* scene = new SceneTalk(99);
			ChangeScene(scene);
		}
	}

	// �J���[�}�X�N�̃t�F�[�h�C���A�E�g����
	ColorFadeProcess();
}

void SceneCredit::Draw()
{
	DrawGraph(0, Bgy, _cgBgCredit, FALSE);

	//DrawFormatString(100, 100, GetColor(255, 255, 255), "Bgy:%d",Bgy);

	// �O���[�o���f�[�^�̓ǂݍ��݂͏I�����Ă��邩�H
	if (gGlobal->IsLoadFinish() != 0)
	{
		// �ǂݍ��݂��I�����Ă���̂ŃL�[���͂��󂯕t����
		//DrawFormatString(500, 600, GetColor(rand() % 256, rand() % 256, rand() % 256), "Finished Load!! Push Any Button!!");
	}
	else
	{
		// �ǂݍ��ݒ�,,,���[�h�f�[�^�̎c�萔��\��
		//DrawFormatString(500, 600, GetColor(255, 255, 255), "Now Loading...( %d )", GetASyncLoadNum());
	}

	// �J���[�}�X�N�̃t�F�[�h�C���A�E�g�`��
	ColorFadeDraw();
}
