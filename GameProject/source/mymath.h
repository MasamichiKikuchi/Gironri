#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include <math.h>

// �~����
#define	PI				(3.141592653589793)

// radian��degree
float DegToRad(float deg);

// degree��radian
float RadToDeg(float rad);

// �����蔻��p�B�_����`���ɂ��邩�𔻒�
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
int IsHitPointBox(
	int px, int py,						// �_�̍��W�ix,y�j
	int bx, int by, int bw, int bh		// ��`�̍���ix,y�j, �傫��w,h
);

// �����蔻��p�B�_���~���ɂ��邩�𔻒�
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
int IsHitPointCircle(
	int px, int py,						// �_�̍��W�ix,y�j
	int cx, int cy, int cr				// �~�̒��S�ix,y�j, ���ar
);

void DrawPosString(int x, int y, int posBaseX, unsigned int color, const char* str);

// �����蔻��p�B2��box�������������𔻒�
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
int IsHitBox(
	int x1, int y1, int w1, int h1,		// �ЂƂ߂�box ����(x,y), �傫��w,h
	int x2, int y2, int w2, int h2		// �ӂ��߂�box ����(x,y), �傫��w,h
);


// �����蔻��p�B2�̉~�������������𔻒�
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
int IsHitCircle(
	int x1, int y1, int r1,		// �ЂƂ߂�circle ���S(x,y), ���ar
	int x2, int y2, int r2		// �ӂ��߂�circle ���S(x,y), ���ar
);


// �l�X�ȃC�[�W���O
// https://game-ui.net/?p=835 ���Q�l��
float EasingLinear(float cnt, float start, float end, float frames);
float EasingInQuad(float cnt, float start, float end, float frames);
float EasingOutQuad(float cnt, float start, float end, float frames);
float EasingInOutQuad(float cnt, float start, float end, float frames);
float EasingInCubic(float cnt, float start, float end, float frames);
float EasingOutCubic(float cnt, float start, float end, float frames);
float EasingInOutCubic(float cnt, float start, float end, float frames);
float EasingInQuart(float cnt, float start, float end, float frames);
float EasingOutQuart(float cnt, float start, float end, float frames);
float EasingInOutQuart(float cnt, float start, float end, float frames);
float EasingInQuint(float cnt, float start, float end, float frames);
float EasingOutQuint(float cnt, float start, float end, float frames);
float EasingInOutQuint(float cnt, float start, float end, float frames);
float EasingInSine(float cnt, float start, float end, float frames);
float EasingOutSine(float cnt, float start, float end, float frames);
float EasingInOutSine(float cnt, float start, float end, float frames);
float EasingInExpo(float cnt, float start, float end, float frames);
float EasingOutExpo(float cnt, float start, float end, float frames);
float EasingInOutExpo(float cnt, float start, float end, float frames);
float EasingInCirc(float cnt, float start, float end, float frames);
float EasingOutCirc(float cnt, float start, float end, float frames);
float EasingInOutCirc(float cnt, float start, float end, float frames);
