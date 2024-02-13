#include "Circle.hpp"

Circle::Circle(sf::Vector2f scale, sf::Color color, bool is_hidden, sf::Vector2f position)
{
	shape = new sf::CircleShape(RADIUS, NUMBER_OF_POINTS_CIRCLESHAPE);
	setColor(color);
	setScale(scale);
	setHidden(is_hidden);
	setPosition(position);
}

Type Circle::getType()
{
	return Type::circle;
}

Circle* Circle::clone()
{
	return new Circle(getScale(), getColor(), is_hidden, getPosition());
}