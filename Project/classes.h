#pragma once
#include <SFML/Graphics.hpp>

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

class Obstacle{};

class GameRectangle : public sf::RectangleShape // Virtual Game Object
{
public:
	GameRectangle(sf::Vector2f rect) :
		RectangleShape(rect)
	{}
	//virtual void collision(Snake* snake) = 0;

};