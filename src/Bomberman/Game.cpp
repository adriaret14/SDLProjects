#include "Game.h"


//enum class estadoActual { Running, Exit, GoTo };
Game::Game() :
	esc(escenaActual::Menu),
	escena(nullptr)
{
	escena = new Menu();
}


Game::~Game()
{
}

void Game::update()
{
	while (esc != escenaActual::Exit)
	{
		//Bucle de vida del juego
		escena->draw();
		escena->update();
		escena->eHandler();
	}
}

