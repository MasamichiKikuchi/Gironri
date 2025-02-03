#pragma once
#include <vector>

//�e�r�S���ӏ��@�t�@�C���S��

#define	ENEMY_MAX	(5)		// �G�ő�l��

class Scenario {
public:
	Scenario();
	virtual ~Scenario();

	// �G�o���V�i���I���
	struct SCENARIO {
		int numName;	// �،��Ҕԍ��i0�F��, 1�F��, 2�F��, 3�F��, 4�F�s���N�j
		int testimonyCnt;	// �،��J�E���g�i0, 1�F�،�, 2�F�\��, 3�F�I���j
		int gamecnt;// gGameCnt�����̒l�ɂȂ�����o��
		float x;// ���t���o������ʒu X���W
		float y;	// ���t���o������ʒu Y���W
		int wordType;	//���t�̎�ށ@0�F���g�p 1�F�\���@2�F�،� -1�F���[�v�p
		int cgName;	//�摜��
		int waitTime;	//�o���ォ�瓮���o���܂ł̎���
		int seName; //������
	};

	void AddScenario(SCENARIO* scenario, size_t size);//�Q�[���V�[���p�̃V�i���I�ɒ��g��ǉ�����
	void SetChapterScenario(int chapter);	//�`���v�^�[���Ƃ̃V�i���I���Z�b�g
	void SetEnemyPosition(int chaoter);     //�G�̈ʒu���Z�b�g

	std::vector<SCENARIO> scenarioList;		//�Q�[���V�[���p�V�i���I��vector
	std::vector<SCENARIO>* GetScenario();	//�Q�[���V�[���p�V�i���I�̃Q�b�^�[

protected:

};
