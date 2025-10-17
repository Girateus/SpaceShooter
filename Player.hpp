#pragma once

#include <iostream>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>


#include "Motor.hpp"

class Player : public sf::Drawable, public sf:: Transformable
{
	sf::Texture Spaceshipe;
	Motor motor_;

public:	
	void Load();
	void Move(float);
	void HandleEvent();

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
};
