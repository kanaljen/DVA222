#include "Engine.hpp"
#include <iostream>

Engine::Engine()
{
	m_gameplay = new GamePlay(*this, 1);
	m_topmenu = new TopMenu(*this);
	m_current_state = m_topmenu;
	m_next_state = m_topmenu;
	m_window.create(VideoMode(SIZE,SIZE), "Snake",Style::Close);
}

void Engine::start()
{
	Clock clock;
	Time start,elapsed;

	while (m_window.isOpen()) 
	{
		start = clock.restart();
		readInput();
		update();
		draw();
		elapsed = clock.getElapsedTime();
		if (milliseconds(50) > elapsed - start)
		{
			sleep(milliseconds(50) - elapsed);
		}
		m_current_state = m_next_state;
	}
}

void Engine::readInput()
{
	Event event;
	while (m_window.pollEvent(event)) 
	{
		m_current_state->readInput(event);
	}
}

void Engine::update()
{
    m_current_state->update();
}

void Engine::draw()
{
	Drawable* object;
    m_window.clear(Color(0, 130, 69));
    while(!m_renderQ.empty()) {
		object = m_renderQ.front();
		m_window.draw(*object);
		m_renderQ.pop();
	}
    m_window.display();
}

void Engine::setNextState(int state)
{
	switch (state)
	{
	case TOPMENU:
		break;
	case ONEPLAYER:
		m_gameplay = new GamePlay(*this, 1);
		m_next_state = m_gameplay;
		break;
	case TWOPLAYER:
		m_gameplay = new GamePlay(*this, 2);
		m_next_state = m_gameplay;
		break;
	case THREEPLAYER:
		m_gameplay = new GamePlay(*this, 3);
		m_next_state = m_gameplay;
		break;
	case EXIT:
		m_window.close();
		exit(1);
		break;
	default:
		m_next_state = m_current_state;
		break;
	}
}
