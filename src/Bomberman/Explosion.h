#pragma once
#include "Objeto.h"
#include "Player.h"
class Explosion :
	public Objeto
{
public:
	Explosion(int, int, Movimiento, bool);
	~Explosion();

	void update() override;

private:
	int dir;
	clock_t timer;
};

