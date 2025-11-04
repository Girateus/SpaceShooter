#include <iostream>

#include <SFML/Audio.hpp>
#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"
#include "Player.hpp"
#include "Projectiles.hpp"
#include "entityManager.hpp"
#include "Motor.hpp"
#include "Meteor.hpp"
#include "Randomizer.hpp"
#include "auto_entity.hpp"
#include "Enemy.hpp"
#include "ui.hpp"
#include "AudioManager.hpp"

int main()
{
	constexpr sf::Vector2f playerSpawnPosition = { 960, 600 };

	sf::RenderWindow window(sf::VideoMode({ 1920, 1200 }), "Star Shooter");

	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(120);

	window.setKeyRepeatEnabled(true);

	sf::Clock clock;
	//sf::Time time = clock.getElapsedTime();
	
	
	

	RandomInit();
	AudioManager audio;
	Motor motor;
	motor.SetPosition({ 0,0 });
	motor.SetDirection({ 1,0 });
	motor.SetSpeed({ 10 });

	//sf::CircleShape circle;
	//circle.setRadius(5);
	Player player;
	player.Load(playerSpawnPosition);
	player.SetAudioManager(&audio);

	/*Enemy enemy;
	enemy.Load();*/
	EnemyManager enemies;
	MeteorManager meteor;


sf::Clock enemySpawnClock;
		sf::Clock meteorSpawnClock;

		const float ENEMY_SPAWN_DELAY = 0.9f;   // en secondes
		const float METEOR_SPAWN_DELAY = 1.0f;  // en secondes
	

	UI ui;
	ui.Load(window);
	audio.PlayAudio();
	float volume = 50;

	sf::Color background_color(sf::Color::Black);

	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
				

		//play audio
		
		

		
		
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
					//PlayAudio().stop();
				}
					

				
				if (keyPressed->scancode == sf::Keyboard::Scancode::Tab)
				{

				}
			}

			
		}

		



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
		player.Update(window ,deltaTime.asSeconds());
		//player.Move(deltaTime.asSeconds());
		meteor.Update(window,deltaTime.asSeconds());
		//meteor.Move(deltaTime.asSeconds());  
		enemies.Update(window, deltaTime.asSeconds());
		//player.setPosition({ 0,0});
		ui.Update();
		// check to make spawn new enemy
		if (enemySpawnClock.getElapsedTime().asSeconds() >= ENEMY_SPAWN_DELAY)
		{
			float xEnemy = RandomSpawnX(1.f, 1920.f);
			enemies.InitEntities({ xEnemy, 0 });
			enemySpawnClock.restart();
		}

		// check to make spawn new meteor
		if (meteorSpawnClock.getElapsedTime().asSeconds() >= METEOR_SPAWN_DELAY)
		{
			float xMeteor = RandomSpawnX(1.f, 1920.f);
			meteor.InitEntities({ xMeteor, 0 });
			meteorSpawnClock.restart();
		}

		
		window.clear(background_color);

		//draw entities
		window.draw(player);
		window.draw(meteor);
		window.draw(enemies);
		window.draw(ui);
		

		window.display();
	}
}