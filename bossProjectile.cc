#include "bossProjectile.hpp"

void BossProjectile::Move(float deltaTime)
{
	rect_.setPosition(motor_.Move(deltaTime));
}

void BossProjectile::Load()
{
	// Charger la texture du boss (ex: laserRed08.png)
	// Assurez-vous d'avoir ce fichier dans votre répertoire de données
	AutoEntity::Load("data\\sprites\\Lasers\\laserRed08.png", { 0, 1 }, 200); // Vitesse plus lente pour les tirs ennemis
}