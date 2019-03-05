#pragma once

#include <SFML/Graphics.hpp>
#include <queue>
#include "GameObjects.hpp"
#include "States.hpp"

// STATES
#define TOPMENU		0
#define ONEPLAYER	1
#define TWOPLAYER	2
#define THREEPLAYER	3
#define GAMEMENU	4
#define EXIT	   -1

using namespace sf;
class GameState;
class GamePlay;
class TopMenu;

class Engine
{
	RenderWindow m_window;
    GameState* m_current_state;
    GameState* m_next_state;
    std::queue<Drawable*> m_renderQ;
    GamePlay* m_gameplay;
	TopMenu* m_topmenu;
	friend class GameState;
public:
	Engine();
	void start();
private:
    void readInput();
    void update();
	void draw();
	void setNextState(int state);
};

