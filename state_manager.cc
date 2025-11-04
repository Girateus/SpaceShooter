#include "state_manager.hpp"

int StateManager::score = 0;
//int lives_remaining = 0;

void StateManager::KillEnemy()
{
	score += 10;
}

//void StateManager::LostLife()
//{
//	lives_remaining -= 1;
//}

int StateManager::Score()
{
	return score;
}
