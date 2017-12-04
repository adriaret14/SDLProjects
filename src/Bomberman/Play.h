#pragma once
#include "Escena.h"
#include "player.h"
#include "Objeto.h"
#include "NoDest.h"
#include "Dest.h"
#include "Bomba.h"
#include "PowerUp.h"
#include <iostream>
#include <unordered_map>

enum class MovCheck {RED, GREEN, CORRECTION};

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
	MovCheck playerMovementCheck(Movimiento, Player);
	Objeto* getAdjCell(int, int, int, int);
	Player p1;
	Player p2;
	int rows;
	int cols;
	Objeto ***mapa;
	std::string estado;
};

