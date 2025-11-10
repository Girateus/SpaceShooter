#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
#include <optional>
#include <iostream>
class AudioManager
{
public:
	AudioManager();
    
	void PlayAudio();//sf::Music
	void ShootAudio();//sf::Sound
	void ExplosionAudio();//sf::Sound
	void NicoSound();//sf::Sound

	void StartBossTrack(const std::string& filename);
	void Update(float deltaTime);
private:
	sf::Music music_; // for longer music
	sf::Music bossMusic_;

	bool fadingOut = false;
	const float fadeOutDuration = 2.0f;
	float fadeTimer = 0.0f;
	float initialVolume = 0.0f;

	sf::SoundBuffer shootBuffer_;   // for shooting sound
	sf::SoundBuffer explosionBuffer_;//for explosion sound
	sf::SoundBuffer bonjourBuffer_;//for Nico intro

	std::optional<sf::Sound> shootSound_;
	std::optional<sf::Sound> explosionSound_;
	std::optional<sf::Sound> bonjourSound_;


   
};



