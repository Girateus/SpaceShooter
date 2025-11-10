#pragma once
#include "auto_entity.hpp"

class BossProjectile : public AutoEntity
{
public:
	void Move(float) override;
	void Load() override;
};

