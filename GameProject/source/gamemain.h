#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�

#include	"scenebase.h"
#include	"gamepad.h"
#include	"data.h"
#include	"global.h"

#define MAX_HP		(100 * 6)		//�ő�HP
#define RECOVERY_HP		(100)		//�U�؋c�_�I����HP�񕜒l
#define TALK_MISS_HP		(10)	//�I�����ԈႦ��HP�����l
#define MAX_LOGSAVE		(9999)		//�o�b�N���O�̍ő�ۑ���
#define JSON_MAX		(999)		// JSON�p�z��̍ő�

// �Q�[�����
extern GamePad gPad;			// �Q�[���p�b�h�̏��
extern Global* gGlobal;

extern int gHP;					// HP
extern int reHP;
extern int gameChapter;			// �͔ԍ�

//FPS�Œ�
static int mStartTime;      //����J�n����
static int mCount;          //�J�E���^
static float mFps;          //fps
static const int N = 60;	//���ς����T���v����
static const int FPS = 60;	//�ݒ肵��FPS

// ���O�֘A
struct messageLog {
	std::string name;
	std::string message1;
	std::string message2;
	int use;
};
extern struct messageLog logsave[MAX_LOGSAVE];
extern int logflg;	//���O�����m�F�̃t���O
extern int log_y;	//���O��Y���W
extern int logcnt;

extern int lastchoice_skipflg;
void LogProcess();
void LogDraw();
void LogChange();

// �V�[��
void ChangeScene(SceneBase* scene);		// Scene��ύX����

// ---�t�F�[�h�C��/�t�F�[�h�A�E�g---
// �J���[�}�X�N�p
extern int gColorMaskR, gColorMaskG, gColorMaskB, gColorMaskA;
// �J���[�}�X�N�w��
void ColorMask(int colorR, int colorG, int colorB, int colorA);

// �t�F�[�h�C���A�E�g�p
extern int gColorFadeStR, gColorFadeStG, gColorFadeStB, gColorFadeStA;
extern int gColorFadeEdR, gColorFadeEdG, gColorFadeEdB, gColorFadeEdA;
extern int gFadeFrames, gFadeCnt;
// �w��̐F�Ƀt�F�[�h�A�E�g�i�J���[�}�X�N�g�p, alpha = 255 �ɂ���j
void ColorFadeOut(int colorR, int colorG, int colorB, int frames);

// ���݂̃J���[�}�X�N����t�F�[�h�C���i�J���[�}�X�N�g�p, alpha = 0 �ɂ���j
void ColorFadeIn(int frames);

// �t�F�[�h�C���A�E�g�͏I���������H
// �߂�l: 1 = �t�F�[�h��, 0 = �t�F�[�h�I���i�������͊J�n�O�j
int IsColorFade();

// �J���[�}�X�N�̃t�F�[�h�C���A�E�g����
void ColorFadeProcess();

// �J���[�}�X�N�̃t�F�[�h�C���A�E�g�`��
void ColorFadeDraw();

// ---�Q�[�����C��---
void GameMain();	// gamemain.cpp �Ɏ��̂��L�q

//FPS�Œ�p
bool Update();
void Wait();