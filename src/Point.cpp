#include "Point.hpp"

Point::Point(sf::Vector2f scale, sf::Color color, bool is_hidden, sf::Vector2f position)
{
	shape = new sf::CircleShape(POINT_RADIUS, NUMBER_OF_POINTS_CIRCLESHAPE);

	setColor(color);
	setScale(scale);

	setHidden(is_hidden);
	setPosition(position);
}

Type Point::getType()
{
	return Type::point;
}

Point* Point::clone()
{
	return new Point(getScale(), getColor(), is_hidden, getPosition());
}
