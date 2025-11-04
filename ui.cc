#include "ui.hpp"
#include "state_manager.hpp"


void UI::Load(sf::RenderWindow& window)
{
	font_.openFromFile("data\\fonts\\SoleSurvivorRegular.ttf");

	scoreLabel_ = sf::Text(font_);

	if (scoreLabel_.has_value())
	{
		scoreLabel_->setCharacterSize(40);
		scoreLabel_->setFillColor(sf::Color::White);
		scoreLabel_->setString("Score :");
		scoreLabel_->setPosition({ window.getSize().x / 2.f - scoreLabel_->getLocalBounds().size.x, 50.f });
	}
		
	score_ = sf::Text(font_);

	if (score_.has_value())
	{
		score_->setCharacterSize(40);
		score_->setFillColor(sf::Color::White);
		score_->setPosition({ scoreLabel_->getPosition().x, 80.f });
		//score_->setString("0000");
	}
		
}

void UI::Update()
{
	SetScore(StateManager::Score());
	//SetLife(3, 5);
}

void UI::SetScore(int score)
{
	score_->setString(std::to_string(score));
}

//void UI::SetLife(int actual_life, int max_life)
//{
//	//actual_life_ = actual_life;
//	//max_life_ = max_life;
//}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (scoreLabel_.has_value())
	{
		target.draw(scoreLabel_.value());
		target.draw(score_.value());
	}
}

