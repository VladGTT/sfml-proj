#pragma once
#include <unordered_map>
#include "Figure.hpp"


class ComposerStorage
{
	std::unordered_map<std::string, Figure*> storage;
public:
	void add(Figure* composer, std::string name);
	Figure* get(std::string name);
};