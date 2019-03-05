#include "States.hpp"
#include <iostream>

#define MNURESUME	1
#define MNUEXIT		2

#define MENUUP		2
#define MENUDOWN	1

GameMenu::GameMenu(Engine& engine) :
	GameState(engine),
	m_selection(0)
{
	FloatRect textRect;
	int titleSize = SIZE/4;
	int menuSize = SIZE/8;

	if (!m_font.loadFromFile("fonts/porcelain.ttf"))
		throw std::invalid_argument("INVALID FONT!");

	// Title 
	m_title.setString("PAUSED");
	m_title.setFont(m_font);
	m_title.setCharacterSize(titleSize);
	textRect = m_title.getLocalBounds();
	m_title.setOrigin(textRect.left + textRect.width / 2.0f, 0);
	m_title.setPosition(SIZE / 2, 0);
	// Resume game
	m_resume.setString("resume game");
	m_resume.setFont(m_font);
	m_resume.setCharacterSize(menuSize);
	textRect = m_resume.getLocalBounds();
	m_resume.setOrigin(textRect.left + textRect.width / 2.0f, 0);
	m_resume.setPosition(SIZE / 2, 2 * (SIZE / 8));
	// Quit current game
	m_exit.setString("quit current game");
	m_exit.setFont(m_font);
	m_exit.setCharacterSize(menuSize);
	textRect = m_exit.getLocalBounds();
	m_exit.setOrigin(textRect.left + textRect.width / 2.0f, 0);
	m_exit.setPosition(SIZE / 2, 3 * (SIZE / 8));
}

void GameMenu::update()
{
	m_menuObjects.clear();

	updateTextColor();
	m_menuObjects.push_back(&m_title);
	m_menuObjects.push_back(&m_resume);
	m_menuObjects.push_back(&m_exit);

	for (Text* text : m_menuObjects)pushToRenderQ(text);
}

void GameMenu::handleInput(Event event)
{
	switch (event.type)
	{
	case Event::Closed:
		setNextState(TERMINATE);
		break;
	case Event::KeyPressed:
		switch (event.key.code)
		{
		case Keyboard::Up:
			moveMenu(MENUUP);
			break;
		case Keyboard::Down:
			moveMenu(MENUDOWN);
			break;
		case Keyboard::Return:
			switch (m_selection)
			{
			case MNURESUME:
				setNextState(RESUMEGAME);
				break;
			case MNUEXIT:
				setNextState(BACKTOTOP);
				break;
			default:
				break;
			}
		default:
			break;
		}
	default:
		break;
	}
}

void GameMenu::moveMenu(int direction)
{
	switch (direction)
	{
	case MENUUP:
		m_selection = m_selection < 2 ? m_selection : m_selection - 1;
		break;
	case MENUDOWN:
		m_selection = m_selection > 1 ? m_selection : m_selection + 1;
		break;
	default:
		break;
	}
}

void GameMenu::updateTextColor()
{
	m_title.setFillColor(Color::White);
	m_resume.setFillColor(Color::White);
	m_exit.setFillColor(Color::White);

	switch (m_selection)
	{
	case MNURESUME:
		m_resume.setFillColor(Color::Yellow);
		break;
	case MNUEXIT:
		m_exit.setFillColor(Color::Yellow);
		break;
	default:
		break;
	}
}