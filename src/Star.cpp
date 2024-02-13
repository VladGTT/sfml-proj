#include "Star.hpp"

Star::Star(sf::Vector2f scale, sf::Color color, bool is_hidden, sf::Vector2f position)
{
	sf::ConvexShape* star=new sf::ConvexShape(10);
	
	star->setPoint(0, sf::Vector2f(60, 0));
	star->setPoint(1, sf::Vector2f(72, 40));
	star->setPoint(2, sf::Vector2f(110, 40));
	star->setPoint(3, sf::Vector2f(80, 60));
	star->setPoint(4, sf::Vector2f(100, 100));
	star->setPoint(5, sf::Vector2f(60, 75));
	star->setPoint(6, sf::Vector2f(20, 100));
	star->setPoint(7, sf::Vector2f(40, 60));
	star->setPoint(8, sf::Vector2f(10, 40));
	star->setPoint(9, sf::Vector2f(48, 40));

	shape = star;
	setColor(color);
	setScale(scale);
	setHidden(is_hidden);
	setPosition(position);
}

Type Star::getType()
{
	return Type::star;
}

Star* Star::clone()
{
	return new Star(getScale(), getColor(), is_hidden, getPosition());
}
