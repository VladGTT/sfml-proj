#include "Circle.hpp"
#include "Line.hpp"
#include "Triangle.hpp"
#include "Star.hpp"
#include "Rectangle.hpp"
#include "Point.hpp"
#include "Composer.hpp"

std::string convertTypeToString(Type arg)
{
	if (arg == Type::circle)return std::string("circle");
	if (arg == Type::line)return std::string("line");
	if (arg == Type::composer)return std::string("composer");
	if (arg == Type::point)return std::string("point");
	if (arg == Type::rectangle)return std::string("rectangle");
	if (arg == Type::star)return std::string("star");
	if (arg == Type::triangle)return std::string("triangle");
}

Type convertStringToType(std::string arg)
{
	if (arg == std::string("circle"))return Type::circle;
	if (arg == std::string("line"))return Type::line;
	if (arg == std::string("composer"))return Type::composer;
	if (arg == std::string("point"))return Type::point;
	if (arg == std::string("rectangle"))return Type::rectangle;
	if (arg == std::string("star"))return Type::star;
	if (arg == std::string("triangle"))return Type::triangle;

	throw std::string("convertStringToType: cant identify type");
}

void Figure::setScale(sf::Vector2f scale)
{
	shape->setScale(scale);
}
sf::Vector2f Figure::getScale()
{
	return shape->getScale();
}

void Figure::setOutline(float thickness, sf::Color color)
{
	shape->setOutlineColor(color);
	shape->setOutlineThickness(thickness);
}
void Figure::setColor(sf::Color color)
{
	shape->setFillColor(color);
}
sf::Color Figure::getColor()
{
	return shape->getFillColor();
}

bool Figure::getHidden()
{
	return is_hidden;
}
void Figure::setHidden(bool arg)
{
	is_hidden = arg;
}


sf::FloatRect Figure::getGlobalBounds()
{
	return shape->getGlobalBounds();
}
void Figure::draw(sf::RenderWindow& window)
{
	if(!is_hidden)window.draw(*shape);
}
void Figure::setPosition(sf::Vector2f position)
{
	shape->setPosition(position);
}
sf::Vector2f Figure::getPosition()
{
	return shape->getPosition();
}

std::string Figure::toString()
{
	std::stringstream str;
	str << convertTypeToString(getType()) << DELIM3
		<< getScale().x << DELIM3
		<< getScale().y << DELIM3
		<< getColor().toInteger() << DELIM3
		<< getHidden() << DELIM3
		<< getPosition().x << DELIM3
		<< getPosition().y;
	return str.str();
}

Figure::~Figure()
{
	delete shape;
}


std::vector<std::string> Figure::split(std::string arg, char delimeter)
{
	std::vector<std::string> retval;
	std::stringstream str(arg);
	while (!str.eof())
	{
		std::getline(str, arg, delimeter);
		retval.push_back(arg);
	}
	return retval;
}


Figure* Figure::fromString(std::string arg)
{
	if (arg.find(convertTypeToString(Type::composer), 0) != std::string::npos)
		return Composer::fromString(arg);

	std::vector<std::string> splited = split(arg,DELIM3);

	Type figure_type;
	try
	{
		figure_type = convertStringToType(splited[0]);
	}
	catch (std::string exp)
	{
		throw std::string("convertFromString: unidentified figure type ");
	}

	if (figure_type == Type::circle)
		return new Circle({ std::stof(splited[1]),std::stof(splited[2]) }, sf::Color(std::stoul(splited[3])), std::stoi(splited[4]), { std::stof(splited[5]),std::stof(splited[6]) });
	if (figure_type == Type::line)
		return new Line({ std::stof(splited[1]),std::stof(splited[2]) }, sf::Color(std::stoul(splited[3])), std::stoi(splited[4]), { std::stof(splited[5]),std::stof(splited[6]) });
	if (figure_type == Type::point)
		return new Point({ std::stof(splited[1]),std::stof(splited[2]) }, sf::Color(std::stoul(splited[3])), std::stoi(splited[4]), { std::stof(splited[5]),std::stof(splited[6]) });
	if (figure_type == Type::rectangle)
		return new Rectangle({ std::stof(splited[1]),std::stof(splited[2]) }, sf::Color(std::stoul(splited[3])), std::stoi(splited[4]), { std::stof(splited[5]),std::stof(splited[6]) });
	if (figure_type == Type::star)
		return new Star({ std::stof(splited[1]),std::stof(splited[2]) }, sf::Color(std::stoul(splited[3])), std::stoi(splited[4]), { std::stof(splited[5]),std::stof(splited[6]) });
	if (figure_type == Type::triangle)
		return new Triangle({ std::stof(splited[1]),std::stof(splited[2]) }, sf::Color(std::stoul(splited[3])), std::stoi(splited[4]), { std::stof(splited[5]),std::stof(splited[6]) });

	throw std::string("convertFromString: no matched Figure constructor");
}