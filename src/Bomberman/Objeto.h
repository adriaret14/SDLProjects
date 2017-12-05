#pragma once
#include "Renderer.h"
#include <time.h>
#include <iostream>
enum class ObjTipo { DEST, NO_DEST, PWRUP, BOMB, EXP, NADA };
enum class PwrUpTipo { CASCO, PATINES, NONE };
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

	//Dest
	virtual bool hit();
	virtual PwrUpTipo powerup();

	bool boom;

	//PowerUp
	PwrUpTipo pwrUp;

	bool collision;
};

