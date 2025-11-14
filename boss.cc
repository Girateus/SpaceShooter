#include "boss.hpp"
#include <iostream>

void Boss::Load(const sf::Vector2f& initialPosition)
{
    //load texture
    if (!texture_.loadFromFile("data\\sprites\\Enemies\\Nico.png"))
    {
        std::cerr << "Erreur: Impossible de charger la texture du boss." << std::endl;
    }

    rect_.setTexture(&texture_);
    rect_.setSize({ static_cast<float>(texture_.getSize().x), static_cast<float>(texture_.getSize().y) });
    rect_.setOrigin({ rect_.getSize().x / 2.f, rect_.getSize().y / 2.f });

    motor_.SetPosition(initialPosition);
    motor_.SetDirection({ 0.0f, 1.0f }); 
    motor_.SetSpeed(50.0f);

    // starting position
    rect_.setPosition(initialPosition);
}
//move the boss to a certain position
void Boss::Move(float deltaTime)
{
     sf::Vector2f currentPos = motor_.GetPosition();

     if (currentPos.y < STOP_Y_POSITION)
    {
       
        sf::Vector2f newPos = motor_.Move(deltaTime);
        rect_.setPosition(newPos);
    }
    // stop mouvement
    else
    {
        
        if (motor_.GetDirection().y != 0.0f || motor_.GetDirection().x != 0.0f)
        {
            motor_.SetDirection({ 0.0f, 0.0f });
  
            motor_.SetPosition({ currentPos.x, STOP_Y_POSITION });
        }

       
        rect_.setPosition(motor_.GetPosition());

       
    }
}
//check collision betwen the player and the boss projectiles
void Boss::CheckPlayerCollisions(ProjectileManager& playerProjectiles)
{
    if (!isAlive_) return;

    auto& bullets = playerProjectiles.GetEntities();

   
    for (size_t i = 0; i < bullets.size(); ++i)
    {
        if (bullets[i]->StillAlive && rect_.getGlobalBounds().findIntersection(bullets[i]->GetBounds()))
        {
            health_--;
            bullets[i]->StillAlive = false;

            if (health_ <= 0)
            {
                StateManager::KillBoss();
                isAlive_ = false;
                std::cout <<  "Boss defeated" << std::endl;
                return;
            }
        }
    }
}

void Boss::HandleShooting(ProjectileManager& bossProjectiles)
{
    //start shooting when the boss reach a certain position
    if (rect_.getPosition().y < STOP_Y_POSITION) return;

    if (isAlive_)
    {
        if (shootClock_.getElapsedTime().asSeconds() >= bossShootDelay)
        {
            const int NUM_SHOTS = 25; 
            //allow the boss to shoot in envery direction of a circle
            const float ANGLE_STEP = 2 * 3.14159f / 15.0f;

            for (int i = 0; i < NUM_SHOTS; ++i)
            {
                
                float angle = spiralAngle_ + static_cast<float>(i) * ANGLE_STEP;

                sf::Vector2f direction;
                direction.x = std::cos(angle);
                direction.y = std::sin(angle);

                bossProjectiles.InitEntities(rect_.getPosition(), direction);
            }

            
            spiralAngle_ += 5.0f * (3.14159f / 180.0f);

            if (spiralAngle_ > 6.28318f) // 2 * Pi
            {
                spiralAngle_ -= 6.28318f;
            }

            shootClock_.restart();
        }
    }
    
}

void Boss::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (isAlive_)
    {
        target.draw(rect_, states);
    }
    
}


sf::FloatRect Boss::GetBounds() const
{
    return rect_.getGlobalBounds();
}