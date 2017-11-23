#include "Types.h"
#include "Renderer.h"
#include <string>
#pragma once

enum estadoActual {Running, GoTo, Exit};
class Escena
{
public:
	Escena(int, int);
	~Escena();
	virtual void update()=0;
	virtual void draw()=0;
	virtual void eHandler()=0;
protected:
	estadoActual Estado;
	SDL_Rect background;
};

