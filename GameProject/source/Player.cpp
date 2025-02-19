#include "Player.h"
#include "winmain.h"
#include "gamemain.h"

Player::Player()
{
	AT = MAX_AT;
}

Player::~Player()
{
}

void Player::LifeProcess()
{
	if (reHP > gHP)
	{
		reHP--;
	}
	if (reHP < gHP)
	{
		reHP++;
	}
}

void Player::CheckPlayerLife()
{
	if (AT < 0)
	{
		//ATが0以下なら0に
		AT = 0;
	}
	else if (AT > MAX_AT) {
		//ATがMAX_AT以上ならMAX_ATに
		AT = MAX_AT;
	}
	if (gHP > MAX_HP)
	{
		gHP = MAX_HP;
	}
	if (gHP < 0)
	{
		//HPが0以下なら0に
		gHP = 0;
	}
}
