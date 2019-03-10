
#include "Snake.hpp"
#include <iostream>

Snake::Snake(int player,Level* level):
    m_player(player),
    m_level(level),
    m_lifetime(0),
    m_poweruptime(0),
    m_score(0),
    m_speed(2),
	hasHitFastFood(false)
{
    if (!m_font.loadFromFile("fonts/arial.ttf"))
        throw std::invalid_argument("INVALID FONT!");
    m_scoretext.setFont(m_font);
    m_scoretext.setCharacterSize(5*BLOCKSIZE/6);
    m_scoretext.setFillColor(Color::White);
    updateText();

    int j = m_level->getEmptyTile(), quadrant = 0, tail = 0;
    quadrant = randomizer(4)+1;
    switch(quadrant)
    {
        case 1:
            while(!((j/ROW < ROW/2)&&(j%ROW >= ROW/2)))j = m_level->getEmptyTile();

            tail = randomizer(100) > 49 ? j-ROW : j+1;
            m_direction = randomizer(100) > 49 ? DOWN : LEFT;
            break;
        case 2:
            while(!((j/ROW < ROW/2)&&(j%ROW < ROW/2)))j = m_level->getEmptyTile();
            tail = randomizer(100) > 49 ? j-ROW : j-1;
            m_direction = randomizer(100) > 49 ? DOWN : RIGHT;
            break;
        case 3:
            while(!((j/ROW >= ROW/2)&&(j%ROW < ROW/2)))j = m_level->getEmptyTile();
            tail = randomizer(100) > 49 ? j+ROW : j-1;
            m_direction = randomizer(100) > 49 ? UP : RIGHT;
            break;
        case 4:
            while(!((j/ROW >= ROW/2)&&(j%ROW >= ROW/2)))j = m_level->getEmptyTile();
            tail = randomizer(100) > 49 ? j+ROW : j+1;
            m_direction = randomizer(100) > 49 ? UP : LEFT;
            break;
        default:
            std::cout << "Wrong value on quadrant" << std::endl;
            break;
    }
    m_body.push_back(j);
    m_level->setPlayerTile(m_player,j);
    m_body.push_back(tail);
    m_level->setPlayerTile(m_player,tail);
    m_alive = true;
}

void Snake::draw(GamePlay* state)
{
    SnakeSegment* segment;

    int row, col, snakesize = m_body.size();
    m_blocks.clear();
    for(int i = 0;i < snakesize;i++)
    {
        if(i == 0){
            if(m_direction == UP)m_blocks.push_back(new SnakeHead(m_player,0));
            else if(m_direction == RIGHT)m_blocks.push_back(new SnakeHead(m_player,90));
            else if(m_direction == DOWN)m_blocks.push_back(new SnakeHead(m_player,180));
            else if(m_direction == LEFT)m_blocks.push_back(new SnakeHead(m_player,270));
        }
        else if (i == snakesize-1)
        {
            if(m_body[i-1] - m_body[i] == 1)m_blocks.push_back(new SnakeTail(m_player,90));
            else if(m_body[i-1] - m_body[i] == ROW)m_blocks.push_back(new SnakeTail(m_player,180));
            else if(m_body[i-1] - m_body[i] == -1)m_blocks.push_back(new SnakeTail(m_player,270));
            else m_blocks.push_back(new SnakeTail(m_player,0));
        }
        else {
            if((m_body[i-1] - m_body[i] == ROW)&&(m_body[i+1] - m_body[i] == -ROW))
				m_blocks.push_back(new SnakeStraight(m_player,0));
            else if((m_body[i-1] - m_body[i] == -ROW)&&(m_body[i+1] - m_body[i] == ROW))m_blocks.push_back(new SnakeStraight(m_player,0));
            else if((m_body[i-1] - m_body[i] == 1)&&(m_body[i+1] - m_body[i] == -1))m_blocks.push_back(new SnakeStraight(m_player,90));
            else if((m_body[i-1] - m_body[i] == -1)&&(m_body[i+1] - m_body[i] == 1))m_blocks.push_back(new SnakeStraight(m_player,90));
            else if((m_body[i-1] - m_body[i] == ROW)&&(m_body[i+1] - m_body[i] == -1))m_blocks.push_back(new SnakeBend(m_player,0)); //
            else if((m_body[i-1] - m_body[i] == ROW)&&(m_body[i+1] - m_body[i] == 1))m_blocks.push_back(new SnakeBend(m_player,270));
            else if((m_body[i-1] - m_body[i] == -ROW)&&(m_body[i+1] - m_body[i] == -1))m_blocks.push_back(new SnakeBend(m_player,90));
            else if((m_body[i-1] - m_body[i] == -ROW)&&(m_body[i+1] - m_body[i] == 1))m_blocks.push_back(new SnakeBend(m_player,180));
            else if((m_body[i-1] - m_body[i] == 1)&&(m_body[i+1] - m_body[i] == ROW))m_blocks.push_back(new SnakeBend(m_player,270));
            else if((m_body[i-1] - m_body[i] == 1)&&(m_body[i+1] - m_body[i] == -ROW))m_blocks.push_back(new SnakeBend(m_player,180));
            else if((m_body[i-1] - m_body[i] == -1)&&(m_body[i+1] - m_body[i] == ROW))m_blocks.push_back(new SnakeBend(m_player,0)); //
            else if((m_body[i-1] - m_body[i] == -1)&&(m_body[i+1] - m_body[i] == -ROW))m_blocks.push_back(new SnakeBend(m_player,90));
        }
        segment = m_blocks.back();
        row = m_body[i]/ROW;
        col = m_body[i]%ROW;
        segment->setPosition(Vector2f(col*BLOCKSIZE,row*BLOCKSIZE));
    }
    for(SnakeSegment* segment: m_blocks)state->pushToRenderQ(segment);

    state->pushToRenderQ(&m_scoretext);
}

