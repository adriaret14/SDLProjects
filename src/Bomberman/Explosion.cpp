#include "Explosion.h"

Explosion::Explosion( int i, int j, Movimiento m, bool punta) :
	Objeto(ObjTipo::EXP, i, j)
{
	boom = false;
	if (m == Movimiento::NONE)
	{
		rect.y = 0;
	}
	else if (!punta)
	{
		if (m == Movimiento::UP || m == Movimiento::DOWN)
		{
			rect.y = 6 * CELLH;
		}
		else if (m == Movimiento::LEFT || m == Movimiento::RIGHT)
		{
			rect.y = 5 * CELLH;
		}
	}
	else
	{
		switch (m)
		{
		case Movimiento::UP:
			rect.y = 3 * CELLH;
			break;
		case Movimiento::DOWN:
			rect.y = 4 * CELLH;
			break;
		case Movimiento::LEFT:
			rect.y = 1 * CELLH;
			break;
		case Movimiento::RIGHT:
			rect.y = 2 * CELLH;
			break;

		case Movimiento::NONE:
			rect.y = 0;
			break;
		}
	}
	rect.x = 0;
	timer = clock();
	dir = 1;
}


Explosion::~Explosion()
{
}

void Explosion::update()
{
	if ((float)(clock() - timer) >= (float)CLOCKS_PER_SEC/8.0f)
	{
		if (dir == -1 && rect.x == 0)
		{
			boom = true;
		}
		else
		{
			if (rect.x == 3 * CELLW)
			{
				dir = -1;
			}
			rect.x += dir * CELLW;
		}
		timer = clock();
	}	
}
