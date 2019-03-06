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
	std::vector<int> m_body;
public:
	Snake(int player);
	bool tryMove(int newpos);
	void draw();
private:
	void move();
	void update();
};

