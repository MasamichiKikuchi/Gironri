#pragma once

#include	<iostream>
#include	<vector>
#include	<string>

class Animation {
public:
	Animation();		// �R���X�g���N�^
	~Animation();		// �f�X�g���N�^

	void GetCG(std::string path, int fileType, int cgMax, std::vector<int>& imgs);	// �������̉摜�̓ǂݍ���
	int cgAnimPattern(int cnt, int speed, int patternMax);				// �\���摜�̃p�^�[���v�Z
protected:
	
};
