#include <SFML/Graphics.hpp>
#include "Engine.h"

int main()
{
	Engine game;

	game.start();
	
	return 0;
}

/*
TODO:
	RenderPipeline för Engine::Draw
	Meny (eventuellt implementera en state macjine i update eller draw)
	Få maskarna att röra sig
*/