#include "ControllerConsoleInterface.hpp"


ControllerConsoleInterface::~ControllerConsoleInterface()
{
	delete ctrl;
	delete cmps_strg;
}

ControllerConsoleInterface::ControllerConsoleInterface(sf::RenderWindow& window, sf::Keyboard& kb,void(*automove_func)(Controller&, sf::Vector2f&, sf::RenderWindow&))
{
	ctrl = Controller::getInstance();
	cmps_strg = new ComposerStorage();
	this->kb = &kb;
	this->window = &window;
	this->automove_func = automove_func;
	automove = false;
}
void ControllerConsoleInterface::createFigure(std::string arg)
{
	try
	{
		Figure* temp = Figure::fromString(arg);
		if (ctrl->getActive())ctrl->getActive()->setOutline(OUTLINE_MIN_THICKNESS, OUTLINE_COLOR);
		ctrl->insertFigure(temp);
		if (composer_mode)figures.push_back(temp);
		if (ctrl->getActive())ctrl->getActive()->setOutline(OUTLINE_MAX_THICKNESS, OUTLINE_COLOR);

	}
	catch (std::exception exp) {}
}

void ControllerConsoleInterface::abortBuildingComposer()
{
	composer_mode = false;
	ctrl->setDeformation(true);

	delete builder;
	builder = nullptr;
	figures.clear();

	std::cout << "Composer mode disabled\n";
}

void ControllerConsoleInterface::startBuildingComposer()
{
	builder = new ComposerBuilder();
	ctrl->resetActive();

	for (size_t i = 0; i < ctrl->getSize(); i++)
	{
		figures.push_back(ctrl->getActive());
		ctrl->next();
	}
	if (ctrl->getActive())ctrl->getActive()->setOutline(OUTLINE_MAX_THICKNESS, OUTLINE_COLOR);

	composer_mode = true;
	ctrl->setDeformation(false);
	std::cout << "Composer mode enabled\n";
}

void ControllerConsoleInterface::finishBuildingComposer()
{
	for (size_t i = 0; i < figures.size(); i++)
		if (figures[i])figures[i] = figures[i]->clone();

	ctrl->clearStorage();

	for (size_t i = 0; i < figures.size(); i++)
		if (figures[i]) ctrl->insertFigure(figures[i]);
	try
	{

		ctrl->insertFigure(builder->completeBuild());

		window->setVisible(false);

		std::cout << "Input composer name: ";

		std::string name;
		std::cin >> name;

		cmps_strg->add(ctrl->getActive(), name);
		window->setVisible(true);

		composer_mode = false;
		ctrl->setDeformation(true);
	}
	catch (std::exception exp)
	{
		std::cout << "Composer is empty\n";
	}

	figures.clear();
	delete builder;
	builder = nullptr;
}

void ControllerConsoleInterface::moveActiveFigure(bool left, bool right, bool up, bool down)
{
	sf::Vector2f position = START_POSITION;
	sf::FloatRect bounds;
	
	if (!ctrl->getActive())return;

	try
	{
		position = ctrl->getActive()->getPosition();
		bounds = ctrl->getActive()->getGlobalBounds();
	}
	catch (std::exception exp)
	{
		return;
	}

	if (automove && automove_func)
		automove_func(*ctrl, position,*window);
	else
	{
		if (left)
			if (bounds.left >0)
				position.x -= DELTA;

		if (right)
			if (bounds.left + bounds.width < window->getSize().x)
				position.x += DELTA;
			
		if (up)
			if (bounds.top > 0)
				position.y -= DELTA;

		if (down)
			if (bounds.top + bounds.height < window->getSize().y)
				position.y += DELTA;
	}

	ctrl->getActive()->setPosition(position);
}

