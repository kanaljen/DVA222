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

GameObject::GameObject() :
	RectangleShape(Vector2f(BLOCKSIZE, BLOCKSIZE))
{
}

Wall::Wall()
{
	setFillColor(Color(71, 71, 71));
}

Food::Food(int value):
	m_value(value)
{
}

ValuableFood::ValuableFood() :
	Food(5)
{
	setFillColor(Color(255, 165, 0));
}

StandardFood::StandardFood():
	Food(1)
{
	setFillColor(Color(255, 245, 114));
}

FastFood::FastFood() :
	Food(0)
{
	setFillColor(Color(255, 67, 0));
}

SnakeSegment::SnakeSegment(int player)
{
	setFillColor(Color::Blue);
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
    add_food(5);
}

int Level::get_tile(int idx)
{
    return m_board[idx];
}

void Level::add_food(int num)
{
    for (int i = 0; i < num; i++)
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
