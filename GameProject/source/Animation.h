#pragma once

#include	<iostream>
#include	<vector>
#include	<string>

class Animation {
public:
	Animation();		// コンストラクタ
	~Animation();		// デストラクタ

	void GetCG(std::string path, int fileType, int cgMax, std::vector<int>& imgs);	// 複数枚の画像の読み込み
	int cgAnimPattern(int cnt, int speed, int patternMax);				// 表示画像のパターン計算
protected:
	
};
