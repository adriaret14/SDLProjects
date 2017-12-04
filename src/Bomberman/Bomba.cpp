#include "Bomba.h"

Bomba::Bomba( int i, int j, int n):
	Objeto(ObjTipo::BOMB, i, j, true)
{
	owner = n;
	rect.x = 0;
	rect.y = 48;
	timer = clock();
	boom = false;
}

Bomba::~Bomba()
{
}

int Bomba::getOwner()
{
	return owner;
}

void Bomba::update()
{
	if (clock() - timer >= CLOCKS_PER_SEC*3)
	{
		boom = true;
	}
}
