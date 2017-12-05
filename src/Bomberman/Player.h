#include "Renderer.h"
#include "Bomba.h"
#pragma once
enum class Movimiento {UP, DOWN, LEFT, RIGHT, NONE};
class Player
{
public:
	Player(int, int, int, int);
	~Player();
	void update();
	void draw();
	void setMov( Movimiento );
	void setCorrDir(Movimiento);
	int getX();
	int getY();
	void setX(int);
	void setY(int);
	Movimiento getLastMov();
	void setCorrection( bool );
	Bomba * spawnBomba(int, int);
	bool bomb;
	void setVida(int);
	int getVida();
	void hit();
	void setScore(int);
	void setPatines(bool);
	bool getPatines();
	void setCasco(bool);
	bool getCasco();
private:
	int velocidad;
	bool patines;
	bool casco;
	int playerNum;
	SDL_Rect pos;
	SDL_Rect rect;
	int vida;
	int score;
	Movimiento corrDir;
	Movimiento mov;
	Movimiento lastMov;
	bool correction;
	int dir;
	clock_t timerVida;
	clock_t timerPwrUp;

};

