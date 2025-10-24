#include "Player.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics//RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

void Player::Load(sf::Vector2f spawnPosition)
{
	Spaceshipe.loadFromFile("data/sprites/Player/playerShip2_green.png");
	
	motor_.SetPosition({ 500, 400 });
	motor_.SetDirection({ 0,1 });
	motor_.SetSpeed(600);

	rect_.setTexture(&Spaceshipe);
	rect_.setSize({ static_cast<float>(Spaceshipe.getSize().x), static_cast<float>(Spaceshipe.getSize().y)});
}

void Player::Update(sf::RenderWindow& window, float deltaTime)
{

	rect_.setPosition(motor_.Move(deltaTime));

	projectiles.Update(window, deltaTime);
}

bool Player::CheckCollision(std::vector<AutoEntity*>& others)
{
	for (auto& other : others)
	{
		if (other->StillAlive == false)
		{
			continue;
		}
		if (rect_.getGlobalBounds().findIntersection(other->GetBounds()))
		{
			other->StillAlive = false;
			return true;
		}
	}
	return false;

}

void Player::CheckProjectileCollisions(std::vector<AutoEntity*>& others)
{
	auto bullets = projectiles.GetEntities();

	for (auto& bullet : bullets)
	{
		if (!bullet->StillAlive)
		{
			continue;
		}

		for (auto& other : others)
		{
			if (!other->StillAlive)
			{
				continue;
			}

			if (bullet->GetBounds().findIntersection(other->GetBounds()))
			{
				other->StillAlive = false;
				bullet->StillAlive = false;
			}
		}

	}
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space))
	{
		projectiles.InitEntities(rect_.getPosition());
	}
	
	motor_.SetDirection(direction);
}

void Player::SetPosition(sf::Vector2f position)
{
	motor_.SetPosition(position);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//sf::Sprite sprite(Spaceshipe);
		target.draw(rect_, states);
	target.draw(projectiles);
}