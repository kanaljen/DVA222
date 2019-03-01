#include "Engine.h"
#include <iostream>

Engine::Engine()
{
	m_window.create(VideoMode(SIZE,SIZE), "Snake",Style::None);
	m_snakes.push_back(new Snake(1,&m_level));
	m_snakes.push_back(new Snake(2, &m_level));
	m_snakes.push_back(new Snake(3, &m_level));
	/*
	for (int i = 0; i < FULLSIZE; i++) 
	{
		if (i%ROW == ROW - 1)std::cout << m_level.get_tile(i) << std::endl;
		else std::cout << m_level.get_tile(i);
	}
	*/
}


void Engine::start()
{
	Clock clock;
	Time start,elapsed;

	while (m_window.isOpen()) 
	{
		start = clock.restart();
		readInput();
		// update();
		draw();
		m_window.display();
		elapsed = clock.getElapsedTime();
		if (milliseconds(50) > elapsed - start)
		{
			sleep(milliseconds(50) - elapsed);
		}
	}
}