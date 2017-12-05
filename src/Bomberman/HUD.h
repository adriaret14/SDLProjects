#pragma once
#include "Renderer.h"
#include "Player.h"
class HUD
{
public:
	HUD();
	~HUD();

	void update();
	void draw();

private:
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
	SDL_Rect l2;

	SDL_Rect s11;
	SDL_Rect s12;
	SDL_Rect s13;
	SDL_Rect s14;

	SDL_Rect s21;
	SDL_Rect s22;
	SDL_Rect s23;
	SDL_Rect s24;

	SDL_Rect t1;
	SDL_Rect t2;
	SDL_Rect t3;
	SDL_Rect t4;
};

