#pragma once

#include "Figure.hpp"

const float POINT_RADIUS = 3;

class Point :public Figure
{
public:

	Point(sf::Vector2f scale, sf::Color color, bool is_hidden, sf::Vector2f position);

	Point* clone();
	void setScale(sf::Vector2f){}
	Type getType();

};





