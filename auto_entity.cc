#include "auto_entity.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

void AutoEntity::Load(std::string_view pathFile, sf::Vector2f direction, float speed)
{
	//load texture for any entitie
	Texture.loadFromFile(pathFile);

	//set the direction and speed of any entitie
	motor_.SetDirection(direction);
	motor_.SetSpeed(speed);

	//set a rectangle to help with collision
	rect_.setTexture(&Texture);
	rect_.setSize({ static_cast<float>(Texture.getSize().x), static_cast<float>(Texture.getSize().y) });
	rect_.setOrigin({ static_cast<float>(Texture.getSize().x/2.f), static_cast<float>(Texture.getSize().y)/ 2.f });
}


void AutoEntity::SetPosition(sf::Vector2f position)
{
	motor_.SetPosition(position);
}

void AutoEntity::SetDirection(sf::Vector2f direction)
{
	motor_.SetDirection(direction);
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