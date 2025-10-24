#include "auto_entity.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

void AutoEntity::Load(std::string_view pathFile, sf::Vector2f direction, float speed)
{
	Texture.loadFromFile(pathFile);

	//motor_.SetPosition({ 500, 400 });
	motor_.SetDirection(direction);
	motor_.SetSpeed(speed);

	rect_.setTexture(&Texture);
	rect_.setSize({ static_cast<float>(Texture.getSize().x), static_cast<float>(Texture.getSize().y) });
}


void AutoEntity::SetPosition(sf::Vector2f position)
{
	motor_.SetPosition(position);
}

sf::Vector2f AutoEntity::GetPosition()
{
	return rect_.getPosition();
}

void AutoEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (StillAlive)
	{
		target.draw(rect_, states);
	}
}

sf::FloatRect AutoEntity::GetBounds()
{
	return rect_.getGlobalBounds();
}