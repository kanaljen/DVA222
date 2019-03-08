#pragma once

#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include "GameObjects.hpp"
#include "Engine.hpp"
#include "Snake.hpp"

using namespace sf;
class Engine;
class Snake;

class GameState
{
	Engine& m_engine;
	int m_next_state;
public:
    GameState(Engine& engine);
    void pushToRenderQ(Drawable*);
    virtual void update() = 0;
	virtual void handleInput(Event event) = 0;
	void readInput();
	void setNextState(int state);
	Background background;
};

class GamePlay: public GameState
{
    const int m_noplayers;
    Level m_level;
	int m_input[4];
    std::vector<GameObject*> m_dynamicObjects;
    std::vector<GameObject*> m_levelObjects;
    std::vector<Snake*> m_snakes;
public:
	GamePlay(Engine& engine,int noPlayers);
	void update() override;
    void handleInput(Event event) override;
	void handleKeys(int key);
	void updateSnakes();
	void drawSnakes();
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
	void handleInput(Event event) override;
	void moveMenu(int direction);
	void updateTextColor();
};

class GameMenu : public GameState
{
	Font m_font;
	int m_selection;
	Text m_title;
	Text m_resume;
	Text m_exit;
	std::vector<Text*> m_menuObjects;
public:
	GameMenu(Engine& engine);
	void update() override;
	void handleInput(Event event) override;
	void moveMenu(int direction);
	void updateTextColor();
};

