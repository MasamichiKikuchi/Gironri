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
	gHP = MAX_HP;		//�̗͂�S��
	reHP = MAX_HP;
	lastchoice_skipflg = 0;

	//�@�S�Ă�logsave������
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
	// �������Ȃ�
}

void SceneGameTitle::Process()
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
			//�L�[�������ꂽ
			if (pushKeyFlag == 1)
			{
				//�����œ_��
				alpha = EasingInOutSine(frame, 0.0f, 255.0f, 4.0f);
				//���t���[���o�߂�����
				if (frame >= 28)
				{
					// �t�F�[�h�A�E�g�J�n
					ColorFadeOut(0, 0, 0, 60);
					step++;
				}
			}
			//�L�[��������Ă��Ȃ�
			else
			{
				//�������_��
				alpha = EasingInOutSine(frame, 0.0f, 255.0f, 100.0f);
			}
			
			// �ǂݍ��݂��I�����Ă���̂ŃL�[���͂��󂯕t����
			if (gPad.gTrg & PAD_INPUT_2 && pushKeyFlag == 0)
			{
				//�t���[�������Z�b�g
				frame = 0;
				//�L�[�������ꂽ
				pushKeyFlag = 1;
				PlaySoundMem(seDecide, DX_PLAYTYPE_BACK);
			}
			//�t���[�������Z
			frame += 1.0f;
		}
		break;
	case 3:
		//�����œ_��
		alpha = EasingInOutSine(frame, 0.0f, 255.0f, 3.0f);
		//�t���[�������Z
		frame += 1.0f;
		if (IsColorFade() == 0)
		{
			// �t�F�[�h�A�E�g�I��
			
			//SceneBase* scene = new SceneTalk(99);
			SceneBase* scene = new SceneGameMain(5);
			ChangeScene(scene);
		}
	}

	// �J���[�}�X�N�̃t�F�[�h�C���A�E�g����
	ColorFadeProcess();
}

void SceneGameTitle::Draw()
{
	//�w�i
	DrawGraph(0, 0, _cgBg, FALSE);
	//����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(700, 835, _cgBgUI, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����`��w��

	// �J���[�}�X�N�̃t�F�[�h�C���A�E�g�`��
	ColorFadeDraw();
}
