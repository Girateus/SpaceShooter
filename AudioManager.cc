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

	if (!bonjourBuffer_.loadFromFile("data/Audio/Nico.wav"))
		std::cout << "Error : couldn't load intro sound.\n";

	if (!bossEndBuffer_.loadFromFile("data/Audio/Boss_End.wav"))
		std::cout << "Error : couldn't load intro sound.\n";

	if (!gameOverBuffer_.loadFromFile("data/Audio/GameOver.wav"))
		std::cout << "Error : couldn't load intro sound.\n";


	shootSound_.emplace(shootBuffer_);
	explosionSound_.emplace(explosionBuffer_);
	bonjourSound_.emplace(bonjourBuffer_);
	bossEndSound_.emplace(bossEndBuffer_);
	gameOverSound_.emplace(gameOverBuffer_);

	shootSound_->setVolume(12);
	explosionSound_->setVolume(12);
	bonjourSound_->setVolume(100);
	bossEndSound_->setVolume(100);
	gameOverSound_->setVolume(100);


	music_.setLooping(true);
	music_.setVolume(40);

	bossMusic_.setLooping(true);
	bossMusic_.setVolume(0.0f);

	


}

void AudioManager::StartBossTrack(const std::string& filename)
{
	if (!bossMusic_.openFromFile(filename))
	{
		std::cout << "Error: Couldn't load boss music from " << filename << std::endl;
		return;
	}

	initialVolume = music_.getVolume();
	fadeTimer = 0.0f;
	fadingOut = true;

	bossMusic_.play();
}

void AudioManager::Update(float deltaTime)
{
	if (fadingOut)
	{
		fadeTimer += deltaTime;

		
		float progress = std::min(fadeTimer / fadeOutDuration, 1.0f);

		
		float currentVolume = initialVolume * (1.0f - progress);

		
		music_.setVolume(currentVolume);

		float bossMaxVolume = 35.0f;
		bossMusic_.setVolume(bossMaxVolume * progress);


		if (progress >= 1.0f)
		{
			music_.stop();
			fadingOut = false;
		}
	}
}

void AudioManager::StopAllSounds()
{
	music_.stop();
	bossMusic_.stop();
	credit_.stop();

	
	if (shootSound_.has_value()) shootSound_->stop();
	if (explosionSound_.has_value()) explosionSound_->stop();
	if (bonjourSound_.has_value()) bonjourSound_->stop();
}


void AudioManager::PlayCreditsMusic(const std::string& filename)
{
	StopAllSounds();

	if (!credit_.openFromFile(filename))
	{
		std::cout << "Error credits song couldn't load " << filename << std::endl;
		return;
	}

	credit_.setLooping(true);
	credit_.setVolume(40.f);
	credit_.play();
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

void AudioManager::NicoSound()
{
	bonjourSound_->play();
}

void AudioManager::GameOverSound()
{
	gameOverSound_->play();
}

void AudioManager::BossEndSound()
{
	bossEndSound_->play();
}
