#include "States.hpp"
#include <iostream>

#define ONPLAYER	1
#define TWPLAYER	2
#define THPLAYER	3
#define MNUEXIT		4

#define MENUUP		2
#define MENUDOWN	1

TopMenu::TopMenu(Engine& engine):
	GameState(engine),
	m_selection(0)
{
	FloatRect textRect;
	int titleSize = 200;
	int menuSize = 100;

	if (!m_font.loadFromFile("porcelain.ttf"))
		throw std::invalid_argument("INVALID FONT!");

	// Title 
	m_title.setString("SNAKE");
	m_title.setFont(m_font);
	m_title.setCharacterSize(titleSize);
	textRect = m_title.getLocalBounds();
	m_title.setOrigin(textRect.left + textRect.width / 2.0f, 0);
	m_title.setPosition(SIZE / 2, 0);
	// One Player
	m_oneplayer.setString("1 Player");
	m_oneplayer.setFont(m_font);
	m_oneplayer.setCharacterSize(menuSize);
	textRect = m_oneplayer.getLocalBounds();
	m_oneplayer.setOrigin(textRect.left + textRect.width / 2.0f, 0);
	m_oneplayer.setPosition(SIZE / 2, 2 * (SIZE / 8));
	// Two Players
	m_twoplayer.setString("2 Players");
	m_twoplayer.setFont(m_font);
	m_twoplayer.setCharacterSize(menuSize);
	textRect = m_twoplayer.getLocalBounds();
	m_twoplayer.setOrigin(textRect.left + textRect.width / 2.0f, 0);
	m_twoplayer.setPosition(SIZE / 2, 3 * (SIZE / 8));
	// Three Players
	m_threeplayer.setString("3 Players");
	m_threeplayer.setFont(m_font);
	m_threeplayer.setCharacterSize(menuSize);
	textRect = m_threeplayer.getLocalBounds();
	m_threeplayer.setOrigin(textRect.left + textRect.width / 2.0f, 0);
	m_threeplayer.setPosition(SIZE / 2, 4 * (SIZE / 8));
	// Exit 
	m_exit.setString("Exit");
	m_exit.setFont(m_font);
	m_exit.setCharacterSize(menuSize);
	textRect = m_exit.getLocalBounds();
	m_exit.setOrigin(textRect.left + textRect.width / 2.0f, 0);
	m_exit.setPosition(SIZE / 2, 5 * (SIZE / 8));
}

void TopMenu::update()
{
	m_menuObjects.clear();

	updateTextColor();
	m_menuObjects.push_back(&m_title);
	m_menuObjects.push_back(&m_oneplayer);
	m_menuObjects.push_back(&m_twoplayer);
	m_menuObjects.push_back(&m_threeplayer);
	m_menuObjects.push_back(&m_exit);

	for (Text* text : m_menuObjects)pushToRenderQ(text);
}

void TopMenu::readInput(Event event)
{
	switch (event.type)
	{
	case Event::Closed:
		setNextState(EXIT);
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
			case ONEPLAYER:
				setNextState(ONEPLAYER);
				break;
			case TWPLAYER:
				setNextState(TWOPLAYER);
				break;
			case THPLAYER:
				setNextState(THREEPLAYER);
				break;
			case MNUEXIT:
				setNextState(EXIT);
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

void TopMenu::moveMenu(int direction)
{
	switch (direction)
	{
	case MENUUP:
		m_selection = m_selection < 2 ? m_selection : m_selection - 1;
		break;
	case MENUDOWN:
		m_selection = m_selection > 3 ? m_selection : m_selection + 1;
		break;
	default:
		break;
	}
}

void TopMenu::updateTextColor()
{
	m_title.setFillColor(Color::White);
	m_oneplayer.setFillColor(Color::White);
	m_twoplayer.setFillColor(Color::White);
	m_threeplayer.setFillColor(Color::White);
	m_exit.setFillColor(Color::White);

	switch (m_selection)
	{
	case ONPLAYER:
		m_oneplayer.setFillColor(Color::Yellow);
		break;
	case TWPLAYER:
		m_twoplayer.setFillColor(Color::Yellow);
		break;
	case THPLAYER:
		m_threeplayer.setFillColor(Color::Yellow);
		break;
	case MNUEXIT:
		m_exit.setFillColor(Color::Yellow);
		break;
	default:
		break;
	}
}