#include <vector>
#include <SFML/Graphics.hpp>
#include "classes.h"
#define FRAMERATE 10

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Snake");
	window.setFramerateLimit(FRAMERATE);
	std::vector<sf::RectangleShape*> board_objects;
	std::vector<GameRectangle*> dynamic_objects;
	board_objects.push_back(new sf::RectangleShape(sf::Vector2f(1000, 10)));
	//board_objects.push_back(new sf::RectangleShape(sf::Vector2f(1000, 1000)));
	//board_objects.push_back(new sf::RectangleShape(sf::Vector2f(1000, 1000)));


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		for (int i = 0; i < board_objects.size(); i++)window.draw(*board_objects[i]);
		window.display();
	}

	return 0;
}