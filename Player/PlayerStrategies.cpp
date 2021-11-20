#include "PlayerStrategies.h" // Include header file

Player* PlayerStrategy::getPlayer()
{
	return p;
}

void PlayerStrategy::setPlayer(Player* player)
{
	p = player;
}
