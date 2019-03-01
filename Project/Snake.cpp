#include "Game.h"

Snake::Snake(int player,Level* level) :
	m_player(player),
	m_alive(false),
	m_score(0),
	m_level(level)
{
	/*
	int j = 0;
	while (m_level->get_tile(j) != CLEAR) { j = randomizer(FULLSIZE); }
	m_bodyparts.insert(m_bodyparts.begin(), j);
	if (j%ROW > ROW / 2)
	{
		if (j / ROW > ROW / 2)m_direction = randomizer(100) % 50 ? UP : LEFT;
		else m_direction = randomizer(100) % 50 ? DOWN : LEFT;
	}
	else
	{
		if (j / ROW > ROW / 2)m_direction = randomizer(100) % 50 ? UP : RIGHT;
		else m_direction = randomizer(100) % 50 ? DOWN : RIGHT;
	}
	*/
	level->spawn_snake(m_player);
	m_alive = true;
}
