
#include "Snake.hpp"

Snake::Snake(int player,Level* level):
    m_player(player),
    m_level(level)
{
    int j;
    while((j<2*ROW)||(j>FULLSIZE-2*ROW)||(j%ROW<3)||(j%ROW>7))j = m_level->getEmptyTile();
    m_body.push_back(j);
    int tail = randomizer(4);
    switch (tail)
    {
        case UP:
            m_body.push_back(j-ROW);
            break;
        case RIGHT:
            m_body.push_back(j+1);
            break;
        case DOWN:
            m_body.push_back(j+ROW);
            break;
        case LEFT:
            m_body.push_back(j-1);
            break;
        default:
            break;
    }
}

bool Snake::tryMove(int newpos) {
    // NOKNOW
    return false;
}

void Snake::draw() {
    //
}

void Snake::move() {

}

void Snake::update() {

}
