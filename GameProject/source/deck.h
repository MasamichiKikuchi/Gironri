#pragma once

#include	"DxLib.h"
#include	<iostream>
#include	<deque>
#include	<vector>

#define	ENEMY_MAX	(5)		// 敵最大人数
#define	CARD_SPEED	(10 * 2.5)	// カードの速度
#define	DECREASE_SCALE (0.005 * 2.5)		//カードの小さくなる度合
#define	ENEMY_HIT_X	(10)	//敵の当たり範囲（X座標）
#define	ENEMY_HIT_Y	(10)	//敵の当たり範囲（Y座標）
#define	DECK_CARD_X	(1830)	// 議論パート中の手札の位置（x座標）
#define	DECK_CARD_Y	(801)	// 議論パート中の手札の位置（y座標）

class Deck {
public:
	Deck();		// コンストラクタ
	~Deck();	// デストラクタ

	int GetCenterCard();						// 手札の中心位置（選択中のカード）
	bool CheckCard(int number, int ttmCnt);		// 同じ証言を所持しているかの確認
	void GetCard(int number, int cgCard, int wordX, int wordY, float wordScale, int wordTtmCnt);	// 手札追加
	void SelectCard();							// カード選択, 正解判定
	void TurnCard();							// カードの裏返し
	void MotionCard(int flg_gf);				// 議論中カードモーション
	void SetDrawCard(int flg_gf);	// ゲーム状況に合わせてカードを変更
	void DrawCard(int flg_gf);		// カード表示
	void MoveCard(int &flg_gf);					// カードの移動
	void SetCutInFlag(int cutInFlag);			// カットイン中フラグの取得

protected:
	float calcX(int i);		// カードのX座標の計算式

public:
	struct CARD {
		int num;			// カード証言者番号（0：赤, 1：緑, 2：黄, 3：青, 4：ピンク）
		int cg;				// カード画像
		VECTOR pos;			// カードの大きさ
		float scale;		// カードの大きさ
		int motionCnt;		// モーションカウント
		int testimonyCnt;	// 証言カウント
		float direction;	// 移動する角度
		float speed;		// 移動する速さ
	};
	std::deque<CARD> cards;		// 手札

	int answer_card;	// 正解のカード
	int flg_ans;		// 正解判定フラグ（0：選択中, 1：正解, 2：不正解）
	int flg_selectCard;	// カードが選択できるかどうか（0：画面外に移動, 1：画面内に移動, 2：展開, 3：選択, 4：正解）
	int cardMoveFlag;	// カードが移動可能か
	int deckCutInflag;  // カットイン中かの判別フラグ
	int cardSelectEffectFlag;	// カード選択時の演出フラグ

protected:
	int getCnt;				// 取得時のカードカウント
	int turnCnt;			// 反転時のカードカウント
	float frame;
};
