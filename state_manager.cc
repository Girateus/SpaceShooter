#include "state_manager.hpp"

int StateManager::score = 0;
int StateManager::lives_remaining = 5;

void StateManager::KillBoss()
{
	score += 50000000;
}

void StateManager::KillEnemy()
{
	score += 10;
}

void StateManager::LostLife()
{
	lives_remaining -= 1;
}

int StateManager::Score()
{
	return score;
}

int StateManager::Life()
{
	return lives_remaining;
}
