#pragma once
#include "Objeto.h"
class Dest :
	public Objeto
{
public:
	Dest( int, int );
	~Dest();

	int hits;

	bool hit();
	int powerup();
};

