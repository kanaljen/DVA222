#include "Engine.hpp"


Engine::Engine()
{
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
		if(m_nextTransition != 0)makeTransition(m_nextTransition);
		m_current_state = m_next_state;
	}
}

void Engine::readInput()
{
	m_nextTransition = 0;
	m_current_state->readInput();
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

void Engine::requestTransition(int transition) 
{
	m_nextTransition = transition;
}

void Engine::makeTransition(int transition)
{
	switch (transition)
	{
	case BACKTOTOPMENU:
		delete m_gamemenu;
		delete m_gameplay;
		m_topmenu = new TopMenu(*this);
		m_next_state = m_topmenu;
		break;
	case PLAYONE:
		delete m_topmenu;
		m_gameplay = new GamePlay(*this, 1);
		m_next_state = m_gameplay;
		break;
	case PLAYTWO:
		delete m_topmenu;
		m_gameplay = new GamePlay(*this, 2);
		m_next_state = m_gameplay;
		break;
	case PLAYTHREE:
		delete m_topmenu;
		m_gameplay = new GamePlay(*this, 3);
		m_next_state = m_gameplay;
		break;
	case GAMEMENU:
		m_gamemenu = new GameMenu(*this);
		m_next_state = m_gamemenu;
	case RESUME:
		delete m_gamemenu;
		m_next_state = m_gameplay;
	case TERMINATE:
		m_window.close();
		break;
	default:
		m_next_state = m_current_state;
		break;
	}
}
