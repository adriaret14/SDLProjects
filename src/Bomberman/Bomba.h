#include "Types.h"
#include "Renderer.h"
#pragma once
class Bomba
{
public:
	Bomba(int, int);
	~Bomba();
private:
	SDL_Rect pos;
	int rango;
	int dmg;
};

