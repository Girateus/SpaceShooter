/*#include "Meteor.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics//RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

void Meteor::Load()
{
	meteorTexture.loadFromFile("data\\sprites\\Meteors\\meteorBrown_big1.png", {0, 1}, 100);
AutoEntity::Load("data\\sprites\\Meteors\\meteorBrown_big2.png", { 0, 1 }, 100);
AutoEntity::Load("data\\sprites\\Meteors\\meteorBrown_big3.png", { 0, 1 }, 100);
AutoEntity::Load("data\\sprites\\Meteors\\meteorBrown_big4.png", { 0, 1 }, 100);
AutoEntity::Load("data\\sprites\\Meteors\\meteorGrey_big1.png", { 0, 1 }, 100);
AutoEntity::Load("data\\sprites\\Meteors\\meteorGrey_big2.png", { 0, 1 }, 100);
AutoEntity::Load("data\\sprites\\Meteors\\meteorGrey_big3.png", { 0, 1 }, 100);
AutoEntity::Load("data\\sprites\\Meteors\\meteorGrey_big4.png", { 0, 1 }, 100);*/
//	motor_.SetPosition({ 500,0 });
//	motor_.SetDirection({ 0,-1 });
//	motor_.SetSpeed({ 100 });
//}
//void Meteor::Move(float deltaTime)
//{
//	setPosition(motor_.Move(deltaTime));
//}
//void Meteor::Update()
//{
//	motor_.SetDirection({ 0,1 });
//}
//
//void Meteor::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//	sf::Clock clock;
//	auto deltaTime = clock.restart();
//	sf::Sprite sprite(MeteorTexture);
//	states.transform *= getTransform();
//	sprite.setOrigin({ static_cast<float>(MeteorTexture.getSize().x/2), static_cast<float>(MeteorTexture.getSize().y/2) });
//
//	
//	sprite.setRotation(sf::degrees(170));
//	sprite.rotate(sf::degrees(10.f * deltaTime.asSeconds()));
//	target.draw(sprite, states);
//
//}