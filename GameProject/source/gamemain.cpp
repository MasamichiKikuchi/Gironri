#include	"DxLib.h"
#include	"winmain.h"
#include	"gamemain.h"
#include	"scenebase.h"
#include	"sceneinit.h"
#include	"data.h"
#include	"mymath.h"


// �Q�[�����
GamePad gPad;
// �O���[�o�����
Global* gGlobal;

int gHP;			// ��l��HP
int reHP;
int gameChapter;	// �Q�[���͔ԍ�

// Scene�|�C���^
SceneBase* gScene;					// �|�C���^�Ȃ̂�new����܂Ŏ��͖̂���

// Scene�̐؂�ւ��p
SceneBase* gNewScene;				// NULL�ȊO���Z�b�g����Ă�����A�V�[����؂�ւ���

// Scene�̕ύX
void ChangeScene(SceneBase* scene)
{
	gNewScene = scene;		// ����Scene���Z�b�g
}

int lastchoice_skipflg = 0;

//���O
int logflg;	//���O�����m�F�̃t���O
int log_y;	//���O��Y���W
int logcnt;

struct messageLog logsave[MAX_LOGSAVE];

//���O�\�����̏���
void LogProcess()
{
	//���O�̏���
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
	int messagebt = 300;	//�ꌾ���Ƃ̊Ԋu
	int speed = 12;			//�X�N���[���̑���
	if (gPad.gKey & PAD_INPUT_2) {
		logcnt++;
		if (logcnt > 60) {
			speed = 30 + ((logcnt - 60) * 2);	//�{�^���𒷉���speed�����񂾂񑁂�
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
	if (gPad.gKey & PAD_INPUT_DOWN) { log_y -= speed; }							//���{�^���X�N���[��
	if (gPad.gKey & PAD_INPUT_UP) { log_y += speed; }							//��{�^���X�N���[��
	if (log_y > 0) { log_y = 0; logcnt = 0; }												//�X�N���[�����
	if ((-n * messagebt) + 850 > log_y) { log_y = (-n * messagebt) + 850; logcnt = 0; }		//�X�N���[������
}
//���O�\�����̕`��
void LogDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	int savefontsize;
	savefontsize = GetFontSize();	//���̃t�H���g�T�C�Y��ۑ�
	int massagefontsize = 62;		//�t�H���g�T�C�Y
	int bt = 10;					//�s��
	int namefontsize = 48;
	int messagebt = 300;
	//���b�Z�[�W�`��
	for (int i = 0; i < MAX_LOGSAVE; i++) {
		if (logsave[i].use == 1) {
			if (((i * messagebt) + log_y < SCREEN_H) && (massagefontsize + massagefontsize + bt + (i * messagebt) + log_y > 0)) {
				SetFontSize(namefontsize);
				DrawFormatString(150, 40 + (i * messagebt) + log_y, GetColor(255, 255, 255), logsave[i].name.c_str());
				SetFontSize(massagefontsize);
				DrawFormatString(400, (i * messagebt) + log_y, GetColor(255, 255, 255), logsave[i].message1.c_str());							//��s��
				DrawFormatString(400, massagefontsize + bt + (i * messagebt) + log_y, GetColor(255, 255, 255), logsave[i].message2.c_str());	//��s��
			}
		}
		else
		{
			break;
		}
	}
	SetFontSize(savefontsize);	//�t�H���g�T�C�Y��߂�
}

//���O�̎g�p�󋵂�ύX
void LogChange()
{
	logflg = 1 - logflg;		//���O�t���O�̔��]
	int messagebt = 300;	//�ꌾ���Ƃ̊Ԋu
	int n = 0;
	for (int i = 0; i < MAX_LOGSAVE; i++) {
		if (logsave[i].use == 1) { n++; }
		else { break; }
	}
	log_y = (-n * messagebt) + 850;	//�����ʒu�̐ݒ�
}

// �J���[�}�X�N�p
int gColorMaskR = 0, gColorMaskG = 0, gColorMaskB = 0, gColorMaskA = 0;
// �w��̐F���J���[�}�X�N
void ColorMask(int colorR, int colorG, int colorB, int colorA)
{
	gColorMaskR = colorR;
	gColorMaskG = colorG;
	gColorMaskB = colorB;
	gColorMaskA = colorA;
}

// �t�F�[�h�C���A�E�g�p
int gColorFadeStR, gColorFadeStG, gColorFadeStB, gColorFadeStA;
int gColorFadeEdR, gColorFadeEdG, gColorFadeEdB, gColorFadeEdA;
int gFadeFrames = 0, gFadeCnt = 0;
// �w��̐F�Ƀt�F�[�h�A�E�g�i�J���[�}�X�N�g�p, alpha = 255 �ɂ���j
void ColorFadeOut(int colorR, int colorG, int colorB, int frames)
{
	// �t�F�[�h�J�n�l
	gColorFadeStR = gColorMaskR;
	gColorFadeStG = gColorMaskG;
	gColorFadeStB = gColorMaskB;
	gColorFadeStA = gColorMaskA;
	// �t�F�[�h���B�l
	gColorFadeEdR = colorR;
	gColorFadeEdG = colorG;
	gColorFadeEdB = colorB;
	gColorFadeEdA = 255;
	// �t�F�[�h�J�E���^
	gFadeFrames = frames;
	gFadeCnt = 0;
}
// ���݂̃J���[�}�X�N����t�F�[�h�C���i�J���[�}�X�N�g�p, alpha = 0 �ɂ���j
void ColorFadeIn(int frames)
{
	// �t�F�[�h�J�n�l
	gColorFadeStR = gColorMaskR;
	gColorFadeStG = gColorMaskG;
	gColorFadeStB = gColorMaskB;
	gColorFadeStA = gColorMaskA;
	// �t�F�[�h���B�l
	gColorFadeEdR = gColorMaskR;
	gColorFadeEdG = gColorMaskG;
	gColorFadeEdB = gColorMaskB;
	gColorFadeEdA = 0;
	// �t�F�[�h�J�E���^
	gFadeFrames = frames;
	gFadeCnt = 0;
}

// �t�F�[�h�C���A�E�g�͏I���������H
// �߂�l: 1 = �t�F�[�h��, 0 = �t�F�[�h�I���i�������͊J�n�O�j
int IsColorFade()
{
	if (gFadeCnt < gFadeFrames)
	{
		return 1;
	}
	return 0;
}

// �J���[�}�X�N�̃t�F�[�h�C���A�E�g����
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

// �J���[�}�X�N�̃t�F�[�h�C���A�E�g�`��
void ColorFadeDraw()
{
	if (gColorMaskA > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, gColorMaskA);	// ���������[�h
		DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(gColorMaskR, gColorMaskG, gColorMaskB), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, gColorMaskA);
	}
}

