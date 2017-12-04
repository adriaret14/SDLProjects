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

	//Dest
	int hits;
	virtual bool hit();
	virtual int powerup();

	//Bomb
	bool boom;
	int owner;
	std::vector<int> exps;
	virtual int getOwner();
	double timer;

	//PowerUp
	int pwr;

	bool collision;
};

