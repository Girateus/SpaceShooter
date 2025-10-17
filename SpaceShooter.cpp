#include <iostream>

#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"
#include "Player.hpp"
//#include "Projectiles.hpp"
#include "Motor.hpp"
#include "Enemy.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1000, 800 }), "Star Shooter");

	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(120);

	window.setKeyRepeatEnabled(true);

	sf::Clock clock;
	sf::Time time = clock.getElapsedTime();
	

	Motor motor;
	motor.SetPosition({ 0,0 });
	motor.SetDirection({ 1,0 });
	motor.SetSpeed({ 10 });

	//sf::CircleShape circle;
	//circle.setRadius(5);
	Player player;
	player.Load();
	Enemy enemy;
	enemy.Load();

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
			}

			
		}



		//Physics
		//sf::Vector2f followMouseDirection = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) - circle.getPosition();

		//motor.SetDirection(followMouseDirection);

		sf::Vector2f position = motor.Move(deltaTime.asSeconds());
		std::cout << position.x << ":" << position.y << "\n";
		//circle.setPosition(position);
		

		player.HandleEvent();
		player.Move(deltaTime.asSeconds());
		//player.setPosition({ 0,0});

		window.clear(background_color);

		//window.draw(circle);
		window.draw(player);
		window.draw(enemy);

		window.display();
	}
}