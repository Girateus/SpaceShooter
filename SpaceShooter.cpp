#include <iostream>

#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"
#include "Player.hpp"
#include "Projectiles.hpp"
#include "entityManager.hpp"
#include "Motor.hpp"
#include "Meteor.hpp"
#include "Randomizer.h"
#include "auto_entity.hpp"
#include "Enemy.hpp"

int main()
{
	constexpr sf::Vector2f playerSpawnPosition = { 400, 580 };

	sf::RenderWindow window(sf::VideoMode({ 1000, 800 }), "Star Shooter");

	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(120);

	window.setKeyRepeatEnabled(true);

	sf::Clock clock;
	//sf::Time time = clock.getElapsedTime();
	
	
	

	RandomInit();

	Motor motor;
	motor.SetPosition({ 0,0 });
	motor.SetDirection({ 1,0 });
	motor.SetSpeed({ 10 });

	//sf::CircleShape circle;
	//circle.setRadius(5);
	Player player;
	player.Load(playerSpawnPosition);

	/*Enemy enemy;
	enemy.Load();*/
	EnemyManager enemies;

	Meteor meteor;
	meteor.Load();

	sf::Color background_color(sf::Color::Black);

	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();

		while (const std::optional event = window.pollEvent())
		{

			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
					window.close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
				{

				}

				if(keyPressed->scancode == sf::Keyboard::Scancode::E)
				{
					enemies.InitEntities({ 400, 0 });
				}
			}

			
		}

		



		//Physics
		//sf::Vector2f followMouseDirection = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) - circle.getPosition();

		//motor.SetDirection(followMouseDirection);

		sf::Vector2f position = motor.Move(deltaTime.asSeconds());
		std::cout << position.x << ":" << position.y << "\n";
		//circle.setPosition(position);
		

		player.HandleEvent();
		if (player.CheckCollision(enemies.GetEntities()))
		{
			player.SetPosition(playerSpawnPosition);
		}
		player.CheckProjectileCollisions(enemies.GetEntities());
		player.Update(window ,deltaTime.asSeconds());
		//player.Move(deltaTime.asSeconds());
		meteor.Update();
		meteor.Move(deltaTime.asSeconds());  
		enemies.Update(window, deltaTime.asSeconds());
		//player.setPosition({ 0,0});
		
		
		window.clear(background_color);

		//window.draw(circle);
		window.draw(player);
		window.draw(meteor);
		window.draw(enemies);
		

		window.display();
	}
}