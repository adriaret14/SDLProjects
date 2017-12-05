#include "Dest.h"

Dest::Dest( int i, int j ):
	Objeto( ObjTipo::DEST, i, j, true ),
	hits(0)
{
	rect.x = 48;
	rect.y = 0;
}


Dest::~Dest()
{
}

bool Dest::hit()
{	
	switch (hits) {
	case 0:
		rect.x += 48;
		hits++;
		return false;
		break;
	case 1:
		return true;
		break;
	}
}

PwrUpTipo Dest::powerup()
{
	int random = rand() % 10;
	if (random == 1)
		return PwrUpTipo::CASCO;
	else if (random == 2)
		return PwrUpTipo::PATINES;
	else
		return PwrUpTipo::NONE;
}
