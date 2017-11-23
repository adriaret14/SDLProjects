#include "Escena.h"



Escena::Escena(int width, int height):
		Estado(estadoActual::Running),
		background({0, 0, 0, 0})
{
		Renderer::Instance()->LoadTexture(BG, PATH_IMG + "bgGame.jpg");
		background = SDL_Rect{ 0, 0, width, height };
}


Escena::~Escena()
{
}
