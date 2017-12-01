#include "PowerUp.h"



PowerUp::PowerUp( int n, int i, int j ):
	Objeto(ObjTipo::PWRUP, i, j ),
	pwr(n)
{
	if (n == 1)
		rect.x = 48;
	else if (n == 2)
		rect.x = 96;
	else
		rect.x = 48;
	rect.y = 48;
}


PowerUp::~PowerUp()
{
}
