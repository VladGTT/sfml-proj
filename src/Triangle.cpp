#include "Triangle.hpp"

Triangle::Triangle(sf::Vector2f scale, sf::Color color, bool is_hidden, sf::Vector2f position)
{
	shape = new sf::CircleShape(HEIGHT, PEEK_NUMBER);
	setColor(color);
	setScale(scale);
	setHidden(is_hidden);
	setPosition(position);
}

Type Triangle::getType()
{
	return Type::triangle;
}

Triangle* Triangle::clone()
{
	return new Triangle(getScale(), getColor(), is_hidden, getPosition());
}