#include <string>
#include "Escena.h"
#include "Menu.h"
#pragma once
enum class escenaActual { Menu, Play, Ranking, Exit };
class Game
{
public:
	Game();
	~Game();
	void update();
private:
	escenaActual esc;
	Escena *escena;
};

