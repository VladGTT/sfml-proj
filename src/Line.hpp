#pragma once
#include "Figure.hpp"


const float ROTATION = 45.0;
const sf::Vector2f BASIC_VECTOR = { 100,1 };
const float DEGREES_IN_RAD = 180 / 3.14;

class Line :public Figure
{
	sf::Vector2f scale;
public:

	Line(sf::Vector2f scale, sf::Color color, bool is_hidden, sf::Vector2f position);

	Line* clone();

	Type getType();

	void setScale(sf::Vector2f scale);

	sf::Vector2f getScale();
};
