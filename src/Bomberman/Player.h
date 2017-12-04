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
	void setCorrDir(Movimiento);
	int getX();
	int getY();
	void setCorrection( bool );
private:
	int playerNum;
	SDL_Rect pos;
	SDL_Rect rect;
	int vida;
	int score;
	Movimiento corrDir;
	Movimiento mov;
	bool correction;
	//Bomba b;
	int dir;

};

