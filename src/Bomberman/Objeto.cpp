#include "Objeto.h"

Objeto::Objeto() :
	tipo(ObjTipo::NADA)
{}

Objeto::Objeto(ObjTipo t, int i, int j) :
	tipo(t)
{
	pos.y = 128 + i * 48;
	pos.x = 48 + j * 48;
	pos.w = rect.w = 48;
	pos.h = rect.h = 48;
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
	Renderer::Instance()->PushSprite(ITEMS, rect, pos);
}