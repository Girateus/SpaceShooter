#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

#include "Player.hpp"
#include "Projectiles.hpp"
#include "entityManager.hpp"
#include "Motor.hpp"
#include "Randomizer.hpp"
#include "auto_entity.hpp"
#include "ui.hpp"
#include "AudioManager.hpp"
#include "state_manager.hpp"
#include "boss.hpp"

int main()
{
	constexpr sf::Vector2f playerSpawnPosition = { 960, 1000 };

	sf::RenderWindow window(sf::VideoMode({ 1920, 1200 }), "Star Shooter");

	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(120);

	window.setKeyRepeatEnabled(true);

	sf::Clock clock;
	

	RandomInit();
	AudioManager audio;
	Motor motor;
	motor.SetPosition({ 0,0 });
	motor.SetDirection({ 1,0 });
	motor.SetSpeed({ 10 });

	Player player;
	player.Load(playerSpawnPosition);
	player.SetAudioManager(&audio);

	EnemyManager enemies;
	MeteorManager meteor;
	Boss boss;
	ProjectileManager bossProjectiles;

//entity spawn clock
	sf::Clock enemySpawnClock;
	sf::Clock meteorSpawnClock;

	sf::Texture backgroundTexture;

	if (!backgroundTexture.loadFromFile("data/sprites/background.png"))
	{
		std::cout << "Error loading background image\n";
	}
	sf::Sprite backgroundSprite(backgroundTexture);

	const float EnemySpawnDelay = 0.5f;   // in secondes
	const float MeteorSpawnDelay = 1.f;  // in secondes
	
	bool bossPhase = false;
	bool endMusicStarted = false;
	
	UI ui;
	ui.Load(window);
	audio.PlayAudio();
	float volume = 50;

	sf::Color background_color(sf::Color::Black);

	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		
		audio.Update(deltaTime.asSeconds());		
		
		while (const std::optional event = window.pollEvent())
		{

			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				{
					window.close();
				}
			}
		}
		
		ui.Update();

		if (bossPhase && !boss.IsAlive())
		{
			if (!ui.IsGameCompleted()) 
			{
				ui.SetGameCompleted(true);
				//StateManager::KillBoss(); 			
			}
		}

		if (ui.IsGameFinished()) 		{
			if (!endMusicStarted) 
			{
				endMusicStarted = true; 

				if (ui.IsGameCompleted()) // VICTORY
				{
					// cue the CREDITS
					audio.PlayCreditsMusic("data/Audio/credits.wav");
				}
				else // Defeat
				{
					
					audio.StopAllSounds();
				}
			}
		}
		
		if(!ui.IsGameFinished())
		{
			//Physics
			sf::Vector2f position = motor.Move(deltaTime.asSeconds());
			std::cout << position.x << ":" << position.y << "\n";



			player.HandleEvent();
			if (player.CheckCollision(enemies.GetEntities()) || player.CheckCollision(meteor.GetEntities()))
			{
				player.SetPosition(playerSpawnPosition);
			}
			player.CheckProjectileCollisions(enemies.GetEntities());
			player.CheckProjecAsterCollisions(meteor.GetEntities());
			boss.CheckPlayerCollisions(player.GetProjectiles());
			if (player.CheckBossProjectileCollision(bossProjectiles))
			{
				player.SetPosition(playerSpawnPosition);
			}
			player.Update(window, deltaTime.asSeconds());
			meteor.Update(window, deltaTime.asSeconds());
			enemies.Update(window, deltaTime.asSeconds());
			boss.Move(deltaTime.asSeconds());
			boss.HandleShooting(bossProjectiles);
			bossProjectiles.Update(window, deltaTime.asSeconds());

			if (!bossPhase)
			{
				if (StateManager::Score() >= 100)
				{

					if (!bossPhase)
					{
						bossPhase = true;

						// change audio
						audio.StartBossTrack("data/Audio/Boss.wav");

						//play audio intro
						audio.NicoSound();

						//Spawne the boss
						boss.Load({ 960.0f, 0.0f });
					}
				}

				else
				{
					if (enemySpawnClock.getElapsedTime().asSeconds() >= EnemySpawnDelay)
					{
						float xEnemy = RandomSpawnX(1.f, 1920.f);
						enemies.InitEntities({ xEnemy, 0 });
						enemySpawnClock.restart();
					}

					// check to make spawn new meteor
					if (meteorSpawnClock.getElapsedTime().asSeconds() >= MeteorSpawnDelay)
					{
						float xMeteor = RandomSpawnX(1.f, 1920.f);
						meteor.InitEntities({ xMeteor, 0 });
						meteorSpawnClock.restart();
					}
				}
			}
		}
		window.clear(background_color);

		window.draw(backgroundSprite);
		if (!ui.IsGameFinished())
		{
			//draw entities
			window.draw(player);
			window.draw(meteor);
			window.draw(enemies);
			window.draw(bossProjectiles);
			window.draw(boss);
		}
		window.draw(ui);
		

		window.display();
	}
}