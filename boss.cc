#include "boss.hpp"
#include <iostream>


// Implémentation du chargement et de l'initialisation
void Boss::Load(const sf::Vector2f& initialPosition)
{
    // 1. Chargement de la texture
    if (!texture_.loadFromFile("data\\sprites\\Enemies\\Nico.png"))
    {
        std::cerr << "Erreur: Impossible de charger la texture du boss." << std::endl;
        // Gérer l'erreur (par exemple, utiliser une texture par défaut ou quitter)
    }

    // 2. Configuration du Rectangle (la partie visible)
    rect_.setTexture(&texture_);
    // Assurez-vous d'utiliser la taille appropriée
    rect_.setSize({ static_cast<float>(texture_.getSize().x), static_cast<float>(texture_.getSize().y) });
    // Configurer l'origine au centre (souvent utile)
    rect_.setOrigin({ rect_.getSize().x / 2.f, rect_.getSize().y / 2.f });

    // 3. Configuration du Moteur (Moteur hérité de AutoEntity::Load)
    motor_.SetPosition(initialPosition);
    motor_.SetDirection({ 0.0f, 1.0f }); // Direction initiale : vers le bas
    motor_.SetSpeed(50.0f);              // Vitesse initiale (par exemple, 50)

    // Positionner le rect initialement
    rect_.setPosition(initialPosition);
}

// Implémentation du mouvement avec arrêt
void Boss::Move(float deltaTime)
{
    // Récupère la position actuelle du moteur
    sf::Vector2f currentPos = motor_.GetPosition();

    // 1. Phase de descente
    if (currentPos.y < STOP_Y_POSITION)
    {
        // Continue de bouger et met à jour la position
        sf::Vector2f newPos = motor_.Move(deltaTime);
        rect_.setPosition(newPos);
    }
    // 2. Phase d'arrêt
    else
    {
        // Vider la direction pour figer le mouvement (si ce n'est pas déjà fait)
        if (motor_.GetDirection().y != 0.0f || motor_.GetDirection().x != 0.0f)
        {
            motor_.SetDirection({ 0.0f, 0.0f });
            // S'assurer que le moteur est exactement à la position d'arrêt
            motor_.SetPosition({ currentPos.x, STOP_Y_POSITION });
        }

        // Mettre à jour la position du rectangle avec la position figée du moteur
        rect_.setPosition(motor_.GetPosition());

        // ** AJOUTEZ ICI LA LOGIQUE DE TIR DU BOSS **
    }
}

void Boss::CheckPlayerCollisions(ProjectileManager& playerProjectiles)
{
    if (!isAlive_) return;

    auto& bullets = playerProjectiles.GetEntities();

    // Itérer sur les projectiles du joueur (qui sont des AutoEntity*)
    for (size_t i = 0; i < bullets.size(); ++i)
    {
        if (bullets[i]->StillAlive && rect_.getGlobalBounds().findIntersection(bullets[i]->GetBounds()))
        {
            health_--;
            bullets[i]->StillAlive = false; // Détruire le projectile

            // Si vous avez un AudioManager* dans Boss (non visible ici), jouez le son d'impact

            if (health_ <= 0)
            {
                isAlive_ = false;
                std::cout << "Le Boss est vaincu!" << std::endl;
                // TO DO: Déclencher l'explosion visuelle, arrêter la musique, etc.
                return;
            }
        }
    }
}

void Boss::HandleShooting(ProjectileManager& bossProjectiles)
{
    if (rect_.getPosition().y < STOP_Y_POSITION) return; // Ne tire pas tant qu'il descend

    if (shootClock_.getElapsedTime().asSeconds() >= BOSS_SHOOT_DELAY)
    {
        // Tirez dans 8 directions (0, 45, 90, 135, ..., 315 degrés)
        for (int i = 0; i < 16; ++i)
        {
            float angle = static_cast<float>(i) * (2.0f*3.14159f / 16.0f);

            sf::Vector2f direction;
            direction.x = std::cos(angle);
            direction.y = std::sin(angle);

            // Initialiser le projectile avec la position du boss et la direction calculée
            bossProjectiles.InitEntities(rect_.getPosition(), direction);
        }
        shootClock_.restart();
    }
}

// Implémentation de l'affichage
void Boss::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(rect_, states);
}

// Implémentation de GetBounds (important pour les collisions)
sf::FloatRect Boss::GetBounds() const
{
    return rect_.getGlobalBounds();
}