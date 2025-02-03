#pragma once

#define	EFFECT_MAX	(30)	// �G�t�F�N�g�̍ő吔

class Effect {
public:
	Effect();	// �R���X�g���N�^
	~Effect();	// �f�X�g���N�^

	void InitEffect();							// �G�t�F�N�g���̏�����
	void AddEffect(int type, int x, int y);		// �G�t�F�N�g�ǉ�
	void ProcessEffect();						// �G�t�F�N�g����
	void DrawEffect();							// �G�t�F�N�g�`��

	void ProcessShake();						// ��ʗh�炵����

	// �G�t�F�N�g�\����
	struct EFFECT
	{
		int		use;		// ���̔z����g�p���邩�i0:�g�p���Ȃ�, 1:�g�p����j
		int		type;		// ����^�C�v
		int		x, y;		// ���W
		int		animcnt;	// �A�j���[�V�����J�E���^
		int		animspeed;	// �A�j���[�V�������x
		int		animnum;	// �A�j���[�V�����p�^�[����
		float   scale;		// �摜�̑傫��
	};
	// �G�t�F�N�g���
	EFFECT effect[EFFECT_MAX];

	// ��ʗh�炵�֘A
	int shake;			//�w�i�h�炵��
	int bgflg;			//�h�炵�t���O
	int shakecnt;		//�h�炷����
	int shakespead;		//�h�炵�X�s�[�h
};
