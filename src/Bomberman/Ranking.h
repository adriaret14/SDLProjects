#pragma once
#include "Escena.h"
#include <iostream>
class Ranking :
	public Escena
{
public:
	Ranking();
	~Ranking();
	void draw() override;
	void update() override;
	void eHandler() override;
private:
	SDL_Rect exitRect;
};
