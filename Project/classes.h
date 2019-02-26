#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <random>

#define OPEN 0
#define WALL 1
#define FOOD 2
#define BLOCKSIZE 40

class Menu
{
	const std::string welcome = "Snake";
	const std::string usage = "Use the arrow keys to make a selection";
public:
	Menu(){}
private:
	void startGame();
	void exitGame();
};

class GameBlock : public sf::RectangleShape // Virtual Game Object
{
public:
	GameBlock() :
		RectangleShape(sf::Vector2f(BLOCKSIZE, BLOCKSIZE))
	{}
	//virtual void collision(Snake* snake) = 0;
};

class Wall: public GameBlock
{
public:
	Wall() 
	{
		setFillColor(sf::Color::Black);
	}
};

class Open : public GameBlock
{
public:
	Open()
	{
		setFillColor(sf::Color::White);
	}
};

class Food : public GameBlock
{
public:
	Food()
	{
		setFillColor(sf::Color::Green);
	}
};

class Level 
{
	int* m_board;
	const int m_row; // Size of one row/column
	const int m_full; // Full size of the array
	const Wall wall;
	const Open open;
	const Food food;
public:
	Level(int size) :
		m_row(size / BLOCKSIZE),
		m_full(int(pow(m_row, 2))),
		m_board(new int[int(pow(size/BLOCKSIZE,2))])
	{
		for (int i = 0; i < m_full; i++)
		{
			if (i < m_row)m_board[i] = WALL; // Top row wall
			else if (i % m_row == 0)m_board[i] = WALL; // Left wall
			else if (i % m_row == m_row-1)m_board[i] = WALL; // Right wall
			else if (i > m_full - m_row)m_board[i] = WALL; // Last row wall
			else m_board[i] = OPEN;
		}
		add_food(20);
	};

	GameBlock get_box(int idx)
	{
		int box_value = m_board[idx];
		switch (box_value)
		{
		case WALL: return wall;
		case OPEN: return open;
		case FOOD: return food;
		default: break;
		}
	}

	void add_food(int num)
	{
		for(int i = 0;i < num+1;i++)
		{
			int j = 0;
			std::mt19937 rng;
			rng.seed(std::random_device()());
			std::uniform_int_distribution<std::mt19937::result_type> dist6(1, m_full);
			while (m_board[j] != 0){ j =  dist6(rng); } // Find empty space
			m_board[j] = FOOD;
		}
	};
private:
	bool m_randomizer(int prob) { return (rand() % 100) < prob; }
};