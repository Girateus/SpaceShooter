#pragma once
#include "auto_entity.hpp"

class Enemy : public AutoEntity
{
public:
	void Load() override;
	void Move(float) override;

};

inline void Enemy::Move(float deltaTime)
{
	rect_.setPosition(motor_.Move(deltaTime));
}

inline void Enemy::Load()
{
	AutoEntity::Load("Data\\PNG\\Enemies\\enemyBlack1.png", { 0, 1 }, 300);
}

