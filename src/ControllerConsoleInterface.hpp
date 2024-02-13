#pragma once
#include <iostream>
#include "ComposerStorage.hpp"
#include "ControllerUtils.hpp"
#include "ComposerBuilder.hpp"

const char DELTA = 3;

const sf::Vector2f START_POSITION = { 0.0,0.0 };

const sf::Color OUTLINE_COLOR = sf::Color::White;
const float OUTLINE_MAX_THICKNESS = 2.0;
const float OUTLINE_MIN_THICKNESS = 0.0;

const float DELAY_DEFAULT_VALUE = 1.0;
const float DELAY_DELTA= -0.05;
const float DELAY_THRESHOLD_VALUE = 0.0;
const float DELAY_MINIMUM_VALUE = -200;

const sf::Vector2f SCALE_DELTA_Y = { 0, 0.1 };
const sf::Vector2f SCALE_DELTA_X = { 0.1, 0 };
const float SCALE_X_MIN = 0.02;
const float SCALE_Y_MIN = 0.02;

const std::string CIRCLE_STRING = "circle/1/1/4294967295/0/0/0";
const std::string LINE_STRING = "line/1/1/4294967295/0/0/0";
const std::string POINT_STRING = "point/1/1/4294967295/0/0/0";
const std::string RECTANGLE_STRING = "rectangle/1/1/4294967295/0/0/0";
const std::string STAR_STRING = "star/1/1/4294967295/0/0/0";
const std::string TRIANGLE_STRING = "triangle/1/1/4294967295/0/0/0";

class ControllerConsoleInterface
{
	Controller* ctrl = nullptr;
	ComposerStorage* cmps_strg = nullptr;


	sf::Keyboard* kb = nullptr;
	sf::RenderWindow* window = nullptr;


	ComposerBuilder* builder = nullptr;
	std::vector<Figure*> figures;
	bool composer_mode = false;


	void (*automove_func)(Controller&, sf::Vector2f&,sf::RenderWindow&);
	bool automove;


	float delay;	


	void startBuildingComposer();
	void abortBuildingComposer();
	void finishBuildingComposer();

	void createFigure(std::string arg);
	void moveActiveFigure(bool left,bool right,bool up,bool down);
public:
	ControllerConsoleInterface(sf::RenderWindow& window, sf::Keyboard& kb, void (*automove_func)(Controller&, sf::Vector2f&, sf::RenderWindow&));
	void createFrame();
	~ControllerConsoleInterface();
};