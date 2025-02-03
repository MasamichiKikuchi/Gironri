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
	
	// �O���[�o���f�[�^�̃��[�h
	SetUseASyncLoadFlag(TRUE);	// �񓯊��ǂݍ��݂��s��
	gGlobal->Load();
	SetUseASyncLoadFlag(FALSE);	// �񓯊��ǂݍ��݂��I������

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
	// ���S1�J�n
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
			stepCnt = 0;
		}
		break;
	case 2:
		// �ʏ폈��
		stepCnt++;
		if (stepCnt > 60)
		{
			// �t�F�[�h�A�E�g�J�n
			ColorFadeOut(0, 0, 0, 60);
			stepCnt = 0;
			step++;
		}
		break;
	//���S2�J�n
	case 3:
		if (IsColorFade() == 0)
		{
			// �t�F�[�h�C���J�n
			ColorFadeIn(60);
			step++;
		}
		break;
	case 4:
		if (IsColorFade() == 0)
		{
			// �t�F�[�h�C���I��
			step++;
			stepCnt = 0;
		}
		break;
	case 5:
		// �ʏ폈��
		stepCnt++;
		if (stepCnt > 60)
		{
			// �t�F�[�h�A�E�g�J�n
			ColorFadeOut(0, 0, 0, 60);
			stepCnt = 0;
			step++;
		}
		break;
	case 6:
		if (IsColorFade() == 0)
		{
			// �t�F�[�h�A�E�g�I��
			SceneBase* scene = new SceneGameTitle();
			ChangeScene(scene);
		}
		break;
	}

	// �J���[�}�X�N�̃t�F�[�h�C���A�E�g����
	ColorFadeProcess();
}

void SceneInit::Draw()
{
	// ���S�\���i0�F�`�[��, 1�FAMG�j
	if (step > 3)
	{
		DrawGraph(0, 0, cgBg[0], FALSE);
	}
	else
	{
		DrawGraph(0, 0, cgBg[1], FALSE);
	}

	// �J���[�}�X�N�̃t�F�[�h�C���A�E�g�`��
	ColorFadeDraw();
}
