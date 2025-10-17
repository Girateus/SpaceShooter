#pragma once
#include "SFML/Graphics.hpp"
#include "Motor.hpp"
#include <iostream>

class Enemy : public sf::Drawable, public sf::Transformable
{
	sf::Texture EnemyShip;
	Motor motor_;

public:
	void Load();
	void Move(float);
	void Update();

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

