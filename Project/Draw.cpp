#include "Engine.h"

void Engine::draw()
{
	Wall wall;
	StandardFood stdfood;
	ValuableFood valfood;
	FastFood fastfood;
	GameBlock block;
	SnakeBlock snake1(1);
	SnakeBlock snake2(2);
	SnakeBlock snake3(3);
	int row, col;

	m_window.clear(Color::White);
	for (int i = 0; i - FULLSIZE; i++) 
	{
		row = i / ROW;
		col = i % ROW;
		switch (m_level.get_tile(i))
		{
		case WALL:
			block = wall;
			break;
		case STDFOOD:
			block = stdfood;
			break;
		case VALUEFOOD:
			block = valfood;
			break;
		case FASTFOOD:
			block = fastfood;
			break;
		case SNAKE1:
			block = snake1;
			break;
		case SNAKE2:
			block = snake2;
			break;
		case SNAKE3:
			block = snake3;
			break;
		default:
			break;
		}
		if (m_level.get_tile(i) > 0) 
		{
			block.setPosition(float(col*BLOCKSIZE), float(row*BLOCKSIZE));
			m_window.draw(block);
		}
	}
}