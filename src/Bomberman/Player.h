#include "Renderer.h"
#include "Bomba.h"
#pragma once
enum class Movimiento {UP, DOWN, LEFT, RIGHT, NONE};
class Player
{
public:
	Player(int, int, int);
	~Player();
	void update();
	void draw();
	void setMov( Movimiento );
	int getX();
	int getY();
private:
	int playerNum;
	SDL_Rect pos;
	SDL_Rect rect;
	int vida;
	int score;
	Movimiento mov;
	//Bomba b;
	int dir;

};

