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
		//AT‚ª0ˆÈ‰º‚È‚ç0‚É
		AT = 0;
	}
	else if (AT > MAX_AT) {
		//AT‚ªMAX_ATˆÈã‚È‚çMAX_AT‚É
		AT = MAX_AT;
	}
	if (gHP > MAX_HP)
	{
		gHP = MAX_HP;
	}
	if (gHP < 0)
	{
		//HP‚ª0ˆÈ‰º‚È‚ç0‚É
		gHP = 0;
	}
}
