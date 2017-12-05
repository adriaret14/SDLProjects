#pragma once
#include "Objeto.h"
class PowerUp :
	public Objeto
{
public:
	PowerUp( int, int, PwrUpTipo );
	~PowerUp();
};

