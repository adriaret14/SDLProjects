#include "PowerUp.h"



PowerUp::PowerUp( int i, int j, PwrUpTipo t ):
	Objeto(ObjTipo::PWRUP, i, j )
{
	pwrUp = t;
	switch (pwrUp)
	{
	case PwrUpTipo::CASCO:
		rect.x = 96;
		break;
	case PwrUpTipo::PATINES:
		rect.x = 48;
		break;
	}
	rect.y = 48;
}


PowerUp::~PowerUp()
{
}
