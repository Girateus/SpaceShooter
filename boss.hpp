#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "Motor.hpp"
#include "entityManager.hpp"
#include "auto_entity.hpp"
#include "state_manager.hpp"

class ProjectileManager;

class Boss : public sf::Drawable
{
private:
    sf::Texture texture_;
    sf::RectangleShape rect_;
    Motor motor_;

    // Position Y where the boss should stop
    const float STOP_Y_POSITION = 250.0f;

    int health_ = 150;
    bool isAlive_ = true;

    sf::Clock shootClock_;
    const float bossShootDelay = 0.95f;
    float spiralAngle_ = 0.0f;
public:

    // load image and position
    void Load(const sf::Vector2f& initialPosition);

    void Move(float deltaTime);

    sf::FloatRect GetBounds() const;
    bool IsAlive() const 
    {
        return isAlive_; 
    }

    // check collision
    void CheckPlayerCollisions(ProjectileManager& playerProjectiles);

    // handle shooting
    void HandleShooting(ProjectileManager& bossProjectiles);

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};