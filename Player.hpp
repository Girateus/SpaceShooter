#pragma once

#include <iostream>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

#include "entityManager.hpp"
#include "auto_entity.hpp"
#include "Motor.hpp"
#include "AudioManager.hpp"

class AudioManager;
class Player : public sf::Drawable
{
	
	sf::Texture Spaceshipe;
	sf::RectangleShape rect_;
	Motor motor_;
	AudioManager* audioManager_ = nullptr;
	sf::Clock shootClock_;
	const float Shoot_Delay = 0.2f;

	ProjectileManager projectiles;

public:	
	void SetAudioManager(AudioManager* audioManager);
	void Load(sf::Vector2f);
	void Update(sf::RenderWindow&, float);
	bool CheckCollision(std::vector<AutoEntity*>& others);
	void CheckProjectileCollisions(std::vector<AutoEntity*>& others);
	void CheckProjecAsterCollisions(std::vector<AutoEntity*>& others);
	bool CheckBossProjectileCollision(ProjectileManager& bossProjectiles);
	void HandleEvent();
	ProjectileManager& GetProjectiles()
	{ 
		return projectiles; 
	}

	void SetPosition(sf::Vector2f);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
};
