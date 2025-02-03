#include	"Animation.h"
#include	"DxLib.h"

Animation::Animation()
{
	
}

Animation::~Animation()
{

}

// 複数枚の画像の読み込み
// fileType = 0:png, 1:jpg
void Animation::GetCG(std::string path, int fileType, int cgMax, std::vector<int>& imgs)
{
	int i;
	std::string fType;
	// 画像ファイルの拡張子の識別
	switch (fileType)
	{
	case 0:
		fType = ".png";
		break;
	case 1:
		fType = ".jpg";
		break;
	}
	// 画像ファイルの複数枚の読み込み
	for (i = 0; i < cgMax; i++)
	{
		std::string imgPath = path + std::to_string(i) + fType;
		int img = LoadGraph(imgPath.c_str());
		imgs.push_back(img);
	}
}

// 表示画像のパターン計算
int Animation::cgAnimPattern(int cnt, int speed, int patternMax)
{
	int pattern = (cnt / speed) % patternMax;
	return pattern;
}
