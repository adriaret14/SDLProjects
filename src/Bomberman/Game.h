#include <string>
#include "Escena.h"
#include "Menu.h"
#include "Play.h"
#include "Ranking.h"
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

