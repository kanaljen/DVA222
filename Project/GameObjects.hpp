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
class GameObject : public RectangleShape
{
public:
    GameObject();
    //virtual void collision(Snake* snake) = 0
};

// Wall block class
class Wall: public GameObject
{
public:
    Wall();
    //virtual void collision(Snake* snake) = 0
};

class Food : public GameObject
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

class SnakeSegment : public GameObject
{
public:
	SnakeSegment(int player);
};

class Snake
{
};


class Level 
{
	int* m_board;

public:
	Level(int players);
	int get_tile(int idx);
	void add_food(int num);
};
