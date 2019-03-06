#include "GameObjects.hpp"
#include <iostream>

using namespace std;

// Return a random int in range [0,max-1]
int randomizer(int max)
{
	mt19937 rng;
	rng.seed(random_device()());
	uniform_int_distribution<mt19937::result_type> dist6(0, max - 1);
	return dist6(rng);
}

using namespace sf;

GameObject::GameObject()
{
    setTextureRect(IntRect(0, 0, BLOCKSIZE, BLOCKSIZE));
}

Background::Background()
{
    setTextureRect(IntRect(0, 0, SIZE, SIZE));
    texture.setRepeated(true);
    texture.loadFromFile("images/grass.png");
    setTexture(texture);
}

Wall::Wall()
{
    texture.loadFromFile("images/brick.png");
    setTexture(texture);
}

Food::Food(int value):
	m_value(value)
{
    texture.loadFromFile("images/food.png");
    setTexture(texture);
}

ValuableFood::ValuableFood() :
	Food(5)
{
}

StandardFood::StandardFood():
	Food(1)
{
}

FastFood::FastFood() :
	Food(0)
{
}

SnakeSegment::SnakeSegment(int player, int position, float rotation):
    m_player(player),
    m_position(position),
    m_rotation(rotation)
{
}

int SnakeSegment::getPosition()
{
    return m_position;
}

SnakeHead::SnakeHead(int player, int position, float rotation):
        SnakeSegment(player,position,rotation)
{
    texture.loadFromFile("images/snake_head.png");
    setTexture(texture);
}

SnakeTail::SnakeTail(int player, int position, float rotation):
        SnakeSegment(player,position,rotation)
{
    texture.loadFromFile("images/snake_tail.png");
    setTexture(texture);
}

SnakeBend::SnakeBend(int player, int position, float rotation):
        SnakeSegment(player,position,rotation)
{
    texture.loadFromFile("images/snake_bend.png");
    setTexture(texture);
}

SnakeStraight::SnakeStraight(int player, int position, float rotation):
        SnakeSegment(player,position,rotation)
{
    texture.loadFromFile("images/snake_straight.png");
    setTexture(texture);
}

Level::Level(int players)
{
    m_board = new int[FULLSIZE];
    
    for (int i = 0; i < FULLSIZE; i++)
    {
        if (i < ROW)m_board[i] = WALL;                    // Top row wall
        else if (i % ROW == 0)m_board[i] = WALL;        // Left wall
        else if (i % ROW == ROW - 1)m_board[i] = WALL;    // Right wall
        else if (i > FULLSIZE - ROW)m_board[i] = WALL;    // Last row wall
        else m_board[i] = CLEAR;
    }
    addFood(5);
}

int Level::getTile(int idx)
{
    return m_board[idx];
}

void Level::addFood(int num)
{
    for (int i = 0; i < num; i++)
    {
        int j = getEmptyTile();

        if (randomizer(100) < 10)
        {
            m_board[j] = randomizer(100) < 50 ? VALUEFOOD : FASTFOOD;
        }
        else m_board[j] = STDFOOD;
    }
}

int Level::getEmptyTile()
{
    int j = 0;
    while (m_board[j] != CLEAR)
    {
        j = randomizer(FULLSIZE);
    }
    return j;
}
