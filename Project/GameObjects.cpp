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
    setColor(Color::Blue);
}

StandardFood::StandardFood():
	Food(1)
{

}

FastFood::FastFood() :
	Food(0)
{
    setColor(Color::Green);
}

SnakeSegment::SnakeSegment(int player, float rotation):
    m_player(player),
    m_rotation(rotation)
{
    if(player == 2)setColor(Color::Green);
    else if(player == 3)setColor(Color::Yellow);
    rotate(m_rotation);
    if (m_rotation==0)setOrigin(0,0);
    else if (m_rotation==90)setOrigin(0,BLOCKSIZE);
    else if(m_rotation==180)setOrigin(BLOCKSIZE,BLOCKSIZE);
    else if(m_rotation==270)setOrigin(BLOCKSIZE,0);

}

SnakeHead::SnakeHead(int player, float rotation):
        SnakeSegment(player,rotation)
{
    texture.loadFromFile("images/snake_head.png");
    setTexture(texture);
}

SnakeTail::SnakeTail(int player, float rotation):
        SnakeSegment(player,rotation)
{
    texture.loadFromFile("images/snake_tail.png");
    setTexture(texture);
}

SnakeBend::SnakeBend(int player, float rotation):
        SnakeSegment(player,rotation)
{
    texture.loadFromFile("images/snake_bend.png");
    setTexture(texture);
}

SnakeStraight::SnakeStraight(int player, float rotation):
        SnakeSegment(player,rotation)
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
        else m_board[i] = EMPTY;
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
    while (m_board[j] != EMPTY)
    {
        j = randomizer(FULLSIZE);
    }
    return j;
}

void Level::setPlayerTile(int player,int tile)
{
    if(m_board[tile] != (EMPTY || WALL))
    {
        switch(player)
        {
            case 1:
                m_board[tile] = SNAKE1;
                break;
            case 2:
                m_board[tile] = SNAKE2;
                break;
            case 3:
                m_board[tile] = SNAKE3;
                break;
            default:
                break;
        }
    }
}

void Level::clearTile(int tile)
{
    if(m_board[tile] != EMPTY && WALL)m_board[tile] = EMPTY;
}

void Level::d_printLevel() {
    for(int i = 0;i < FULLSIZE;i++)
    {
        if(i%ROW == ROW-1)std::cout << m_board[i] << std::endl;
        else std::cout << m_board[i];
    }
}
