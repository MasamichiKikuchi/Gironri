#pragma once

class SceneBase {
public:
	SceneBase();				// �R���X�g���N�^
	virtual ~SceneBase();		// �f�X�g���N�^

	virtual void Input();		// ����
	virtual void Process();		// �v�Z
	virtual void Draw();		// �`��

protected:
};