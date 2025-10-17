#include "Enemy.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics//RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

void Enemy::Load()
{
	EnemyShip.loadFromFile("data/sprites/Enemies/enemyBlack1.png");
	motor_.SetPosition({ 0,0 });
	motor_.SetDirection({ 0,-1 });
	motor_.SetSpeed({ 10 });
}
void Enemy::Move(float deltaTime)
{
	setPosition(motor_.Move(deltaTime));
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite sprite(EnemyShip);
	states.transform *= getTransform();

	target.draw(sprite, states);
}
