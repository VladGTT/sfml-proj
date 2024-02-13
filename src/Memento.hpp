#pragma once
#include <vector>
#include "Figure.hpp"
#include <fstream>
class Memento
{
	friend class Controller;

	std::vector<Figure*> storage;
	unsigned char active = 0;

	bool trail;
	bool deformation;

	friend std::ofstream& operator<<(std::ofstream& str, Memento& obj);
	
	friend std::ifstream& operator>>(std::ifstream& str, Memento& obj);

	friend void clear(Memento& memento);

};
