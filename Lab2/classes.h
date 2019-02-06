#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#define SPEED 10
#define FRAMERATE 60

class Ball: public sf::CircleShape
{
public:
	Ball(float pos_x, float pos_y) : CircleShape(20)
	{
		setPosition(pos_x, pos_y);
		direction.x = 1.5;
		direction.y = 1;
		speed = SPEED;
		setFillColor(sf::Color::White);
	}
	void change_x_direction() 
	{
		direction.x = -direction.x;
	}
	void change_y_direction()
	{
		direction.y = -direction.y;
	}
	void increase_speed()
	{
		if (speed < (SPEED * 3))speed += 1;
	}
	void deincrease_speed()
	{
		if (speed > SPEED/3)speed -= 1;
	}
	sf::Vector2f get_velocity()
	{
		sf::Vector2f velocity;
		velocity.x = direction.x * speed;
		velocity.y = direction.y * speed;
		return velocity;
	}
private:
	sf::Vector2f direction;
	int speed;
};

class GameRectangle : public sf::RectangleShape // Virtual Game Object
{
public:
	GameRectangle(sf::Vector2f rect) :
		RectangleShape(rect),
		active(false)
	{}
	virtual void collision(Ball* ball) = 0;
	virtual void activate() = 0;
	virtual void deactivate() = 0;
	bool is_active()
	{
		return active;
	}
	bool active;
};

class YellowLine: public GameRectangle // Vertical Line
{
public:
	YellowLine(float height, float pos_x, float pos_y) : GameRectangle(sf::Vector2f(5,height))
	{
		setFillColor(sf::Color::Yellow);
		setPosition(pos_x, pos_y);
	}
	void collision(Ball* ball) override
	{
		ball->change_x_direction();
	}
	virtual void activate() override
	{
		setFillColor(sf::Color::Black);
		active = true;
	}
	virtual void deactivate() override
	{
		setFillColor(sf::Color::Yellow);
		active = false;
	}
};

class GreenLine : public GameRectangle // Horizontal Line
{
public:
	GreenLine(float width, float pos_x, float pos_y) : GameRectangle(sf::Vector2f(width, 5))
	{
		setFillColor(sf::Color::Green);
		setPosition(pos_x, pos_y);
	}
	void collision(Ball* ball) override
	{
		ball->change_y_direction();
	}
	virtual void activate() override
	{
		setFillColor(sf::Color::Black);
		active = true;
	}
	virtual void deactivate() override
	{
		setFillColor(sf::Color::Green);
		active = false;
	}
};

class RedBox : public GameRectangle // Speed increase box
{
public:
	RedBox(sf::Vector2f size, float pos_x, float pos_y) : 
		GameRectangle(size)
	{
		setFillColor(sf::Color::Black);
		setOutlineThickness(5);
		setOutlineColor(sf::Color::Red);
		setPosition(pos_x, pos_y);
	}
	void collision(Ball* ball) override
	{
		ball->increase_speed();
	}
	virtual void activate() override
	{
		setFillColor(sf::Color::Red);
		active = true;
	}
	virtual void deactivate() override
	{
		setFillColor(sf::Color::Black);
		active = false;
	}
};

class BlueBox : public GameRectangle // Speed decrease box
{
public:
	BlueBox(sf::Vector2f size, float pos_x, float pos_y) : 
		GameRectangle(size)
	{
		setFillColor(sf::Color::Black);
		setOutlineThickness(5);
		setOutlineColor(sf::Color::Blue);
		setPosition(pos_x, pos_y);
		
	}
	void collision(Ball* ball) override
	{
		ball->deincrease_speed();
	}
	virtual void activate() override
	{
		setFillColor(sf::Color::Blue);
		active = true;
	}
	virtual void deactivate() override
	{
		setFillColor(sf::Color::Black);
		active = false;
	}
};

class Board
{
public:
	Board(float size_x, float size_y) :
		window(sf::VideoMode(size_x, size_y), "Assignment 2 - Bounce!"),
		ball(size_x/2, size_y/3)
	{
		objects.push_back(new YellowLine(size_y, size_x - 5, 0));		// Left Border
		objects.push_back(new YellowLine(size_y, 0, 0));				// Right Border
		objects.push_back(new GreenLine(size_x, 0, 0));					// Top Border
		objects.push_back(new GreenLine(size_x, 0, size_y - 5));		// Bottom Border
		objects.push_back(new GreenLine(size_x/4, size_x/4, size_y/4)); // Obstacle_1
		objects.push_back(new GreenLine(size_x/2, size_x/4, (size_y / 4)*3)); // Obstacle_2
		objects.push_back(new YellowLine(size_y/3, size_x/2, size_y/3)); // Obstacle_3
		objects.push_back(new RedBox(sf::Vector2f(size_x/6,size_y/6),size_x/6,size_y/2));  // Speed Box
		objects.push_back(new BlueBox(sf::Vector2f(size_x / 6, size_y / 6), (size_x / 6)*4, size_y / 2)); // Slow Box
		window.setFramerateLimit(FRAMERATE);		
	}
	void draw();
	bool alive();

private:
	void Board::update();
	Ball ball; // The ball
	std::vector<GameRectangle*> objects;
	sf::RenderWindow window;
};

void Board::draw()
{
	window.clear();
	for (int i = 0; i < objects.size(); i++)window.draw(*objects[i]);
	ball.move(this->ball.get_velocity());
	update();
	window.draw(ball);
	window.display();
}

bool Board::alive()
{
	sf::Event event;
	window.pollEvent(event);
	if (event.type == sf::Event::Closed)
	{
		window.close();
		return false;
	}
	return true;
}

void Board::update()
{
	for (GameRectangle* object : objects)
	{
		if (this->ball.getGlobalBounds().intersects(object->getGlobalBounds()))
		{
			if(!object->is_active())object->collision(&ball);
			object->activate();
		}
		else
		{
			object->deactivate();
		}
	}
}