#pragma once
#include <iostream>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

class UI : public sf::Drawable
{
private:
	sf::RectangleShape bigFrame_;
	sf::RectangleShape scoreFrame_;

	std::optional<sf::Text> scoreLabel_;
	std::optional<sf::Text> score_;

	std::optional<sf::Text> lifeLabel_;
	std::optional<sf::Text> life_;

	std::optional<sf::Text> gameOver_;

	std::optional<sf::Text> credits_;


	sf::Font font_;
	void SetScore(int);
	void SetLife(int);
	

	bool isGameOver_ = false;
	bool isGameCompleted_ = false;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Load(sf::RenderWindow&);
	void Update();
	void SetGameCompleted(bool completed) { isGameCompleted_ = completed; }
	bool IsGameOver() const { return isGameOver_; }
	bool IsGameCompleted() const { return isGameCompleted_; }
	bool IsGameFinished() const { return isGameOver_ || isGameCompleted_; }
	
};

