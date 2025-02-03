#pragma once

#include	"Animation.h"
#include	"data.h"
#include	<vector>

#define	CGBGANIM_PATTERN_MAX	(72)	// �U�؋c�_�̔w�i�A�j���[�V�����p�^�[���i�摜�j�ő吔
#define	CG_JISHOU_BGANIM_PATTERN_MAX	(75)	// �����c�_�̔w�i�A�j���[�V�����p�^�[���i�摜�j�ő吔
#define DAMAGE_EFFECT_ANINAM_NAM (8)// �_���[�W�G�t�F�N�g�̃A�j���[�V������
#define DAMAGE_DIRECTION_ANINAM_NAM (3)// �_���[�W���o�̃A�j���[�V������

class Global {
public:
	Global();			// �R���X�g���N�^
	virtual ~Global();	// �f�X�g���N�^

	void Load();		// �ǂݍ���
	int IsLoadFinish();	// �ǂݍ��݂��I�����Ă���1�A�܂��Ȃ�0

protected:
	Animation anim;

public:
	// ---�������ӏ����ɂރp�[�g�iSceneLook�j---
	
	// ---�U�؋c�_�p�[�g�iSceneGameMain�j---
	std::vector<int> _cgBg;			// �w�i(�U�؋c�_)
	std::vector<int> _cgJishouBg;	// �w�i(�����c�_)
};
