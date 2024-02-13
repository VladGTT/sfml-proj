#pragma once
#include <vector>
#include "Figure.hpp"

class Composer : public Figure
{
	std::vector<Figure*> storage;
	sf::FloatRect global_bounds;

	sf::Vector2f scale;
	sf::Color color;

	void calculateGlobalBounds();

	static std::string parse(std::string& arg, size_t start, size_t& end);
public:
	Composer();

	~Composer();

	Composer* clone();

	void setScale(sf::Vector2f scale);

	void setOutline(float thickness, sf::Color color);
	
	void setColor(sf::Color color);

	sf::Color getColor();
	sf::Vector2f getScale();

	sf::FloatRect getGlobalBounds();

	void draw(sf::RenderWindow& window);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f new_position);

	void addFigure(Figure* figure);

	void setHidden(bool arg);

	std::string toString();

	static Composer* fromString(std::string arg);

	Type getType();
};


