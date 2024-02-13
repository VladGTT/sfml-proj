#pragma once
#include <iostream>
#include "Controller.hpp"

class ControllerUtils
{
	Memento memento;
public:
	void save(Controller& ctrl);
	void load(Controller& ctrl);
};