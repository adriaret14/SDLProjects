#include "Types.h"
#include "Renderer.h"
#include <string>
#pragma once

enum estadoActual {Running, GoToLvl1, GoToLvl2, GoToRank, Exit};
class Escena
{
public:
	Escena(int, int);
	~Escena();
	virtual void update()=0;
	virtual void draw()=0;
	virtual void eHandler()=0;

	estadoActual Estado;
protected:
	SDL_Rect background;
	std::unordered_map<std::string, bool> eventos;
};

