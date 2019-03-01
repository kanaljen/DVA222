#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#define SIZE 800

using namespace sf;

class Engine
{
	RenderWindow m_window;
	Level m_level;
	int m_input[3];
	std::vector<Snake*> m_snakes;
public:
	Engine();
	void start();
private:
	void readInput();
	void update();
	void draw();
	void handleKeys(int key);
};