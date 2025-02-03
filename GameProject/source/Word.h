#pragma once
#include "ObjectBase.h"
#include "DxLib.h"

//菊池担当箇所　ファイル全て

#define	THOUGHTLESSWORDS_SPEED_CHAPT0	(6)			// 暴言のスピード　チュートリアル
#define	THOUGHTLESSWORDS_SPEED_CHAPT1	(6)			// 暴言のスピード　チャプター1
#define	THOUGHTLESSWORDS_SPEED_CHAPT2	(8)			// 暴言のスピード　チャプター2
#define	THOUGHTLESSWORDS_SPEED_CHAPT3	(6)			// 暴言のスピード　チャプター3
#define	THOUGHTLESSWORDS_SPEED_CHAPT4	(8)			// 暴言のスピード　チャプター4
#define	THOUGHTLESSWORDS_SPEED_CHAPT5	(6)			// 暴言のスピード　チャプター5
#define	THOUGHTLESSWORDS_SCALE	(0.005)		// 暴言の拡大率
#define	TESTIMONY_SPEED_CHAPT0	(3)			// 証言のスピード　チュートリアル
#define	TESTIMONY_SPEED_CHAPT1	(3)			// 証言のスピード　チャプター1
#define	TESTIMONY_SPEED_CHAPT2	(3)			// 証言のスピード　チャプター2
#define	TESTIMONY_SPEED_CHAPT3	(3)			// 証言のスピード　チャプター3
#define	TESTIMONY_SPEED_CHAPT4	(3)			// 証言のスピード　チャプター4
#define	TESTIMONY_SPEED_CHAPT5	(3)			// 証言のスピード　チャプター5
#define	TESTIMONY_SCALE	(0.0025)		// 証言の拡大率

class Word : public ObjectBase {
public:
	Word();			// コンストラクタ
	virtual ~Word();	// デストラクタ
	void Move(int wordType, int chapter);	//言葉を動かす
	void EraseWord();	//言葉を消す
	int wordType;	// この言葉の種類（0:未使用, 1:暴言, 2:証言,）
	int use;		// この言葉を使用するか（0:使用しない, 1:使用する）
	float scale;		//言葉の大きさ
	int cgName;	//画像ハンドル
	int count; //出現のタイミング
	int waitTime; //出現から動き出す時間
	int seName; //音声
	int numName;	// 証言者番号（0：赤, 1：緑, 2：黄, 3：青, 4：ピンク）
	int testimonyCnt;	// 証言カウント
	
protected:
	
};