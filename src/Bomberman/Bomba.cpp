#include "Bomba.h"

Bomba::Bomba( int i, int j, std::vector<int> e, int n):
	Objeto(ObjTipo::BOMB, i, j, true)
{
	owner = n;
	exps = e;
	rect.x = 0;
	rect.y = 48;
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

}
