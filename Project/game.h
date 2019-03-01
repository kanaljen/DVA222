#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <ctime>

// SIZECONSTANTS
#define SIZE		800					// Window width/height in pixels
#define BLOCKSIZE	40					// Width/height of one block in pixels
#define ROW			int(SIZE/BLOCKSIZE)	// Size of one row/column
#define FULLSIZE	int(pow(ROW,2))		// Total number of blocks, 20*20=400

// BLOCKTYPES, for level array
#define CLEAR		0
#define WALL		1
#define STDFOOD		2
#define VALUEFOOD	3
#define FASTFOOD	4
#define SNAKE1		11
#define SNAKE2		12
#define SNAKE3		13

// SNAKE DIRECTIONS
#define UP		1
#define RIGHT	2
#define DOWN	3
#define LEFT	4

int randomizer(int max);

using namespace sf;

// Virtual block class of size BLOCKSIZExBLOCKSIZE
class GameBlock : public RectangleShape
{
public:
	GameBlock();
	//virtual void collision(Snake* snake) = 0
};

// Wall block class
class Wall: public GameBlock
{
public:
	Wall();
};

class Food : public GameBlock
{
	int m_value;
public:
	Food(int value);
};

class ValuableFood : public Food
{
public:
	ValuableFood();
};

class FastFood : public Food
{
public:
	FastFood();
};

class StandardFood : public Food
{
public:
	StandardFood();
};

class SnakeBlock : public GameBlock
{
public:
	SnakeBlock(int player);
};

// Class holds the information about the blocks in the level
class Level 
{
	int* m_board;

public:
	Level();
	int get_tile(int idx);
	int spawn_snake(int player);
	void add_food(int num);
};

// Class holds info about the snakes
class Snake
{
	std::vector<int> m_bodyparts;
	int m_player;
	bool m_alive;
	Level* m_level;
	int m_score;
	int m_direction;
public:
	Snake(int player, Level* level);
};