#include "States.hpp"

GameState::GameState(Engine& engine):
	m_engine(engine)
{
}

void GameState::pushToRenderQ(Drawable * object)
{
	m_engine.m_renderQ.push(object);
}

void GameState::readInput()
{
	Event event;
	m_next_state = 0;
	while (m_engine.m_window.pollEvent(event))
	{
		handleInput(event);
	}
	if (m_next_state != 0)m_engine.requestTransition(m_next_state);
}

void GameState::setNextState(int state)
{
	m_next_state = state;
}

