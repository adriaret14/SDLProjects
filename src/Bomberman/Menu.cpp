#include "Menu.h"



Menu::Menu():
	Escena::Escena(720,704)
{
}


Menu::~Menu()
{
}

void Menu::draw()
{
	Renderer::Instance()->Clear();
	Renderer::Instance()->PushImage("BG", background);
	Renderer::Instance()->Render();
}

void Menu::update()
{
	std::cout << "Update" << std::endl;
}

void Menu::eHandler()
{
	std::cout << "Event Handler" << std::endl;
}
