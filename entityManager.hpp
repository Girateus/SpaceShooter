#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Projectiles.hpp"
#include "Enemy.hpp"
class EntityManager : public sf::Drawable
{
	

public:
	virtual void InitEntities(sf::Vector2f) = 0;
	void Update(sf::RenderWindow&, float deltaTime);
	std::vector<AutoEntity*>& GetEntities();

protected:
	std::vector<AutoEntity*> entities_;
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	
};

class EnemyManager : public EntityManager
{
public:
	void InitEntities(sf::Vector2f position) override
	{
		entities_.emplace_back(new Enemy());


		entities_.back()->Load();
		entities_.back()->SetPosition(position);
	}
};

class ProjectileManager : public EntityManager
{
public:
	void InitEntities(sf::Vector2f position) override
	{
		entities_.emplace_back(new Projectile());


		entities_.back()->Load();
		entities_.back()->SetPosition(position);
	}
};

