#include "NoDest.h"



NoDest::NoDest( int i, int j ):
	Objeto(ObjTipo::NO_DEST, i, j, true)
{
	rect.x = 0;
	rect.y = 0;
}

NoDest::~NoDest()
{
}
