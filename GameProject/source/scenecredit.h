#pragma once

#include	"scenebase.h"

class SceneCredit : public SceneBase {
public:
	SceneCredit();				// �R���X�g���N�^
	virtual ~SceneCredit();		// �f�X�g���N�^

	void Input() override;			// ����
	void Process() override;		// �v�Z
	void Draw() override;			// �`��

protected:
	int step;						// �t�F�[�h�C���A�E�g�p�X�e�b�v
	int Bgy;
};