void ControllerConsoleInterface::createFrame()
{
	
	if (kb->isKeyPressed(kb->C) && delay <= DELAY_THRESHOLD_VALUE)
	{
		if (ctrl->getActive())ctrl->getActive()->setOutline(OUTLINE_MIN_THICKNESS, OUTLINE_COLOR);

		startBuildingComposer();

		delay = DELAY_DEFAULT_VALUE;
	}

	if (composer_mode && kb->isKeyPressed(kb->F) && delay <= DELAY_THRESHOLD_VALUE)
	{
		if (ctrl->getActive())ctrl->getActive()->setOutline(OUTLINE_MIN_THICKNESS, OUTLINE_COLOR);

		finishBuildingComposer();

		if (ctrl->getActive())ctrl->getActive()->setOutline(OUTLINE_MAX_THICKNESS, OUTLINE_COLOR);
		delay = DELAY_DEFAULT_VALUE;
	}
	if (composer_mode && kb->isKeyPressed(kb->Escape) && delay <= DELAY_THRESHOLD_VALUE)
	{
		abortBuildingComposer();
		delay = DELAY_DEFAULT_VALUE;
	}

	//next
	if (kb->isKeyPressed(kb->Add) && delay <= DELAY_THRESHOLD_VALUE)
	{
		if (ctrl->getActive())ctrl->getActive()->setOutline(OUTLINE_MIN_THICKNESS, OUTLINE_COLOR);
		ctrl->next();
		if (ctrl->getActive())ctrl->getActive()->setOutline(OUTLINE_MAX_THICKNESS, OUTLINE_COLOR);

		delay = DELAY_DEFAULT_VALUE;
	}
	

	//scale
	if (kb->isKeyPressed(kb->Up))
	{
		
		 ctrl->getActive()->setScale(ctrl->getActive()->getScale() + SCALE_DELTA_Y);
	}
	if (kb->isKeyPressed(kb->Down))
	{
		sf::Vector2f scale = ctrl->getActive()->getScale();
		if ((scale - SCALE_DELTA_Y).y > SCALE_Y_MIN) ctrl->getActive()->setScale(scale - SCALE_DELTA_Y);
	}
	if (kb->isKeyPressed(kb->Left))
	{
		sf::Vector2f scale = ctrl->getActive()->getScale();
		if ((scale - SCALE_DELTA_X).x > SCALE_X_MIN) ctrl->getActive()->setScale(scale - SCALE_DELTA_X);
	}
	if (kb->isKeyPressed(kb->Right))
	{
		ctrl->getActive()->setScale(ctrl->getActive()->getScale() + SCALE_DELTA_X);
	}


	//color
	if (kb->isKeyPressed(kb->F5))
	{
		sf::Color color = ctrl->getActive()->getColor();
		ctrl->getActive()->setColor(sf::Color(color.r+1, color.g, color.b));
	}
	if (kb->isKeyPressed(kb->F6))
	{
		sf::Color color = ctrl->getActive()->getColor();
		ctrl->getActive()->setColor(sf::Color(color.r, color.g+1, color.b));
	}
	if (kb->isKeyPressed(kb->F7))
	{
		sf::Color color = ctrl->getActive()->getColor();
		ctrl->getActive()->setColor(sf::Color(color.r, color.g, color.b+1));
	}

	//add to composer (only in composer mode)
	if (composer_mode && kb->isKeyPressed(kb->F8) && delay <= DELAY_THRESHOLD_VALUE)
	{
		Figure* temp = figures[ctrl->getActiveIndex()];
		if (temp)
		{
			builder= builder->add(temp);
			figures[ctrl->getActiveIndex()] = nullptr;
			std::cout << "Figure added to coposite\n";
		}
		else
			std::cout << "Figure is already in composer\n";
		
		delay = DELAY_DEFAULT_VALUE;
	}


	//insert
	if (kb->isKeyPressed(kb->Insert) && kb->isKeyPressed(kb->Num1) && delay <= DELAY_THRESHOLD_VALUE)
	{
		createFigure(CIRCLE_STRING);
		delay = DELAY_DEFAULT_VALUE;
	}
	if (kb->isKeyPressed(kb->Insert) && kb->isKeyPressed(kb->Num2) && delay <= DELAY_THRESHOLD_VALUE)
	{
		createFigure(LINE_STRING);
		delay = DELAY_DEFAULT_VALUE;
	}
	if (kb->isKeyPressed(kb->Insert) && kb->isKeyPressed(kb->Num3) && delay <= DELAY_THRESHOLD_VALUE)
	{
		createFigure(POINT_STRING);
		delay = DELAY_DEFAULT_VALUE;
	}
	if (kb->isKeyPressed(kb->Insert) && kb->isKeyPressed(kb->Num4) && delay <= DELAY_THRESHOLD_VALUE)
	{
		createFigure(RECTANGLE_STRING);
		delay = DELAY_DEFAULT_VALUE;
	}
	if (kb->isKeyPressed(kb->Insert) && kb->isKeyPressed(kb->Num5) && delay <= DELAY_THRESHOLD_VALUE)
	{
		createFigure(STAR_STRING);
		delay = DELAY_DEFAULT_VALUE;
	}
	if (kb->isKeyPressed(kb->Insert) && kb->isKeyPressed(kb->Num6) && delay <= DELAY_THRESHOLD_VALUE)
	{
		createFigure(TRIANGLE_STRING);
		delay = DELAY_DEFAULT_VALUE;
	}


	//delete
	if (kb->isKeyPressed(kb->Delete) && delay <= DELAY_THRESHOLD_VALUE)
	{
		if(composer_mode)figures.erase(std::find(figures.begin(), figures.end(), figures[ctrl->getActiveIndex()]));
		ctrl->deleteFigure();
		if (ctrl->getActive())ctrl->getActive()->setOutline(OUTLINE_MAX_THICKNESS, OUTLINE_COLOR);

		delay = DELAY_DEFAULT_VALUE;
	}


	//reset
	if (kb->isKeyPressed(kb->R) && delay <= DELAY_THRESHOLD_VALUE)
	{
		try
		{
			ctrl->reset();
			if(ctrl->getActive())ctrl->getActive()->setOutline(2.0, OUTLINE_COLOR);
		}
		catch (std::exception exp) {}
		
		delay = DELAY_DEFAULT_VALUE;
	}

	//get Composer from ComposerStorage
	if (kb->isKeyPressed(kb->G))
	{
		window->setVisible(false);
		std::string name;
		std::cout << "Input figure name: ";
		std::cin >> name;
		try
		{
			ctrl->insertFigure(cmps_strg->get(name));
			if (ctrl->getActive())ctrl->getActive()->setOutline(OUTLINE_MAX_THICKNESS, OUTLINE_COLOR);
		}
		catch (std::exception exp)
		{
			std::cout << exp.what() << "\n";
			system("pause");
		}
		window->setVisible(true);
		system("CLS");
	}

	//save
	if (!composer_mode && kb->isKeyPressed(kb->F1) && delay <= DELAY_THRESHOLD_VALUE)
	{
		ControllerUtils* ctrl_utils = new ControllerUtils();
		ctrl_utils->save(*ctrl);
		delete ctrl_utils;

		std::cout << "Stage is successfully saved\n";

		delay = DELAY_DEFAULT_VALUE;
	}

	//load
	if (!composer_mode && kb->isKeyPressed(kb->F2) && delay <= DELAY_THRESHOLD_VALUE)
	{
		ControllerUtils* ctrl_utils = new ControllerUtils();
		ctrl_utils->load(*ctrl);
		delete ctrl_utils;

		std::cout << "Stage is successfully loaded\n";

		if (ctrl->getActive())ctrl->getActive()->setOutline(OUTLINE_MAX_THICKNESS, OUTLINE_COLOR);

		delay = DELAY_DEFAULT_VALUE;
	}

	//trail
	if (!composer_mode && kb->isKeyPressed(kb->T) && delay <= DELAY_THRESHOLD_VALUE)
	{
		ctrl->setTrail(!ctrl->getTrail());
		
		delay = DELAY_DEFAULT_VALUE;
	}

	//hidden
	if (!composer_mode && kb->isKeyPressed(kb->H) && delay <= DELAY_THRESHOLD_VALUE)
	{
		ctrl->getActive()->setHidden(!ctrl->getActive()->getHidden());
		
		delay = DELAY_DEFAULT_VALUE;
	}

	//automove
	automove = kb->isKeyPressed(kb->LShift);
	moveActiveFigure(kb->isKeyPressed(kb->A), kb->isKeyPressed(kb->D), kb->isKeyPressed(kb->W), kb->isKeyPressed(kb->S));
	
	ctrl->render(*window);
	delay += DELAY_DELTA;
	if (delay < DELAY_MINIMUM_VALUE)
		delay = DELAY_THRESHOLD_VALUE;
}

