#pragma once
#include "Figure.hpp"

const float RADIUS = 15.0;

class Circle:public Figure
{
public:
	Circle(sf::Vector2f scale, sf::Color color, bool is_hidden, sf::Vector2f position);
	Circle* clone();
	Type getType();
};

