#pragma once

#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include "GameObjects.hpp"
#include "Engine.hpp"

using namespace sf;
class Engine;

class GameState
{
	Engine& m_engine;
public:
    GameState(Engine& engine);
    void pushToRenderQ(Drawable*);
    virtual void update() = 0;
    virtual void readInput(Event event) = 0;
	void setNextState(int state);
};

class GamePlay: public GameState
{
    const int m_noplayers;
    Level m_level;
	int m_input[3];
    std::vector<GameObject*> m_dynamicObjects;
    std::vector<GameObject*> m_levelObjects;
public:
	GamePlay(Engine& engine,int noPlayers);
	void update() override;
    void readInput(Event event) override;
	void handleKeys(int key);
	void updateSnakes();
};

class TopMenu: public GameState
{
	Font m_font;
	int m_selection;
	Text m_title;
	Text m_oneplayer;
	Text m_twoplayer;
	Text m_threeplayer;
	Text m_exit;
	std::vector<Text*> m_menuObjects;
public:
	TopMenu(Engine& engine);
	void update() override;
	void readInput(Event event) override;
	void moveMenu(int direction);
	void updateTextColor();
};

