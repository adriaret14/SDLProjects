#include "Objeto.h"



Objeto::Objeto( ObjTipo t, int i, int j ):
	tipo(t)
{
	pos.x = 128 + i*48;
	pos.y = 48 + j*48;
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
