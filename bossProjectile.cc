#include "bossProjectile.hpp"

void BossProjectile::Move(float deltaTime)
{
	rect_.setPosition(motor_.Move(deltaTime));
}

void BossProjectile::Load()
{
	AutoEntity::Load("data\\sprites\\Lasers\\laserRed08.png", { 0, 1 }, 200); // shooting speed
}