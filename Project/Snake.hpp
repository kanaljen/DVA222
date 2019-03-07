#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include "GameObjects.hpp"
#include "Engine.hpp"

class Snake
{
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
	Snake(int player,Level* level);
	void draw(GamePlay* state);
	void update();
	bool isAlive();
private:
	void tryMove(int newpos);
	void collision(int tiletype);
	void move();
};

