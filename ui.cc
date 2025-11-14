#include "ui.hpp"
#include "state_manager.hpp"


void UI::Load(sf::RenderWindow& window)
{
	font_.openFromFile("data\\fonts\\SoleSurvivorRegular.ttf");

	scoreLabel_ = sf::Text(font_);
	score_ = sf::Text(font_);
	lifeLabel_ = sf::Text(font_);
	life_ = sf::Text(font_);
	gameOver_ = sf::Text(font_);
	credits_ = sf::Text(font_);

	if (lifeLabel_.has_value())
	{
		lifeLabel_->setCharacterSize(40);
		lifeLabel_->setFillColor(sf::Color::White);
		lifeLabel_->setString("life :");
		lifeLabel_->setPosition({ window.getSize().x / 3.f - lifeLabel_->getLocalBounds().size.x, 50.f });
	}
	
	if (life_.has_value())
	{
		life_->setCharacterSize(40);
		life_->setFillColor(sf::Color::White);
		life_->setPosition({ lifeLabel_->getPosition().x, 80.f });
		life_->setString("5");

	}
	

	if (scoreLabel_.has_value())
	{
		scoreLabel_->setCharacterSize(40);
		scoreLabel_->setFillColor(sf::Color::White);
		scoreLabel_->setString("Score :");
		scoreLabel_->setPosition({ window.getSize().x / 2.f - scoreLabel_->getLocalBounds().size.x, 50.f });
	}
		
	

	if (score_.has_value())
	{
		score_->setCharacterSize(40);
		score_->setFillColor(sf::Color::White);
		score_->setPosition({ scoreLabel_->getPosition().x, 80.f });
		score_->setString("0000");
	}

	if (gameOver_.has_value())
	{
		gameOver_->setCharacterSize(200);
		gameOver_->setFillColor(sf::Color::Red);
		gameOver_->setString("GAME OVER");
		gameOver_->setPosition({ window.getSize().x / 2.85f - lifeLabel_->getLocalBounds().size.x, 450.f });
	}

	if (credits_.has_value())
	{
		credits_->setCharacterSize(40);
		credits_->setFillColor(sf::Color::White);
		credits_->setString("Un jeu de Noah P. Munoz\nSous la direction de Sebastien Albert\nAvec la Participation de Alexander Samuel King, Tibo Benjamin Robert-Nicoud,\nArthur Melchior et Gaëtan Meyer\nMerci d'avoir joué !!");
		credits_->setPosition({ window.getSize().x / 2.85f - lifeLabel_->getLocalBounds().size.x, 450.f });
	}
		
}

void UI::Update()
{
	SetScore(StateManager::Score());
	SetLife(StateManager::Life());

	if (StateManager::Life() <= 0 && !isGameOver_ && !isGameCompleted_)
	{
		isGameOver_ = true;
	}

}

void UI::SetScore(int score)
{
	score_->setString(std::to_string(score));
}

void UI::SetLife(int lives)
{
	life_->setString(std::to_string(lives));
}


void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!isGameOver_ && !isGameCompleted_)
	{
		// Draw standar UI
		if (scoreLabel_.has_value())
		{
			target.draw(scoreLabel_.value());
			target.draw(score_.value());
		}

		if (lifeLabel_.has_value())
		{
			target.draw(lifeLabel_.value());
			target.draw(life_.value());
		}
	}
	//victory
	else if (isGameCompleted_)
	{
		// draw credits
		if (scoreLabel_.has_value())
		{
			target.draw(scoreLabel_.value());
			target.draw(score_.value());
		}

		if (credits_.has_value())
		{
			target.draw(credits_.value());
		}
	}
	// lost
	else if (isGameOver_)
	{
		// draw Game Over
		if (gameOver_.has_value())
		{
			target.draw(gameOver_.value());
		}
	}
	
}

