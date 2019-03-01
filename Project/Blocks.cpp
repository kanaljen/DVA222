#include "Game.h"

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

GameBlock::GameBlock():
	RectangleShape(sf::Vector2f(BLOCKSIZE, BLOCKSIZE))
{}

Wall::Wall()
{
	setFillColor(Color::Black);
}

SnakeBlock::SnakeBlock(int player)
{
	switch (player)
	{
	case 1:
		setFillColor(Color::Blue);
		break;
	case 2:
		setFillColor(Color::Cyan);
		break;
	case 3:
		setFillColor(Color::Green);
		break;
	default:
		break;
	}
}

Food::Food(int value):
	m_value(value)
{}

ValuableFood::ValuableFood() :
	Food(5)
{
	setFillColor(Color::Red);
}

StandardFood::StandardFood():
	Food(1)
{
	setFillColor(Color::Yellow);
}

FastFood::FastFood() :
	Food(0)
{
	setFillColor(Color::Yellow);
}