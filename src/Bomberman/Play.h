#pragma once
#include "Escena.h"
#include "player.h"
#include "Objeto.h"
#include <iostream>

class Play :
	public Escena
{
public:
	Play( int );
	~Play();

	void draw() override;
	void update() override;
	void eHandler() override;

private:
	Player p1;
	Player p2;
	Objeto **mapa;
};

