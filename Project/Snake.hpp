#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include <sstream>
#include "GameObjects.hpp"
#include "Engine.hpp"
#include "States.hpp"

class GamePlay;

class Snake
{
    Font m_font;
	const int m_player;
	Level* m_level;
	int m_lifetime;

	int m_speed;
	int m_poweruptime;
	int m_direction;
	bool m_alive;
	std::vector<int> m_body;
	std::vector<SnakeSegment*> m_blocks;
	int m_score;
	Text m_scoretext;
public:
	bool hasHitFastFood;
	Snake(int player,Level* level);
	void draw(GamePlay* state);
	void update(int input);
	int whatPlayer();
	bool isAlive();
	void setPowerUp(int speed, int poweruptime);
private:
	void tryMove(int newpos);
	void collision(int tiletype, int newpos);
	void move();
	void updateText();
};

