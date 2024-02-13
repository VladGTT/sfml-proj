#include "Controller.hpp"


Controller* Controller::instance = nullptr;
Controller* Controller::getInstance()
{
	if (!instance)instance = new Controller();
	return instance;
}


Controller::~Controller() 
{ 
	clearStorage(); 
}

void Controller::resetActive() { active = 0; }
void Controller::setTrail(bool arg) { trail = arg; }
bool Controller::getTrail() { return trail; }

void Controller::next()
{
	if (storage.empty()) return;
	active++;
	if (active >= storage.size()) active = 0;
}

void Controller::prev()
{
	if (storage.empty()) return;
	active--;
	if (active >= storage.size()) active = storage.size()-1;
}
Figure* Controller::getActive(){ return (storage.empty()) ? nullptr : storage[active]; }


uint64_t Controller::getActiveIndex() { return active; }
uint64_t Controller::getSize() { return storage.size(); }


void Controller::setDeformation(bool arg) { deformation = arg; }
bool Controller::getDeformation() { return deformation; }

bool Controller::checkIntersection(Figure* arg)
{
	if (!arg)return false;

	sf::FloatRect bounds = arg->getGlobalBounds();
	for (size_t i = 0; i < storage.size(); i++)
	{
		if (storage[i] == arg)
			continue;
		if (bounds.intersects(storage[i]->getGlobalBounds()))
			return true;
	}
	return false;
}

void Controller::insertFigure(Figure* figure)
{
	storage.push_back(figure);
	default_states.push_back(figure->toString());

	active = storage.size()-1;
}
void Controller::deleteFigure()
{
	if (storage.empty())
		return;
	
	Figure* temp = storage[active];
	storage.erase(std::find(storage.begin(), storage.end(), storage[active]));
	delete temp;

	default_states.erase(std::find(default_states.begin(), default_states.end(), default_states[active]));

	active = 0;
	
}

void Controller::render(sf::RenderWindow& window)
{
	sf::Vector2f scale;
	bool is_scaled;

	for (size_t i = 0; i < storage.size(); i++)
	{
		if (deformation)
		{
			scale = storage[i]->getScale();
			is_scaled = false;
			
			if (checkIntersection(storage[i]))
			{
				storage[i]->setScale(DEFORMATION_SCALE);
				is_scaled = true;
			}

			storage[i]->draw(window);
			if (is_scaled) storage[i]->setScale(scale);
		}
		else storage[i]->draw(window);
	}

	window.display();
	
	if (!trail)window.clear();
}

void Controller::reset()
{
	Figure* temp = storage[active];
	storage[active] = Figure::fromString(default_states[active]);
	delete temp;
}

void Controller::setMemento(Memento& obj)
{
	obj.active = active;
	obj.trail = trail;
	obj.deformation = deformation;

	for (size_t i = 0; i < storage.size(); i++)
		obj.storage.push_back(storage[i]->clone());
}
void Controller::getMemento(Memento& obj)
{
	clearStorage();

	for (size_t i = 0; i < obj.storage.size(); i++)
		insertFigure(obj.storage[i]->clone());
	
	trail = obj.trail;
	deformation = obj.deformation;
	active = obj.active;
}

void Controller::clearStorage()
{
	for (size_t i = 0; i < storage.size(); i++)
		delete storage[i];
	storage.clear();
	active = 0;
	trail = false;
	deformation = true;
	default_states.clear();
}

