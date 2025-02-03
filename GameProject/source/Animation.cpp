#include	"Animation.h"
#include	"DxLib.h"

Animation::Animation()
{
	
}

Animation::~Animation()
{

}

// �������̉摜�̓ǂݍ���
// fileType = 0:png, 1:jpg
void Animation::GetCG(std::string path, int fileType, int cgMax, std::vector<int>& imgs)
{
	int i;
	std::string fType;
	// �摜�t�@�C���̊g���q�̎���
	switch (fileType)
	{
	case 0:
		fType = ".png";
		break;
	case 1:
		fType = ".jpg";
		break;
	}
	// �摜�t�@�C���̕������̓ǂݍ���
	for (i = 0; i < cgMax; i++)
	{
		std::string imgPath = path + std::to_string(i) + fType;
		int img = LoadGraph(imgPath.c_str());
		imgs.push_back(img);
	}
}

// �\���摜�̃p�^�[���v�Z
int Animation::cgAnimPattern(int cnt, int speed, int patternMax)
{
	int pattern = (cnt / speed) % patternMax;
	return pattern;
}
