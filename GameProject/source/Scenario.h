#pragma once
#include <vector>

//菊池担当箇所　ファイル全て

#define	ENEMY_MAX	(5)		// 敵最大人数

class Scenario {
public:
	Scenario();
	virtual ~Scenario();

	// 敵出現シナリオ情報
	struct SCENARIO {
		int numName;	// 証言者番号（0：赤, 1：緑, 2：黄, 3：青, 4：ピンク）
		int testimonyCnt;	// 証言カウント（0, 1：証言, 2：暴言, 3：終了）
		int gamecnt;// gGameCntがこの値になったら出現
		float x;// 言葉が出現する位置 X座標
		float y;	// 言葉が出現する位置 Y座標
		int wordType;	//言葉の種類　0：未使用 1：暴言　2：証言 -1：ループ用
		int cgName;	//画像名
		int waitTime;	//出現後から動き出すまでの時間
		int seName; //音声名
	};

	void AddScenario(SCENARIO* scenario, size_t size);//ゲームシーン用のシナリオに中身を追加する
	void SetChapterScenario(int chapter);	//チャプターごとのシナリオをセット
	void SetEnemyPosition(int chaoter);     //敵の位置をセット

	std::vector<SCENARIO> scenarioList;		//ゲームシーン用シナリオのvector
	std::vector<SCENARIO>* GetScenario();	//ゲームシーン用シナリオのゲッター

protected:

};
