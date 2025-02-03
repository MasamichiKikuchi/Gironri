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
		//AT��0�ȉ��Ȃ�0��
		AT = 0;
	}
	else if (AT > MAX_AT) {
		//AT��MAX_AT�ȏ�Ȃ�MAX_AT��
		AT = MAX_AT;
	}
	if (gHP > MAX_HP)
	{
		gHP = MAX_HP;
	}
	if (gHP < 0)
	{
		//HP��0�ȉ��Ȃ�0��
		gHP = 0;
	}
}
