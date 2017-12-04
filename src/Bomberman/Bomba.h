#include "Types.h"
#include "Renderer.h"
#include "Objeto.h"
#include <ctime>
#pragma once
class Bomba : public Objeto
{
public:
	Bomba(int, int);
	~Bomba();
	void update() override;

private:
	clock_t timer;
};

