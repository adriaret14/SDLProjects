#include "Escena.h"



Escena::Escena(int width, int height):
		Estado(estadoActual::Running),
		background({0, 0, 0, 0})
{
}


Escena::~Escena()
{
	Renderer::Instance()->EmptyRenderer();
}
