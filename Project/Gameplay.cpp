#include "States.hpp"

Vector2f getPosition(int idx)
{
	float row = float(idx / ROW);
	float col = float(idx % ROW);
	return Vector2f(col*BLOCKSIZE, row*BLOCKSIZE);
}

GamePlay::GamePlay(Engine& engine, int noPlayers) :
	GameState(engine),
	m_noplayers(noPlayers),
	m_level(noPlayers)
{
	GameObject* wall;
	for (int i = 0; i<FULLSIZE; i++)
	{
		if (m_level.get_tile(i) == WALL)
		{
			m_levelObjects.push_back(new Wall);
			wall = m_levelObjects.back();
			wall->setPosition(getPosition(i));
		}
	}
}

void GamePlay::update()
{
	// Push static level objects to renderQ
	for (GameObject* wall : m_levelObjects)pushToRenderQ(wall);

	// Clear object vector
	m_dynamicObjects.clear();

	// Add food to object vector
	GameObject* object;
	for (int i = ROW; i<FULLSIZE - ROW; i++)
	{
		switch (m_level.get_tile(i))
		{
		case STDFOOD:
			m_dynamicObjects.push_back(new StandardFood);
			object = m_dynamicObjects.back();
			object->setPosition(getPosition(i));
			break;
		case VALUEFOOD:
			m_dynamicObjects.push_back(new ValuableFood);
			object = m_dynamicObjects.back();
			object->setPosition(getPosition(i));
			break;
		case FASTFOOD:
			m_dynamicObjects.push_back(new FastFood);
			object = m_dynamicObjects.back();
			object->setPosition(getPosition(i));
			break;
		default:
			break;
		}
	}
	// Push dynamic game objects to renderQ
	for (GameObject* object : m_dynamicObjects)pushToRenderQ(object);
}

void GamePlay::handleInput(Event event)
{
	switch (event.type)
	{
	case Event::Closed:
		setNextState(TERMINATE);
		break;
	case Event::KeyPressed:
			handleKeys(event.key.code);
		default:
			break;
	}
}

void GamePlay::handleKeys(int key)
{
	switch (key)
	{
	case Keyboard::Escape:
		setNextState(GAMEMENU);
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

void GamePlay::updateSnakes()
{
	for (int i = 0; i < m_noplayers; i++) 
	{
		// snake.trymove()
		// snake.handlecolosion()
		// snake.move(), AKA modifie the board
		// add snakesegment to renderq
	}
}
