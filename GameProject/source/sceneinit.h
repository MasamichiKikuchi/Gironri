#pragma once

#include	"scenebase.h"

class SceneInit : public SceneBase {
public:
	SceneInit();				// �R���X�g���N�^
	virtual ~SceneInit();		// �f�X�g���N�^

	void Input() override;			// ����
	void Process() override;		// �v�Z
	void Draw() override;			// �`��

protected:
	int cgBg[2];		// �w�i�摜
	int step;	// �t�F�[�h�C���A�E�g�p�X�e�b�v
	int stepCnt;	// �X�e�b�v�J�E���^
};
