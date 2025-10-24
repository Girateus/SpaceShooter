#pragma once
#include <iostream>

void RandomInit()
{
	srand(time(nullptr));
}
float Spawn()
{
	return 1 + rand() % 800;
}