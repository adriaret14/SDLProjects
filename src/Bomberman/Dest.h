#pragma once
#include "Objeto.h"
class Dest :
	public Objeto
{
public:
	Dest( int, int );
	~Dest();

	bool hit() override;
	PwrUpTipo powerup() override;

private:
	int hits;
};

