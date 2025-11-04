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
private:
	sf::Music music_;               // for longer music
	sf::SoundBuffer shootBuffer_;   // for  shooting sound
	sf::SoundBuffer explosionBuffer_;//for explosion sound

	std::optional<sf::Sound> shootSound_;
	std::optional<sf::Sound> explosionSound_;


   
};



