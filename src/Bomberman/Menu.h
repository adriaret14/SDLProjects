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

};

