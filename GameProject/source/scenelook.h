#pragma once

#include	"scenebase.h"
#include	"winmain.h"
#include	"gamemain.h"
#include	"UI.h"
#include	"effect.h"
#include	"Player.h"
#include	<iostream>
#include	<vector>
#include	<string>

#define	ALPHA_VALUE	(150)	// �A���t�@�l
#define	SPOTLIGHT_SPEED	(7)	// �X�|�b�g���C�g�̈ړ����x
#define	SPOTLIGHT_SIZE_MAX	(150)	// �X�|�b�g���C�g�̍ő�T�C�Y
#define	SPOTLIGHT_SIZE_MIN	(10)	// �X�|�b�g���C�g�̍ŏ��T�C�Y
#define	DRAW_MESSAGE_COUNT	(2)	// �`��^�C�~���O�̃J�E���^
#define LOOK_BGM_VOLUME	(70)	// BGM�{�����[��	���{�����[���͑S��255�i�K
#define LOOK_SE_VOLUME	(70)	// SE�{�����[��

class SceneLook : public SceneBase {
public:
	SceneLook(int chapter);
	virtual ~SceneLook();

	void Input() override;
	void Process() override;
	void Draw() override;

protected:
	//int _cgBg;		// �w�i

	int flgAnswer;		// �ɂ񂾉ӏ����������i�����F0, �����F1, �s�����F2, ����s�����F3�j

	// ---�X�|�b�g���C�g---
	// ���C�g�̃}�X�T�C�Y
	static const int LIGHTSIZE_W = 2;
	static const int LIGHTSIZE_H = 2;

	// ���C�g�̃}�X��
	static const int LIGHTMAP_W = (SCREEN_W / LIGHTSIZE_W);
	static const int LIGHTMAP_H = (SCREEN_H / LIGHTSIZE_H);

	// ���C�g�̃}�X�f�[�^
	int mapLight[LIGHTMAP_W * LIGHTMAP_H];
	int mapAnsLight[LIGHTMAP_W * LIGHTMAP_H];	// ����p

	// �X�|�b�g���C�g�̈ʒu, �T�C�Y
	VECTOR vSpotLight;
	int spotlightSize;
	int ansLightSize;	// ����p���C�g�̃T�C�Y

	// ���C�g�}�b�v�̒l�̃Z�b�g
	void SetLightMap();
	// ���C�g�̃}�X�f�[�^�ɉ~�̃X�|�b�g���C�g������
	void SpotLight(int cx, int cy, int cr, int alpha, int typeAns);

	// ---����֌W---
	VECTOR vInputR;		// �E�X�e�B�b�N�̓��͒l
	VECTOR vUnitR;		// �E�X�e�B�b�N���͒l�ɂ��̒P�ʃx�N�g��
	VECTOR vDirR;		// �ړ���

	// ---����---
	std::string drawMessage1;				// �`�悷�镶����i1�s�ځj
	std::string drawMessage2;				// �`�悷�镶����i2�s�ځj
	std::string drawMessage3;				// �`�悷�镶����i3�s�ځj
	int talkCnt;		// �Z���t�����J�E���^
	int flgAllTalk;	// �Z���t�S���\�����邩�i0�F���Ȃ�, 1�F����j
	int allTalkCnt;	// �S���\���J�E���g
	int lineflg;	// 2�s�ڔ���
	int drawCnt1;	// 1�s�ډ�b�J�E���g
	int drawCnt2;	// 2�s�ډ�b�J�E���g

	//---�֐�---
	void NormInput(XINPUT_STATE xinput);	// �E�X�e�B�b�N�̓��͒l�̐��K��
	void splMove(XINPUT_STATE xinput);		// �~�̈ړ�
	void splScale(XINPUT_STATE xinput);		// �~�̃T�C�Y�ύX�i�g��k���j
	void CheckPoint(float px, float py);	// �ɂ񂾉ӏ��̃`�F�b�N
	void lookTalk();						// �������ӏ���I�����̃Z���t

	UI ui;		// UI�֘A

	Effect gEffect;		// �G�t�F�N�g

	Player player;

	int lightCnt;		// ���C�g�}�X�J�E���g
	int step;			// �t�F�[�h�C���A�E�g�p�X�e�b�v

	int UniqueNoAnsNum;
	int UniqueNoAnsCnt;
	int flgLook;		// ����{�^���L������t���O�i0�F�����i�J�n���j, 1�F�����i�G�t�F�N�g���j, 2�F�L���j
};
