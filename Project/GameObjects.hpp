#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <ctime>

// SIZECONSTANTS
#define SIZE		1280					// Window width/height in pixels
#define BLOCKSIZE	64				// Width/height of one block in pixels
#define ROW			int(SIZE/BLOCKSIZE)	// Size of one row/column
#define FULLSIZE	int(pow(ROW,2))		// Total number of blocks, 20*20=400

// BLOCKTYPES, for level array
#define EMPTY		0
#define WALL		1
#define STDFOOD		2
#define VALUEFOOD	3
#define FASTFOOD	4
#define SNAKE1		11
#define SNAKE2		12
#define SNAKE3		13

// DIRECTIONS
#define UP		1
#define RIGHT	2
#define DOWN   -1
#define LEFT   -2

// SNAKE BEND ROTATION
#define DOWNLEFT    1
#define LEFTUP      2
#define UPRIGHT     3
#define RIGHTDOWN   4

int randomizer(int max);

using namespace sf;


// Virtual block class of size BLOCKSIZExBLOCKSIZE
class GameObject : public Sprite
{
public:
	Texture texture;
    GameObject();
    //virtual void collision(Snake* snake) = 0
};

class Background : public GameObject
{
public:
	Background();
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
    const int m_player;
    int m_rotation;
public:
	SnakeSegment(int player, float rotation);
};

class SnakeHead : public SnakeSegment
{
public:
    SnakeHead(int player, float rotation);
};

class SnakeTail : public SnakeSegment
{
public:
    SnakeTail(int player, float rotation);
};

class SnakeBend : public SnakeSegment
{
public:
    SnakeBend(int player, float rotation);
};

class SnakeStraight : public SnakeSegment
{
public:
    SnakeStraight(int player, float rotation);
};

class Level 
{
	int* m_board;

public:
	Level(int players);
	int getTile(int idx);
	void addFood(int num);
	int getEmptyTile();
	void setPlayerTile(int player,int tile);
	void clearTile(int tile);
};
