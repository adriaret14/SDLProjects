#include "Objeto.h"

Objeto::Objeto() :
	tipo(ObjTipo::NADA),
	collision(false)
{}

Objeto::Objeto(ObjTipo t, int i, int j, bool c) :
	tipo(t),
	collision(c),
	boom(false)
{
	pos.x = BORDER_LEFT + i * CELLW;
	pos.y = BORDER_TOP + j * CELLH;
	pos.w = rect.w = CELLW;
	pos.h = rect.h = CELLH;
}

Objeto::Objeto(ObjTipo t, int i, int j) :
	tipo(t),
	collision(false)
{
	pos.x = BORDER_LEFT + i * CELLW;
	pos.y = BORDER_TOP + j * CELLH;
	pos.w = rect.w = CELLW;
	pos.h = rect.h = CELLH;
}

Objeto::~Objeto()
{
}

void Objeto::update()
{
return;
}

void Objeto::draw()
{
	if (tipo == ObjTipo::EXP)
	{
		Renderer::Instance()->PushSprite(EXPS, rect, pos);
	}
	else
	{
		Renderer::Instance()->PushSprite(ITEMS, rect, pos);
	}
}

bool Objeto::hit()
{
	return false;
}

PwrUpTipo Objeto::powerup()
{
	return PwrUpTipo::NONE;
}
