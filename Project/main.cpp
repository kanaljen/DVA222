#include <vector>
#include <SFML/Graphics.hpp>
#include "classes.h"
#define FRAMERATE 10
#define SIZE 800

int main()
{
	sf::RenderWindow window(sf::VideoMode(SIZE, SIZE), "Snake");
	window.setFramerateLimit(FRAMERATE);
	Level level(SIZE);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		level.draw(&window);
		window.display();
	}

	return 0;
}