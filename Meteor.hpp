#pragma once
#include "auto_entity.hpp"

class Meteor : public AutoEntity
{

public:
	void Load() override;
	void Move(float) override;

};
// set meteor Position
inline void Meteor::Move(float deltaTime)
{
	rect_.setPosition(motor_.Move(deltaTime));
}
//load meteor Texture
inline void Meteor::Load()
{
	AutoEntity::Load("data\\sprites\\Meteors\\meteorBrown_big1.png", {0, 1}, 100);

}

