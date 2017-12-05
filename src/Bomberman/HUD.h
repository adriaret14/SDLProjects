#pragma once
#include "Renderer.h"
#include "Player.h"
#include <time.h>
class HUD
{
public:
	HUD(Player &, Player &);
	~HUD();

	void update();
	void draw();
	void setTime( int );

private:
	clock_t timer;

	std::vector<std::string> nums;
	Player &Player1;
	Player &Player2;

	SDL_Rect tPlayer1;
	SDL_Rect tPlayer2;
	SDL_Rect tLives1;
	SDL_Rect tLives2;
	SDL_Rect tScore1;
	SDL_Rect tScore2;
	SDL_Rect tTime;

	SDL_Rect p1;
	SDL_Rect p2;

	SDL_Rect l1;
	int iL1;
	SDL_Rect l2;
	int iL2;

	SDL_Rect s11;
	int iS11;
	SDL_Rect s12;
	int iS12;
	SDL_Rect s13;
	int iS13;
	SDL_Rect s14;
	int iS14;

	SDL_Rect s21;
	int iS21;
	SDL_Rect s22;
	int iS22;
	SDL_Rect s23;
	int iS23;
	SDL_Rect s24;
	int iS24;

	SDL_Rect tMins;
	int iMins;
	SDL_Rect tColon;
	SDL_Rect tTens;
	int iTens;
	SDL_Rect tSecs;
	int iSecs;
};

