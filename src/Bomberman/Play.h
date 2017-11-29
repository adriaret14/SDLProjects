#pragma once
#include "Escena.h"
#include <iostream>
class Play :
	public Escena
{
public:
	Play();
	~Play();

	void draw() override;
	void update() override;
	void eHandler() override;

};

