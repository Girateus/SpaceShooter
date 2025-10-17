#pragma once
#include <SFML/System/Vector2.hpp>
class Motor
{
	float speed_;
	sf::Vector2f direction_;
	sf::Vector2f position_;

public:
	Motor();

	
	void SetSpeed(float speed);
	void SetDirection(sf::Vector2f);
	void SetPosition(sf::Vector2f);

	sf::Vector2f GetDirection();

	sf::Vector2f Move(float deltaTimeSec);
};