// �A�v���̏�����
// �N������1�񂾂����s�����
void AppInit() {
	//----------------�t�H���g�ǂݍ���----------------------------
	//
	LPCSTR font_path = "res/font/Corporate-Mincho-ver3.otf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}

	// ********** ��������ǂݍ��񂾃t�H���g�𗘗p�ł��� **********
	ChangeFont("�R�[�|���[�g���� ver3 Medium", DX_CHARSET_DEFAULT);

	//----------------------------------------------------------

	gHP = MAX_HP;
	gameChapter = 0;

	gGlobal = new Global();				// �O���[�o�����̍쐬

	gNewScene = NULL;					// ����Scene������������
	gScene = new SceneInit();		// Scene�̎��Ԃ����
}


// �A�v���̉��
// �I������1�񂾂����s�����
void AppRelease() {
	delete gScene;			// Scene���폜����
	delete gGlobal;			// �O���[�o�����̍폜
}

//
// �t���[�������B1�t���[����1�񂸂��s�����
//

// �t���[�������F����
void FrameInput() {
	// �L�[���́A�g���K���́A�����[�X���́Apad1�̓��͒l�𓾂�
	gPad.Input();

	// Scene�̓��͌Ăяo��
	gScene->Input();
}

// �t���[�������F�v�Z
void FrameProcess() {
	// Scene�̌v�Z�Ăяo��
	gScene->Process();
}

// �t���[�������F�`��
void FrameDraw() {

	ClearDrawScreen();						// ��ʂ�����������

	// Scene�̕`��Ăяo��
	gScene->Draw();
	//�J���p
	int massagefontsize = 32;		//�t�H���g�T�C�Y
	int savefontsize;
	savefontsize = GetFontSize();
	SetFontSize(savefontsize);

	ScreenFlip();							// ����ʂ̓��e��\��ʂɔ��f������
}

bool Update() {
	if (mCount == 0) { //1�t���[���ڂȂ玞�����L��
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60�t���[���ڂȂ畽�ς��v�Z����
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void Wait() {
	int tookTime = GetNowCount() - mStartTime;	//������������
	int waitTime = mCount * 1000 / FPS - tookTime;	//�҂ׂ�����
	if (waitTime > 0) {
		Sleep(waitTime);	//�ҋ@
	}
}

void GameMain()
{
	AppInit();	// ������

	// 1�t���[�����[�v��g�� ----------------------------------------------------------
	while (ProcessMessage() == 0)		// �v���O�������I������܂Ń��[�v
	{
		// �V�[����؂�ւ��邩�H
		if (gNewScene != NULL) {
			delete gScene;		// ���̃V�[�����폜����
			gScene = gNewScene;	// �󂯎�����V�[�����|�C���^�Z�b�g
			gNewScene = NULL;	// ���̃V�[��������������
		}
		
		FrameInput();	// ����
		FrameProcess();	// �v�Z
		FrameDraw();	// �`��
		Update();		//�X�V
		Wait();			//FPS�Œ�
	}

	AppRelease();	// ���
}
