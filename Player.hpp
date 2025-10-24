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

class Player : public sf::Drawable
{
	sf::Texture Spaceshipe;
	sf::RectangleShape rect_;
	Motor motor_;

	ProjectileManager projectiles;

public:	
	void Load(sf::Vector2f);
	void Update(sf::RenderWindow&, float);
	bool CheckCollision(std::vector<AutoEntity*>& others);
	void CheckProjectileCollisions(std::vector<AutoEntity*>& others);
	void HandleEvent();

	void SetPosition(sf::Vector2f);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
};
