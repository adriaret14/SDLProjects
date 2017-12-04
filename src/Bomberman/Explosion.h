#pragma once
#include "Objeto.h"
#include "Player.h"
class Explosion :
	public Objeto
{
public:
	Explosion(int, int, Movimiento, bool, int);
	~Explosion();

	void update() override;
};

