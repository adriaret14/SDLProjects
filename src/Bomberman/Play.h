#pragma once
#include "Escena.h"
#include "player.h"
#include <iostream>
enum class Obstaculo { NO_DESTRUIBLE, DESTRUIBLE_1, DESTRUIBLE_2, NONE };
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
	Obstaculo **mapa;
};

