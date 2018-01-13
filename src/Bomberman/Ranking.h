#pragma once
#include "Escena.h"
#include <iostream>
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
	std::list<RankStruct> createRankingList();

	SDL_Rect exitRect;
	SDL_Rect topTenRect;

	//Pos 1
	SDL_Rect posOneNumRect;
	SDL_Rect posOneNameRect;
	SDL_Rect posOneScoreRect;

	//Pos 2
	SDL_Rect posTwoNumRect;
	SDL_Rect posTwoNameRect;
	SDL_Rect posTwoScoreRect;

	//Pos 3
	SDL_Rect posThrNumRect;
	SDL_Rect posThrNameRect;
	SDL_Rect posThrScoreRect;

	//Pos 4
	SDL_Rect posForNumRect;
	SDL_Rect posForNameRect;
	SDL_Rect posForScoreRect;

	//Pos 5
	SDL_Rect posFivNumRect;
	SDL_Rect posFivNameRect;
	SDL_Rect posFivScoreRect;

	//Pos 6
	SDL_Rect posSixNumRect;
	SDL_Rect posSixNameRect;
	SDL_Rect posSixScoreRect;

	//Pos 7
	SDL_Rect posSevNumRect;
	SDL_Rect posSevNameRect;
	SDL_Rect posSevScoreRect;

	//Pos 8
	SDL_Rect posEitNumRect;
	SDL_Rect posEitNameRect;
	SDL_Rect posEitScoreRect;

	//Pos 9
	SDL_Rect posNinNumRect;
	SDL_Rect posNinNameRect;
	SDL_Rect posNinScoreRect;

	//Pos 10
	SDL_Rect posTenNumRect;
	SDL_Rect posTenNameRect;
	SDL_Rect posTenScoreRect;
};

