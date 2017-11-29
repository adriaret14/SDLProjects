#pragma once
#include "Escena.h"
#include <iostream>
class Menu :
	public Escena
{
public:
	Menu();
	~Menu();

	void draw() override;
	void update() override;
	void eHandler() override;

private:
	SDL_Rect play1Rect;
	SDL_Rect play2Rect;
	SDL_Rect rankRect;
	SDL_Rect exitRect;
	SDL_Rect muteRect;

};

