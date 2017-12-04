#include "Bomba.h"

Bomba::Bomba( int i, int j):
	Objeto(ObjTipo::BOMB, i, j, true)
{
	rect.x = 0;
	rect.y = 48;
	timer = clock();
	boom = false;
}

Bomba::~Bomba()
{
}

void Bomba::update()
{
	if (clock() - timer >= CLOCKS_PER_SEC*3)
	{
		boom = true;
	}
}
