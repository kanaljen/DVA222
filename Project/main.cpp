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
	RenderPipeline f�r Engine::Draw
	Meny (eventuellt implementera en state macjine i update eller draw)
	F� maskarna att r�ra sig
*/