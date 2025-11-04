#pragma once

#include "auto_entity.hpp"

	class Projectile : public AutoEntity
	{

	public:
		void Move(float) override;
		void Load() override;
	};
	//set projectile position 
	inline void Projectile::Move(float deltaTime)
	{
		rect_.setPosition(motor_.Move(deltaTime));
	}
	//load projectile texture
	inline void Projectile::Load()
	{
		AutoEntity::Load("data\\sprites\\Lasers\\laserGreen08.png", { 0, -1 }, 300);
	}


