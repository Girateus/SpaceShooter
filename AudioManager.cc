#include "AudioManager.hpp"
#include <iostream>

AudioManager::AudioManager()
{
	

	if (!music_.openFromFile("data/Audio/Wind of Madness.wav"))
		std::cout << "Error : couldn't load music.\n";

	if (!shootBuffer_.loadFromFile("data/Audio/Laser2.ogg"))
		std::cout << "Error : couldn't load shooting sound.\n";

	if (!explosionBuffer_.loadFromFile("data/Audio/Explosion1.ogg"))
		std::cout << "Error : couldn't load explosion sound.\n";


	shootSound_.emplace(shootBuffer_);
	explosionSound_.emplace(explosionBuffer_);

	shootSound_->setVolume(15);
	explosionSound_->setVolume(15);

	music_.setLooping(true);
	music_.setVolume(30);


}

void AudioManager::PlayAudio()
{
	music_.play();
}

void AudioManager::ShootAudio()
{
	if (shootSound_.has_value())
	{
		shootSound_->play();
	}

}

void AudioManager::ExplosionAudio()
{
	if (explosionSound_.has_value())
	{
		explosionSound_->play();
	}
}
