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

		switch (escena->Estado)
		{
		case estadoActual::Running:

			break;
		case estadoActual::GoToLvl1:
			escena->~Escena();
			escena = new Play();
			break;
		case estadoActual::GoToLvl2:

			break;
		case estadoActual::GoToRank:

			break;
		case estadoActual::Exit:

			break;
		}
	}
}

