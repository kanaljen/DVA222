
#include "Snake.hpp"
#include <iostream>

Snake::Snake(int player,Level* level):
    m_player(player),
    m_level(level),
    m_lifetime(1),
    m_poweruptime(0),
    m_score(2),
    m_speed(1)
{
    int j;
    while((j<2*ROW)||(j>FULLSIZE-2*ROW)||(j%ROW<3)||(j%ROW>7))j = m_level->getEmptyTile();
    m_body.push_back(j);
    int tail = randomizer(4);
    switch (tail)
    {
        case UP:
            m_body.push_back(j-ROW);
            m_direction = DOWN;
            break;
        case RIGHT:
            m_body.push_back(j+1);
            m_direction = LEFT;
            break;
        case DOWN:
            m_body.push_back(j+ROW);
            m_direction = UP;
            break;
        case LEFT:
            m_body.push_back(j-1);
            m_direction = RIGHT;
            break;
        default:
            break;
    }
}

void Snake::draw(GamePlay* state)
{
    m_blocks.clear();
    for(int i = 0;i < m_body.size();i++)
    {
        m_blocks.push_back(new SnakeStraight);
    }

}

void Snake::update()
{
    int try_move = input[m_player];
    if(try_move == -m_direction)m_direction = m_direction;
    else m_direction = try_move;
    switch(m_direction)
    {
        case UP:
            try_move(m_body[0]-ROW);
            break;
        case LEFT:
            try_move(m_body[0]-1);
            break;
        case DOWN:
            try_move(m_body[0]+ROW);
            break;
        case RIGHT:
            try_move(m_body[0]+1);
            break;
        default:
            break;
    }
}

bool Snake::isAlive()
{
    return m_alive;
}

void Snake::tryMove(int newpos) {
    int tiletype = m_level->getTile(newpos);
    if(tiletype != EMPTY)collision(tiletype);
    else move();
}

void Snake::collision(int tiletype) {
    switch(tiletype)
    {
        case WALL:
            m_alive = false;
            std::cout << "Snake " << m_player << " was killed by a wall!" << std::endl;
            break;
        case STDFOOD:
            m_score += 1;
            std::cout << "Snake " << m_player << " ate standard food!" << std::endl;
            move();
            break;
        case VALUEFOOD:
            m_score += 5;
            std::cout << "Snake " << m_player << " ate valuable food!" << std::endl;
            move();
            break;
        default:
            move();
            break;
    }
}

void Snake::move()
{
    int size = int(m_body.size());
    int tile;
    for(int i = size;i > -1;i--)
    {
        if(i == 0)
        {
            switch(m_direction)
            {
                case UP:
                    tile = m_body[0] - ROW;
                    break;
                case RIGHT:
                    tile = m_body[0] + 1;
                    break;
                case DOWN:
                    tile = m_body[0] + ROW;
                    break;
                case LEFT:
                    tile = m_body[0] - 1;
                    break;
            }
            m_body[0] = tile;
            m_level->setPlayerTile(m_player,tile);
        }
        else if(i == size)
        {
            m_level->clearTile(m_body[size]);
            m_body[size] = m_body[size-1];
        }
        else m_body[size] = m_body[size-1];
    }
}

