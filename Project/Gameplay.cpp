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
	for (int i = 0; i < noPlayers; i++)m_snakes.push_back(new Snake(i + 1, &m_level));
	m_levelObjects.push_back(&background);
	GameObject* wall;
	for (int i = 0; i < FULLSIZE; i++)
	{
		if (m_level.getTile(i) == WALL)
		{
			m_levelObjects.push_back(new Wall);
			wall = m_levelObjects.back();
			wall->setPosition(getPosition(i));
		}
	}
	for (int i = 0; i < 4; i++)m_input[i] = 0;
}

void GamePlay::update()
{
	printf("NUMBERO OF SNAKES: %d \n", m_snakes.size());
	// Push static level objects to renderQ
	for (GameObject* wall : m_levelObjects)pushToRenderQ(wall);
	// Update snakes
	for (int i = 0; i < m_snakes.size(); i++)
	{
		if (m_snakes[i]->isAlive())
			m_snakes[i]->update(m_input[i]);
		else
		{
			m_snakes.erase(m_snakes.begin() + i);
			continue;
		}

		//int test = randomizer(3) % m_snakes.size();
		if (m_snakes[i]->hasHitFastFood == true)
		{
			// select random  snake
			
			m_snakes[randomizer(3) % m_snakes.size()]->setPowerUp(1, 50); // set speed and powerup time
			m_snakes[i]->hasHitFastFood = false;
		}
	}
	// Clear object vector
	m_dynamicObjects.clear();

	// Add food to object vector
	GameObject* object;
	for (int i = ROW; i < FULLSIZE - ROW; i++)
	{
		switch (m_level.getTile(i))
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
	for (Snake* snake : m_snakes)
	{
		if (snake->isAlive())snake->draw(this);
	}
	//m_level.d_printLevel();
}

void GamePlay::handleInput(Event event)
{
	int alive = 0;
	for (Snake* snake : m_snakes)
	{
		if (snake->isAlive())alive++;
	}
	if (alive == 0) {
		setNextState(GAMEOVER);
	}
	switch (event.type)
	{
	case Event::Closed:
		setNextState(TERMINATE);
		break;
	case Event::KeyPressed:
		handleKeys(event.key.code);
		break;
	default:
		break;
	}
}

void GamePlay::handleKeys(int key)
{
	switch (key)
	{
	case Keyboard::Escape:
		setNextState(TOGAMEMENU);
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

void GamePlay::drawSnakes()
{


}
