#include "Engine.h"
#include <iostream>

void Engine::readInput()
{
	Event event;

	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			m_window.close();
			break;
		case Event::KeyPressed:
			handleKeys(event.key.code);
			break;
		default:
			break;
		}
	}
}

void Engine::handleKeys(int key)
{
	switch (key)
	{
	case Keyboard::Escape:
		m_window.close();
		break;
	// PLAYER 1
	case Keyboard::W:
		m_input[0] = UP;
		break;
	case Keyboard::A:
		m_input[0] = LEFT;
		break;
	case Keyboard::S:
		m_input[0] = DOWN;
		break;
	case Keyboard::D:
		m_input[0] = RIGHT;
	// PLAYER 2
		break;
	case Keyboard::I:
		m_input[1] = UP;
		break;
	case Keyboard::J:
		m_input[1] = LEFT;
		break;
	case Keyboard::K:
		m_input[1] = DOWN;
		break;
	case Keyboard::L:
		m_input[1] = RIGHT;
		break;
	// PLAYER 3
	case Keyboard::Up:
		m_input[2] = UP;
		break;
	case Keyboard::Left:
		m_input[2] = LEFT;
		break;
	case Keyboard::Down:
		m_input[2] = DOWN;
		break;
	case Keyboard::Right:
		m_input[2] = RIGHT;
		break;
	default:
		break;
	}
}