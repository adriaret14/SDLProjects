#pragma once
#include "Escena.h"
#include <iostream>

struct RankRectStruct {
	SDL_Rect nameRect;
	SDL_Rect scoreRect;
};

class Ranking :
	public Escena
{
public:
	Ranking();
	~Ranking();
	void draw() override;
	void update() override;
	void eHandler() override;
private:
	std::vector<RankStruct> createRankingList();

	SDL_Rect exitRect;
	SDL_Rect topTenRect;

	std::vector<SDL_Rect> rankNums;
	std::vector<RankRectStruct> rankRects;
};

