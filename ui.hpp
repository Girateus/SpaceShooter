#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class UI : public sf::Drawable
{
private:
	//sf::Texture Texture_;
	sf::RectangleShape bigFrame_;
	sf::RectangleShape scoreFrame_;

	std::optional<sf::Text> scoreLabel_;
	std::optional<sf::Text> score_;

	sf::RectangleShape lifeIcon_;

	sf::Font font_;
	void SetScore(int);
	//void SetLife(int, int);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Load(sf::RenderWindow&);
	void Update();

	
};

