#include "Types.h"
#include "Renderer.h"
#include "Objeto.h"
#include <ctime>
#pragma once
class Bomba : public Objeto
{
public:
	Bomba( int, int, std::vector<int>, int );
	~Bomba();
	int getOwner() override;
	void update() override;
};

