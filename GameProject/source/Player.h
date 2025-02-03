#pragma once
#include "ObjectBase.h"
#include "DxLib.h"

#define	NOMAL_DAMAGE		10	//通常状態で受けるダメージ
#define	SHIELD_DAMAGE		7	//ガード状態でATが受けるダメージ
#define	GET_IP		50			//シールド状態で手に入るIP
#define MAX_AT		(50 * 2)		//最大AT

#define AT_SPEED		100		//AT回復スピード
#define AT_INTERVAL		120.0	//AT回復インターバル

class Player : public ObjectBase {
public:
	Player();
	virtual ~Player();

	void	LifeProcess();		//体力ヌルヌル変更
	void	CheckPlayerLife();

	float AT;
	
protected:

	
};