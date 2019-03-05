#pragma once

#include <SFML/Graphics.hpp>
#include <queue>
#include "GameObjects.hpp"
#include "States.hpp"

// STATES TRANSITIONS
#define NOTRANSITION	0
#define BACKTOTOP		1
#define PLAYONE			2
#define PLAYTWO			3
#define PLAYTHREE		4
#define TOGAMEMENU		5
#define RESUMEGAME		6
#define TERMINATE		-1

using namespace sf;
class GameState;
class GamePlay;
class TopMenu;
class GameMenu;

class Engine
{
	RenderWindow m_window;
    GameState* m_current_state;
    GameState* m_next_state;
	int m_nextTransition;
    std::queue<Drawable*> m_renderQ;
    GamePlay* m_gameplay;
	TopMenu* m_topmenu;
	GameMenu* m_gamemenu;
	friend class GameState;
public:
	Engine();
	void start();
private:
    void readInput();
    void update();
	void draw();
	void requestTransition(int transition);
	void makeTransition(int transition);
};

