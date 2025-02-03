#include	"effect.h"
#include	"DxLib.h"
#include	"data.h"

Effect::Effect()
{
	shake = 0;
	shakecnt = 0;
	shakespead = 6;
	bgflg = 0;
}

Effect::~Effect()
{

}

// エフェクト情報の初期化
void Effect::InitEffect()
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		effect[i].use = 0;
	}
}

// エフェクト追加
void Effect::AddEffect(int type, int x, int y)
{
	int i;
	// 使っていない配列を探す
	for (i = 0; i < EFFECT_MAX; i++)
	{
		if (effect[i].use == 0)
		{
			// 使っていない。ここを使う
			effect[i].use = 1;
			effect[i].x = x;
			effect[i].y = y;
			effect[i].animcnt = 0;
			effect[i].type = type;
			switch (type) {
			case 0:	// ダメージエフェクト
				effect[i].animspeed = 6;
				effect[i].animnum = 8;
				effect[i].scale = 0.3;
				break;

			case 1:	// ダメージ演出
				effect[i].animspeed = 5;
				effect[i].animnum = 9;
				effect[i].scale = 1.0;
				break;
			case 2:	// ガード中カード演出
				effect[i].animspeed = 2;
				effect[i].animnum = 10;
				effect[i].scale = 1.0;
				break;
			case 3:	// ガード中ダメージ演出
				effect[i].animspeed = 3;
				effect[i].animnum = 8;
				effect[i].scale = 0.75;
				break;
			}

			break;
		}
	}
}

// エフェクト処理
void Effect::ProcessEffect()
{
	int i;
	for (i = 0; i < EFFECT_MAX; i++)
	{
		// このエフェクトは使用中か？
		if (effect[i].use == 1)
		{
			effect[i].animcnt++;

			if (effect[i].animcnt / effect[i].animspeed >= effect[i].animnum) {
				// 最後まで再生されたので終了
				effect[i].use = 0;
			}
		}
	}
}

// エフェクト描画
void Effect::DrawEffect()
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		// このエフェクトは使用中か？
		if (effect[i].use == 1)
		{

			DrawRotaGraph(effect[i].x, effect[i].y, effect[i].scale, 0.0f, cgEffect[effect[i].type][effect[i].animcnt / effect[i].animspeed], TRUE, 0);
		}
	}
}

void Effect::ProcessShake()
{
	int bgcnt = 3;
	if (shakecnt <= 0) {
		shake = 0;
	}
	else {
		shakecnt--;
		if (bgflg == 1) {
			shake++;
			if (shake > bgcnt) {
				bgflg = 2;
			}
		}
		else {
			shake--;
			if (shake < -bgcnt) {
				bgflg = 1;
			}
		}
	}
}
