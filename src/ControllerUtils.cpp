#include "ControllerUtils.hpp"

const char* STAGE_STATE_FILENAME = "stage.txt";

void ControllerUtils::save(Controller& ctrl)
{
	std::ofstream str;
	str.open(STAGE_STATE_FILENAME);
	ctrl.setMemento(memento);
	str << memento;
	str.close();
	clear(memento);
}
void ControllerUtils::load(Controller& ctrl)
{
	std::ifstream str;
	str.open(STAGE_STATE_FILENAME);
	str >> memento;
	ctrl.getMemento(memento);
	str.close();
	clear(memento);
}