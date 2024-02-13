#pragma once

#include "Figure.hpp"

const sf::Vector2f SIZE = { 50,50 };

class Rectangle :public Figure
{
	sf::RectangleShape rect;
public:

	Rectangle(sf::Vector2f scale, sf::Color color, bool is_hidden, sf::Vector2f position);
	Rectangle* clone();
	Type getType();
	
};