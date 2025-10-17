#include "Player.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics//RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

void Player::Load()
{
	Spaceshipe.loadFromFile("data/sprites/Player/playerShip2_green.png");
	
	motor_.SetPosition({ 500, 400 });
	motor_.SetDirection({ 0,1 });
	motor_.SetSpeed(600);
}

void Player::Move(float deltaTime)
{
	setPosition(motor_.Move(deltaTime));
}

void Player::HandleEvent()
{
	sf::Vector2f direction({ 0, 0 });

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down))
	{
		direction.y = 1;
		std::cout << "test down \n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up))
	{
		direction.y = -1;
		std::cout << "test up \n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
	{
		direction.x = -1;
		std::cout << "test left \n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
	{
		direction.x = 1;
		std::cout << "test right\n";
	}
	
	motor_.SetDirection(direction);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite sprite(Spaceshipe);
	states.transform *= getTransform();

	target.draw(sprite, states);
}