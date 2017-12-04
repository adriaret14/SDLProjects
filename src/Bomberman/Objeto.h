#pragma once
#include "Renderer.h"
enum class ObjTipo { DEST, NO_DEST, PWRUP, BOMB, NADA };
class Objeto
{
public:
	Objeto();
	Objeto( ObjTipo, int, int, bool );
	Objeto(ObjTipo, int, int);
	~Objeto();

	virtual void update();
	void draw();

	ObjTipo tipo;
	SDL_Rect rect;
	SDL_Rect pos;

	bool collision;
};

