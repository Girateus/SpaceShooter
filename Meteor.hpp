#pragma once
#include "SFML/Graphics.hpp"
#include "Motor.hpp"
#include <iostream>

class Meteor : public sf::Drawable, public sf::Transformable
{
	sf::Texture MeteorTexture;
	Motor motor_;

public:
	void Load();
	void Move(float);
	void Update();

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

