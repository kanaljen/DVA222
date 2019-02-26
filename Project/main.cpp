#include <vector>
#include <SFML/Graphics.hpp>
#include "game.h"
#define FRAMERATE 10


int main()
{
	sf::RenderWindow window(sf::VideoMode(SIZE, SIZE), "Snake");
	window.setFramerateLimit(FRAMERATE);
	Level level;
	Snake snake(1);
	snake.init(&level);

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
		snake.draw(&window);
		window.display();
	}

	return 0;
}