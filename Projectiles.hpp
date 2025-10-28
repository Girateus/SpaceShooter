#pragma once

#include "auto_entity.hpp"

class Projectile : public AutoEntity
{

public:
	void Move(float) override;
	void Load() override;
};

inline void Projectile::Move(float deltaTime)
{
	rect_.setPosition(motor_.Move(deltaTime));
}

inline void Projectile::Load()
{
	AutoEntity::Load("data\\sprites\\Lasers\\laserGreen08.png", {0, -1}, 300);
}

