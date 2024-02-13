#pragma once

#include "Figure.hpp"

class Star :public Figure
{
	sf::ConvexShape star;
public:

	Star(sf::Vector2f scale, sf::Color color, bool is_hidden, sf::Vector2f position);

	Star* clone();

	Type getType();
};