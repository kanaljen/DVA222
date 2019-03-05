#include "States.hpp"

GameState::GameState(Engine& engine):
	m_engine(engine)
{
}

void GameState::pushToRenderQ(Drawable * object)
{
	m_engine.m_renderQ.push(object);
}

void GameState::setNextState(int state)
{
	m_engine.setNextState(state);
}
