#include "Bomba.h"



Bomba::Bomba(int x, int y):
	pos({0, 0, 0, 0}),
	rango(2),
	dmg(100)
{
	//Renderer::Instance()->LoadTexture(BG, PATH_IMG + "items.png");
	//pos = { 0, 48, x, y };
}


Bomba::~Bomba()
{
}
