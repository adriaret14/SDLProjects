#include "Dest.h"



Dest::Dest( int i, int j ):
	Objeto( ObjTipo::DEST, i, j, true )
{
	hits = 0;
	rect.x = 48;
	rect.y = 0;
}


Dest::~Dest()
{
}

bool Dest::hit()
{
	std::cout << "hit" << std::endl;
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

int Dest::powerup()
{
	int random = rand() % 10;
	if (random == 1)
		return 1;
	else if (random == 2)
		return 2;
	else
		return 0;
}
