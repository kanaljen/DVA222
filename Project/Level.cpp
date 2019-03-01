#include "Game.h"

Level::Level()
{
	m_board = new int[FULLSIZE];

	for (int i = 0; i < FULLSIZE; i++)
	{
		if (i < ROW)m_board[i] = WALL;					// Top row wall
		else if (i % ROW == 0)m_board[i] = WALL;		// Left wall
		else if (i % ROW == ROW - 1)m_board[i] = WALL;	// Right wall
		else if (i > FULLSIZE - ROW)m_board[i] = WALL;	// Last row wall
		else m_board[i] = CLEAR;
	}
	add_food(10);
}

int Level::get_tile(int idx)
{
	return m_board[idx];
}

int Level::spawn_snake(int player)
{
	int idx = 0;
	while (m_board[idx] != CLEAR) { idx = randomizer(FULLSIZE); }
	m_board[idx] = 10 + player;
	return idx;
}

void Level::add_food(int num)
{
	for (int i = 0; i < num + 1; i++)
	{
		int j = 0;
		while (m_board[j] != CLEAR) 
		{ 
			j = randomizer(FULLSIZE); 
		}
		if (randomizer(100) < 10) 
		{
			m_board[j] = randomizer(100) < 50 ? VALUEFOOD : FASTFOOD;
		}
		else m_board[j] = STDFOOD;
	}
}