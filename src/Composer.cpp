#include "Composer.hpp"

Composer::Composer()
{
	scale = DEFAULT_SCALE;
	color = sf::Color::Transparent;
	shape = nullptr;
}

Composer::~Composer()
{
	for (int i = 0; i < storage.size(); i++)
		delete storage[i];
}
Composer* Composer::clone()
{
	Composer* cloned = new Composer();

	if (storage.empty())
		return cloned;

	for (int i = 0; i < storage.size(); i++)
		cloned->addFigure(storage[i]->clone());

	cloned->color = color;

	cloned->scale = scale;

	cloned->setHidden(is_hidden);

	cloned->calculateGlobalBounds();

	return cloned;
}

void Composer::setScale(sf::Vector2f new_scale)
{
	sf::Vector2f position = { global_bounds.left, global_bounds.top };
	sf::Vector2f vector;
	
	for (size_t i = 0; i <storage.size(); i++)
	{
		vector = { (sf::Vector2f(storage[i]->getPosition() - position).x * new_scale.x) / scale.x,(sf::Vector2f(storage[i]->getPosition() - position).y * new_scale.y) / scale.y };
		
		storage[i]->setScale({ (storage[i]->getScale().x * new_scale.x) / scale.x, (storage[i]->getScale().y * new_scale.y) / scale.y });	
		storage[i]->setPosition(position + vector);
	}
	
	global_bounds.width *= new_scale.x / scale.x;
	global_bounds.height *= new_scale.y / scale.y;
	scale = new_scale;
}

void Composer::setOutline(float thickness, sf::Color color)
{
	for (size_t i = 0; i < storage.size(); i++)
		storage[i]->setOutline(thickness, color);
}
void Composer::setColor(sf::Color color)
{
	if (storage.empty() || color == sf::Color::Transparent)
		return;
	for (int i = 0; i < storage.size(); i++)
		storage[i]->setColor(color);

	this->color = color;
}

void Composer::calculateGlobalBounds()
{
	if (storage.empty()) return;
	if (storage.size() == 1)
	{
		global_bounds = storage[0]->getGlobalBounds();
		return;
	}

	sf::FloatRect bounds = storage[0]->getGlobalBounds();
	float top(bounds.top), bottom(bounds.top + bounds.height), left(bounds.left), right(bounds.left + bounds.width);


	for (uint16_t i = 0; i < storage.size(); i++)
	{
		bounds = storage[i]->getGlobalBounds();

		if (bounds.top + bounds.height > bottom)
			bottom = bounds.top + bounds.height;

		if (bounds.top < top)
			top = bounds.top;

		if (bounds.left + bounds.width > right)
			right = bounds.left + bounds.width;

		if (bounds.left < left)
			left = bounds.left;
	}
	global_bounds = sf::FloatRect(left, top, right - left, bottom - top);
}

sf::FloatRect Composer::getGlobalBounds()
{
	return global_bounds;
}

void Composer::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < storage.size(); i++)
		storage[i]->draw(window);
}

sf::Vector2f Composer::getPosition()
{
	return sf::Vector2f(global_bounds.left, global_bounds.top);
}

void Composer::setPosition(sf::Vector2f new_position)
{
	sf::Vector2f position = { global_bounds.left, global_bounds.top }, delta=new_position-position;

	for (size_t i = 0; i < storage.size(); i++)
		storage[i]->setPosition(storage[i]->getPosition()+delta);

	global_bounds.left = new_position.x;
	global_bounds.top = new_position.y;
}

void Composer::addFigure(Figure* figure)
{
	if (!figure)
		throw std::string("Argument == NULL");

	storage.push_back(figure);

	setHidden(getHidden());

	scale = DEFAULT_SCALE;
}

void Composer::setHidden(bool arg)
{
	for (int i = 0; i < storage.size(); i++)
		storage[i]->setHidden(arg);
	is_hidden = arg;
}

Type Composer::getType() { return Type::composer; }

sf::Color Composer::getColor() { return color; }

sf::Vector2f Composer::getScale() { return scale; }

std::string Composer::toString()
{
	std::stringstream str;

	str << convertTypeToString(getType()) << DELIM3
		<< getScale().x << DELIM3
		<< getScale().y << DELIM3
		<< getColor().toInteger() << DELIM3
		<< getHidden() << DELIM3
		<< storage.size();

	for (int i = 0; i < storage.size(); i++)
		str << "(" << storage[i]->toString() << ")";
	return str.str();
}


std::string Composer::parse(std::string& arg, size_t start, size_t& end)
{
	uint16_t counter = 0;

	for (size_t i = start; i < arg.size(); i++)
	{
		if (arg[i] == DELIM1)counter++;
		if (arg[i] == DELIM2)counter--;
		if (!counter)
		{
			start++;
			end = i + 1;
			return arg.substr(start, i - start);
		}
	}
	throw std::exception();
}

Composer* Composer::fromString(std::string arg)
{
	size_t first_delim = arg.find(DELIM1), last_delim;

	std::vector < std::string> splited = split(arg.substr(0, first_delim),DELIM3);

	Composer* retval = new Composer();

	int size = std::stoi(splited[5]);

	for (int i = 0; i < size; i++)
	{
		try
		{
			retval->addFigure(Figure::fromString(parse(arg, first_delim, last_delim)));
			first_delim = last_delim;
		}
		catch (std::exception exp)
		{
			continue;
		}
	}

	retval->scale={ std::stof(splited[1]),std::stof(splited[2]) };

	retval->setColor(sf::Color(std::stol(splited[3])));

	retval->is_hidden=std::stoi(splited[4]);

	retval->calculateGlobalBounds();
	return retval;

}
