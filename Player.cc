#include "Player.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics//RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include "AudioManager.hpp"
#include "state_manager.hpp"




void Player::Load(sf::Vector2f spawnPosition)
{
	Spaceshipe.loadFromFile("data/sprites/Player/playerShip2_green.png");
	
	motor_.SetPosition({ 960, 600 });
	motor_.SetDirection({ 0,1 });
	motor_.SetSpeed(600);

	rect_.setTexture(&Spaceshipe);
	rect_.setSize({ static_cast<float>(Spaceshipe.getSize().x), static_cast<float>(Spaceshipe.getSize().y)});
	rect_.setOrigin({ static_cast<float>(Spaceshipe.getSize().x / 2.f), static_cast<float>(Spaceshipe.getSize().y) / 2.f });
}

void Player::Update(sf::RenderWindow& window, float deltaTime)
{

	rect_.setPosition(motor_.Move(deltaTime));

	projectiles.Update(window, deltaTime);
}

void Player::SetAudioManager(AudioManager* audioManager)
{
	audioManager_ = audioManager;
}
//check collision between player and meteor and enemies
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
			StateManager::LostLife();
			//play explosion sound
			audioManager_->ExplosionAudio();
			return true;
		}
	}
	return false;

}
//check collisions between enemies and bullets and destroy them both
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
				//play projectile explosion sound
				audioManager_->ExplosionAudio();
				StateManager::KillEnemy();
			}
		}

	}
}
//check if projectiles collide with meteor to destroy the projectile
void Player::CheckProjecAsterCollisions(std::vector<AutoEntity*>& others)
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

				bullet->StillAlive = false;
				//play projectile explosion sound
				if (audioManager_) audioManager_->ExplosionAudio();
			}
		}

	}
}

bool Player::CheckBossProjectileCollision(ProjectileManager& bossProjectiles)
{
	auto& enemyBullets = bossProjectiles.GetEntities();

	for (auto& bullet : enemyBullets)
	{
		if (bullet->StillAlive && rect_.getGlobalBounds().findIntersection(bullet->GetBounds()))
		{
			bullet->StillAlive = false;

			StateManager::LostLife();

			if (audioManager_) audioManager_->ExplosionAudio();

			// player hit
			return true;
		}
	}
	return false;
}


//player input (mouvement and shoot)
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
	//shoot
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space))
	{
		//prevent mass missiles when spacebar is pressed
		if(shootClock_.getElapsedTime().asSeconds() > Shoot_Delay)
		{
			//play shooting sound
			if (audioManager_) audioManager_->ShootAudio();
			projectiles.InitEntities(rect_.getPosition());

			shootClock_.restart();
		}
		
		
	}
	
	motor_.SetDirection(direction);
}
//set player position
void Player::SetPosition(sf::Vector2f position)
{
	motor_.SetPosition(position);
}
//draw player character
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//sf::Sprite sprite(Spaceshipe);
	target.draw(projectiles);
	target.draw(rect_, states);
	
}