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
	int row;
	int col;
	GameBlock block;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		for(int i = 0; i < int(pow(SIZE / BLOCKSIZE, 2)); i++)
		{
			block = level.get_box(i);
			row = i / (SIZE / BLOCKSIZE);
			col = i % (SIZE / BLOCKSIZE);
			block.setPosition(col*BLOCKSIZE, row*BLOCKSIZE);
			window.draw(block);
		}
		window.display();
	}

	return 0;
}