void Snake::update(int input)
{
    m_lifetime++;
    if(m_poweruptime > 0)m_poweruptime--;
    if(m_poweruptime == 0)m_speed = 2;
    if(m_lifetime%m_speed == 0)
    {
        int try_move = input;
        if(try_move == 0)m_direction = m_direction;
        else if(try_move == -m_direction)m_direction = m_direction;
        else m_direction = try_move;
        switch(m_direction)
        {
            case UP:
                tryMove(m_body[0]-ROW);
                break;
            case LEFT:
                tryMove(m_body[0]-1);
                break;
            case DOWN:
                tryMove(m_body[0]+ROW);
                break;
            case RIGHT:
                tryMove(m_body[0]+1);
                break;
            default:
                break;
        }
        updateText();
    }
}

bool Snake::isAlive()
{
    return m_alive;
}

void Snake::tryMove(int newpos) {
    int tiletype = m_level->getTile(newpos);
    if(tiletype != EMPTY)collision(tiletype,newpos);
    else move();
}

void Snake::collision(int tiletype, int newpos) {
    switch(tiletype)
    {
        case WALL:
            m_alive = false;
            for(int i = 0;i < m_body.size();i++)m_level->clearTile(m_body[i]);
            std::cout << "Snake " << m_player << " was killed by a wall!" << std::endl;
            break;
        case SNAKE1:
            m_alive = false;
            for(int i = 0;i < m_body.size();i++)m_level->clearTile(m_body[i]);
            std::cout << "Snake " << m_player << " was killed by a snake 1!" << std::endl;
            break;
        case SNAKE2:
            m_alive = false;
            for(int i = 0;i < m_body.size();i++)m_level->clearTile(m_body[i]);
            std::cout << "Snake " << m_player << " was killed by a snake 2!" << std::endl;
            break;
        case SNAKE3:
            m_alive = false;
            for(int i = 0;i < m_body.size();i++)m_level->clearTile(m_body[i]);
            std::cout << "Snake " << m_player << " was killed by a snake 3!" << std::endl;
            break;
        case STDFOOD:
            m_score += 1;
            m_body.insert(m_body.begin(),newpos);
            m_level->setPlayerTile(m_player,newpos);
            m_level->addFood(1);
            break;
        case VALUEFOOD:
            m_score += 5;
            m_body.insert(m_body.begin(),newpos);
            m_level->setPlayerTile(m_player,newpos);
            m_level->addFood(1);
            break;
        case FASTFOOD:
			hasHitFastFood = true;
   /*       m_speed = 1;
            m_poweruptime = 50;*/
            m_level->addFood(1);
            move();
            break;
        default:
            move();
            break;
    }
}

void Snake::move()
{
    int size = int(m_body.size()) - 1;
    int tile;
    for(int i = size;i > -1;i--)
    {
        if(i == 0)  // Head
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
                default:
                    break;
            }
            m_body[0] = tile;
            m_level->setPlayerTile(m_player,tile);
        }
        else if(i == size)
        {
            m_level->clearTile(m_body[i]);
            m_body[size] = m_body[i-1];
        }
        else m_body[i] = m_body[i-1];
    }
}

void Snake::updateText()
{
    FloatRect textRect;
    std::stringstream scoretext;

    if(m_player == 1)
    {
        scoretext << "P" << m_player << ": "<< m_score;
        m_scoretext.setString( scoretext.str().c_str() );
        textRect = m_scoretext.getLocalBounds();
        m_scoretext.setOrigin(0, 0);
        m_scoretext.setPosition(Vector2f(BLOCKSIZE,0));
    }
    else if(m_player == 2)
    {
        scoretext << "P" << m_player << ": "<< m_score;
        m_scoretext.setString( scoretext.str().c_str() );
        textRect = m_scoretext.getLocalBounds();
        m_scoretext.setOrigin(textRect.left + textRect.width / 2.0f, 0);
        m_scoretext.setPosition(SIZE / 2, 0);
    }
    else if(m_player == 3)
    {
        scoretext << "P" << m_player << ": "<< m_score;
        m_scoretext.setString( scoretext.str().c_str() );
        textRect = m_scoretext.getLocalBounds();
        m_scoretext.setOrigin(textRect.left + textRect.width, 0);
        m_scoretext.setPosition(SIZE - BLOCKSIZE, 0);
    }
}

void Snake::setPowerUp(int speed, int poweruptime)
{
	m_speed = speed;
	m_poweruptime = poweruptime;

}

