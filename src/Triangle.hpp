#pragma once
#include "Figure.hpp"

const float HEIGHT = 50.0;
const short PEEK_NUMBER = 3;

class Triangle :public Figure
{
public:

	Triangle(sf::Vector2f scale, sf::Color color, bool is_hidden, sf::Vector2f position);
	
	Type getType();

	Triangle* clone();
};