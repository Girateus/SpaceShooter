#include "Motor.hpp"
#include <SFML/OpenGL.hpp>

Motor::Motor()
{
	speed_ = 0;
	direction_ = { 0,0 };
	position_ = { 0, 0 };
}

void Motor::SetSpeed(float speed)
{
	speed_ = speed;
}
void Motor::SetDirection(sf::Vector2f dir)
{
	direction_ = dir;

}
void Motor::SetPosition(sf::Vector2f position)
{
	position_ = position;
}
sf::Vector2f Motor::GetDirection()
{
	return direction_;
}
sf::Vector2f Motor::Move(float deltaTimeSec)
{ 
	if(direction_.length() > 0 )
	{
		position_ += deltaTimeSec * speed_ * direction_.normalized();
	}
	
	return position_;
}