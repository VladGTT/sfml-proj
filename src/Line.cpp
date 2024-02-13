#include "Line.hpp"

Line::Line(sf::Vector2f scale, sf::Color color, bool is_hidden, sf::Vector2f position)
{
	shape = new sf::RectangleShape(BASIC_VECTOR);
	shape->rotate(ROTATION);

	setColor(color);
	setScale(scale);
	setHidden(is_hidden);
	setPosition(position);
}

Type Line::getType()
{
	return Type::line;
}

void Line::setScale(sf::Vector2f scale)
{
	this->scale = scale;
	shape->setScale(sqrt(scale.x * scale.x + scale.y * scale.y), BASIC_VECTOR.y);
	shape->setRotation(atan(scale.y / scale.x) * DEGREES_IN_RAD);
}
sf::Vector2f Line::getScale()
{
	return scale;
}
Line* Line::clone()
{
	return new Line(getScale(), getColor(), is_hidden, getPosition());
}