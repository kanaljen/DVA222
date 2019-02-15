//
//  main.cpp
//  Assignment_1
//
//  Created by Staffan Brickman & Fredrik Ginsberg on 2019-01-21.
//  Copyright © 2019 kanaljen. All rights reserved.
//
//using namespace System;
#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <time.h>
#include <random>
#pragma comment(lib,"user32.lib") 
#define N 3
#define FALSE 0
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

//using namespace std;

bool isEven(int num)
{
	if (num % 2 != 0)return false;
	else return true;
}

class Tile {
public:
	int number;
	Tile(int number = 0) {
		this->number = number;
	};
	int readValue(void);
};

int Tile::readValue(void)
{
	return number;
}

class Board {
public:
	int boardsize = N*N;
	Tile tiles[N*N];
	int zero_index;
	Board() {
		for (int i = 0; i < (N*N); i++) {
			tiles[i] = Tile(i);
		}
		do
		{
			randomize();
			this->zero_index = findZero();
		} while (!isSolveable());

	}
	void printBoard();
	bool checkBoard();
	void swapTiles(int direction);

private:
	bool isSolveable(void);
	void randomize();
	int findZero();
};

class Player {
public:
	int moves;
	Board board;
	Player() {
		this->moves = 0;
	}
	int readInput(void);
private:
	bool isLegal(int input);
};

int Player::readInput(void) {
	int action = 0;
	bool hasRead = false;
	if (GetAsyncKeyState(VK_UP) && (hasRead == false))
	{
		action = UP;
		hasRead = true;
	}
	if (GetAsyncKeyState(VK_RIGHT) && (hasRead == false))
	{
		action = RIGHT;
		hasRead = true;
	}
	if (GetAsyncKeyState(VK_DOWN) && (hasRead == false))
	{
		action = DOWN;
		hasRead = true;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		if ((hasRead == false))
		{
			action = LEFT;
			hasRead = true;
		}

	}
	if (this->isLegal(action) == true) {
		return action;
	}
	return 0;
}

bool Player::isLegal(int action) {

	if (action == UP)
	{
		if (this->board.zero_index - N >= 0) return true;
	}
	if (action == RIGHT)
	{
		if (this->board.zero_index + 1 < N*N && (this->board.zero_index + 1) % N != 0) return true;
	}
	if (action == DOWN)
	{
		if (this->board.zero_index + N < N*N) return true;
	}
	if (action == LEFT)
	{
		if (this->board.zero_index - 1 >= 0 && (this->board.zero_index - 1) % N != (N - 1)) return true;
	}
	return false;

}

void Board::randomize(void) {
	int temp;
	int randIndex;

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(1, 6);

	for (int i = 0; i < N*N; i++)
		std::swap(this->tiles[i], this->tiles[dis(gen) % (N*N)]);
	//{
	//	randIndex = dis(gen) % (N*N);
	//	temp = this->tiles[i].number;
	//	this->tiles[i].number = this->tiles[randIndex].number;
	//	this->tiles[randIndex].number = temp;

	//}
	//	std::cout << this->tiles[i].number << std::endl;
	//	
	//auto gen = std::default_random_engine(seed);
	//(begin(this->tiles), end(this->tiles), gen);

}

bool Board::checkBoard(void) {
	for (int i = 0; i < ((N*N)-1); i++) {
		if (this->tiles[i].readValue() != i+1)
		{
			return false;
		}
	}
	return true;
}


void Board::printBoard(void) {
	int rows = N;
	for (int i = 0; i < rows; i++) {
		for (int j = i*N; j < (i + 1)*N; j++) {
			std::cout << this->tiles[j].readValue() << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


void Board::swapTiles(int direction) {
	switch (direction) {
	case UP:
	
		std::swap(this->tiles[zero_index], this->tiles[zero_index - N]);

		this->zero_index = zero_index - N;
		break;
	case RIGHT:
	
		std::swap(this->tiles[zero_index], this->tiles[zero_index + 1]);

		this->zero_index = zero_index + 1;
		break;
	case DOWN:

		std::swap(this->tiles[zero_index], this->tiles[zero_index + N]);
		
		this->zero_index = zero_index + N;
		break;
	case LEFT:

		std::swap(this->tiles[zero_index], this->tiles[zero_index - 1]);
	
		this->zero_index = zero_index - 1;
		break;
	default:
		break;
	}
}

int Board::findZero(void) {
	for (int i = 0; i < (N*N); i++)if (this->tiles[i].readValue() == 0) return i;
	return 0;
}

bool Board::isSolveable(void)
{
	int i, j, row;
	bool rowIsEven;
	int inversions = 0;
	for (i = 0; i < N*N; i++)
	{
		for (j = i + 1; j < N*N; j++)
		{
			if (this->tiles[j].readValue() == 0) continue;
			if (this->tiles[i].readValue() > this->tiles[j].readValue()) inversions++;
		}
	}
	if (!isEven(N))
	{
		if (isEven(inversions)) return true;
		else return false;
	}
	else
	{
		row = N - (this->zero_index / N);
		if (isEven(row))
		{
			if (!isEven(inversions))return true;
			else return false;
		}
		else
		{
			if (isEven(inversions))return true;
			else return false;

		}
	}
	return false;
}

int main(void) {

	Player player;
	int action;
	std::srand(time(nullptr));



	while (player.board.checkBoard() == false) {
		system("CLS");
		std::cout << "MOVE " << player.moves << std::endl;
		std::cout << "-------" << std::endl;
		player.board.printBoard();
		action = player.readInput();
		if (action != 0) // Valid input
		{
			player.board.swapTiles(action);
			player.moves += 1;
		}
		Sleep(250);
	}
	std::cout << "Board Solved!" << std::endl;
	player.board.printBoard();
	getchar();
	return 0;
}