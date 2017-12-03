#pragma once
#include "Renderer.h"
enum class ObjTipo { DEST, NO_DEST, PWRUP, BOMB };
class Objeto
{
public:
	Objeto( ObjTipo, int, int );
	~Objeto();

	virtual void update();
	void draw();

	ObjTipo tipo;
	SDL_Rect rect;
	SDL_Rect pos;
};

