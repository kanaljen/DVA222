#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <random>

// SIZECONSTANTS
#define SIZE 800					// Window width/height in pixels
#define BLOCKSIZE 40				// Width/height of one block in pixels
#define ROW int(SIZE/BLOCKSIZE)			// Size of one row/column
#define FULLSIZE int(pow(ROW,2))	// Total number of blocks, 20*20=400


// BLOCKTYPES
#define CLEAR 0
#define WALL 1
#define FOOD 2
#define VFOOD 3


// Return a random int in range [0,max-1]
int randomizer(int max) 
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, max-1);
	return dist6(rng);
}

// Virtual block class of size BLOCKSIZExBLOCKSIZE
class GameBlock : public sf::RectangleShape
{
public:
	GameBlock() :
		RectangleShape(sf::Vector2f(BLOCKSIZE, BLOCKSIZE))
	{}
	//virtual void collision(Snake* snake) = 0;
};

// Wall block class
class Wall: public GameBlock
{
public:
	Wall() 
	{
		setFillColor(sf::Color::Black);
	}
};

// Clear area class
class Clear : public GameBlock
{
public:
	Clear()
	{
		setFillColor(sf::Color::White);
	}
};

// Virtual food class
class Food : public GameBlock
{
	int m_value;
public:
	Food(int inputvalue): m_value(inputvalue) {}
};

// Class for valuable food object
class ValuableFood : public Food
{
public:
	ValuableFood(): 
		Food(5)
	{
		
		setFillColor(sf::Color::Red);
	}
};

// Class for standard food object
class StandardFood : public Food
{
public:
	StandardFood():
		Food(1)
	{
		setFillColor(sf::Color::Green);
	}
};

// Class holds the information about the blocks in the level
class Level 
{
	int* m_board;
	const Wall wall;
	const Clear clear;
	const ValuableFood valfood;
	const StandardFood stdfood;
public:
	Level() :
		m_board(new int[FULLSIZE])
	{
		for (int i = 0; i < FULLSIZE; i++)
		{
			if (i < ROW)m_board[i] = WALL;					// Top row wall
			else if (i % ROW == 0)m_board[i] = WALL;		// Left wall
			else if (i % ROW == ROW-1)m_board[i] = WALL;	// Right wall
			else if (i > FULLSIZE - ROW)m_board[i] = WALL;	// Last row wall
			else m_board[i] = CLEAR;
		}
		add_food(10);
	};

	// Draw level in renderwindow
	void draw(sf::RenderWindow* window)
	{
		int row;
		int col;
		GameBlock block;

		for (int i = 0; i < FULLSIZE; i++)
		{
			row = i / ROW;
			col = i % ROW;
			switch (m_board[i])
			{
			case WALL:
				block = wall;
				break;
			case CLEAR:
				block = clear;
				break;
			case FOOD:
				block = stdfood;
				break;
			case VFOOD:
				block = valfood;
				break;
			default:
				break;
			}
			block.setPosition(float(col*BLOCKSIZE), float(row*BLOCKSIZE));
			window->draw(block);
		}
	}

	// Get type of tile for a specified index
	int get_tile(int idx)
	{
		return m_board[idx];
	}

private:
	// Add num number of food objects to the level
	void add_food(int num)
	{
		for (int i = 0; i < num + 1; i++)
		{
			int j = 0;
			while (m_board[j] != CLEAR) { j = randomizer(FULLSIZE); }
			m_board[j] = randomizer(100) < 10 ? VFOOD : FOOD;
		}
	};
};

class SnakeBlock : public GameBlock
{
	int m_position;
public:
	SnakeBlock(int pos) : m_position(pos)
	{
		setPosition(float((m_position%ROW)*BLOCKSIZE), float((m_position%ROW)*BLOCKSIZE));
		setFillColor(sf::Color::Blue);
	}
};

class Snake
{
	std::vector<SnakeBlock*> m_bodyparts;
	int m_dirction;
	const int m_player;
	int m_score;
public:
	Snake(int inplayer) : m_player(inplayer), m_score(0) {}
	void init(Level* level)
	{
		int j = 0;
		while (level->get_tile(j) != CLEAR) { j = randomizer(FULLSIZE); }
		m_bodyparts.push_back(new SnakeBlock(j));
	}
	void draw(sf::RenderWindow* window)
	{
		for (SnakeBlock* block : m_bodyparts)window->draw(*block);
	}

};