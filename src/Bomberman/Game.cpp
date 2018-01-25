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
			escena = new Play(1);
			esc = escenaActual::Play;
			break;
		case estadoActual::GoToLvl2:
			escena->~Escena();
			escena = new Play(2);
			esc = escenaActual::Play;
			break;
		case estadoActual::GoToRank:
			escena->~Escena();
			escena = new Ranking();
			esc = escenaActual::Ranking;
			break;
		case estadoActual::Exit:
			if (esc == escenaActual::Ranking || esc == escenaActual::Play)
			{
				escena->~Escena();
				escena = new Menu();
				esc = escenaActual::Menu;
			}
			else
			{
				escena->~Escena();
				exit(0);
			}
			break;
		}
	}
}

