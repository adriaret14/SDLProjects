#pragma once
#include "Escena.h"
#include "player.h"
#include "Objeto.h"
#include "NoDest.h"
#include "Dest.h"
#include "Bomba.h"
#include "PowerUp.h"
#include "Explosion.h"
#include "HUD.h"
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
	int maxTime;
	HUD hud;
	clock_t tiempo;
	MovCheck playerMovementCheck(Movimiento, Player);
	MovCheck bombPlacementCheck(Movimiento, Player);
	std::vector<std::vector<int>> generateExplosionVector(int, int);
	Objeto* getAdjCell(int, int, int, int);
	Player p1;
	std::vector<int> b1;
	Player p2;
	std::vector<int> b2;
	int rows;
	int cols;
	Objeto ***mapa;
	std::string estado;
};

