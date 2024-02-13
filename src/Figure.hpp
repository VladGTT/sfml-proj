#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <cmath>


const sf::Vector2f DEFAULT_SCALE = { 1,1 };
const short NUMBER_OF_POINTS_CIRCLESHAPE = 1000;

const char DELIM1 = '(';
const char DELIM2 = ')';
const char DELIM3 = '/';

const uint16_t NUMBER_OF_FIGURE_TYPES = 7;
enum Type
{
	circle,
	line,
	composer,
	point,
	rectangle,
	star,
	triangle
};

std::string convertTypeToString(Type arg);
Type convertStringToType(std::string arg);

class Figure
{
protected:
	sf::Shape* shape=nullptr;
	bool is_hidden=false;

	static std::vector<std::string> split(std::string arg, char delimeter);
public:

	//Scale
	virtual void setScale(sf::Vector2f scale);
	virtual sf::Vector2f getScale();
	
	//Outline
	virtual void setOutline(float thickness, sf::Color color);
	
	//Color
	virtual void setColor(sf::Color color);
	virtual sf::Color getColor();

	//Hidden
	virtual bool getHidden();
	virtual void setHidden(bool arg);

	virtual Type getType() = 0;

	virtual sf::FloatRect getGlobalBounds();
	
	virtual void draw(sf::RenderWindow& window);

	virtual void setPosition(sf::Vector2f position);
	virtual sf::Vector2f getPosition();
	
	virtual Figure* clone()=0;
	
	//virtual void addFigure(Figure* arg) {}

	virtual std::string toString();

	static Figure* fromString(std::string arg);

	virtual ~Figure();
};