#pragma once
#include "Memento.hpp"
#include <fstream>

const sf::Vector2f DEFORMATION_SCALE = { 0.2,1 };

class Controller
{
	std::vector<Figure*> storage;
	uint64_t active;
	bool trail=false;
	bool deformation=true;

	std::vector<std::string> default_states;
	static Controller* instance;

	Controller() {};

	bool checkIntersection(Figure* arg);
	
public:
	void clearStorage();
	static Controller* getInstance();

	~Controller();

	void setTrail(bool arg);
	bool getTrail();

	void next();
	void prev();
	
	void resetActive();

	Figure* getActive();
	uint64_t getActiveIndex();

	void insertFigure(Figure* figure);
	void deleteFigure();

	void setDeformation(bool arg);

	bool getDeformation();

	uint64_t getSize();

	void render(sf::RenderWindow& window);
	
	void reset();

	void setMemento(Memento& obj);
	void getMemento(Memento& obj);
};