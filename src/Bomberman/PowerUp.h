#pragma once
#include "Objeto.h"
class PowerUp :
	public Objeto
{
public:
	PowerUp( int, int, int );
	~PowerUp();
	
	int pwr;
};

