#pragma once

#include	"scenebase.h"

class SceneGameTitle : public SceneBase {
public:
	SceneGameTitle();				// �R���X�g���N�^
	virtual ~SceneGameTitle();		// �f�X�g���N�^

	void Input() override;			// ����
	void Process() override;		// �v�Z
	void Draw() override;			// �`��

protected:
	int _cgBg;						// �w�i�摜
	int _cgBgUI;					// ����
	int step;						// �t�F�[�h�C���A�E�g�p�X�e�b�v
	int alpha;						// �摜�A���t�@�l
	int frame;						// �C�[�W���O�t���[����
	int pushKeyFlag;				// �{�^���������ꂽ���̃t���O
};
