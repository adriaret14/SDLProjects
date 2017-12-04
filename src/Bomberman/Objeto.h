#pragma once
#include "Renderer.h"
#include <time.h>
#include <iostream>
enum class ObjTipo { DEST, NO_DEST, PWRUP, BOMB, EXP, NADA };
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
	int hits;
	virtual bool hit();
	virtual int powerup();

	bool boom;
	int owner;
	virtual int getOwner();

	//PowerUp
	int pwr;

	bool collision;
};

