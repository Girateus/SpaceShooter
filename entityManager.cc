#include "entityManager.hpp"
#include <iostream>
#include <algorithm>


void EntityManager::Update(sf::RenderWindow& window, float deltaTime)
{
	erase_if(entities_, [&window](AutoEntity* p)
	{
			return p->GetPosition().y < 0 || p->GetPosition().y > window.getSize().y || p->StillAlive == false;
	}
	);

	 
	for (auto& entity : entities_)
	{

		entity->Move(deltaTime);
	}
	
}


void EntityManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& projectile : entities_)
	{
		target.draw(*projectile);
	}
}

std::vector<AutoEntity*>& EntityManager::GetEntities()
{
	return entities_;
}