//#include <iostream>

#include "ControllerConsoleInterface.hpp"

bool reached_border_x;
bool reached_border_y;

void automove_func(Controller& ctrl, sf::Vector2f& position, sf::RenderWindow& window)
{
	sf::FloatRect temp = ctrl.getActive()->getGlobalBounds();
	if (temp.top <= 0)reached_border_y = true;
	if (int(temp.top + temp.height) >= window.getSize().y) reached_border_y = false;
	if (temp.left <= 0)reached_border_x = true;
	if (int(temp.left + temp.width) >= window.getSize().x)reached_border_x = false;

	if (reached_border_x)position.x += DELTA;
	else position.x -= DELTA;

	if (reached_border_y)position.y += DELTA;
	else position.y -= DELTA;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window", sf::Style::Default, sf::ContextSettings(0U, 0U, 8, 1U, 1U, 0U, false));
	window.setFramerateLimit(60);

	sf::Keyboard kb;
	sf::CircleShape circle;

	ControllerConsoleInterface* console_interface = new ControllerConsoleInterface(window, kb, automove_func);
	
	window.setVisible(false);
	std::cout << "Press Insert to add figure\n";
	system("pause");
	system("CLS");
	window.setVisible(true);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)window.close();
		
		console_interface->createFrame();
	}

	delete console_interface;
	return EXIT_SUCCESS;
}


