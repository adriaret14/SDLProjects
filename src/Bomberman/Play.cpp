#include "Play.h"



Play::Play() :
	Escena::Escena(720, 704)
{
}


Play::~Play()
{
}

void Play::draw()
{
	Renderer::Instance()->Clear();
	Renderer::Instance()->PushImage("BG", background);
	Renderer::Instance()->Render();
}

void Play::update()
{
	std::cout << "jaja Salu2" << std::endl;
}

void Play::eHandler()
{
	std::cout << "Adios" << std::endl;
}
