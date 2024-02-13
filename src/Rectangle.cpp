#include "Rectangle.hpp"

Rectangle::Rectangle(sf::Vector2f scale, sf::Color color, bool is_hidden, sf::Vector2f position)
{
	shape = new sf::RectangleShape(SIZE);
	setColor(color), setScale(scale);
	setHidden(is_hidden);
	setPosition(position);
}
Rectangle* Rectangle::clone()
{
	return new Rectangle(getScale(), getColor(), is_hidden, getPosition());
}
Type Rectangle::getType()
{
	return Type::rectangle;
}