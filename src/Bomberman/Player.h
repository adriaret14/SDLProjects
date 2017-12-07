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
	Movimiento getLastMov();

	int getX();
	int getY();
	void setX(int);
	void setY(int);	

	void setCorrection( bool );

	Bomba * spawnBomba(int, int);
	void hit();

	void setVida(int);
	int getVida();
	void setScore(int);
	int getScore();
	void setPatines(bool);
	bool getPatines();
	void setCasco(bool);
	bool getCasco();

	bool bomb;
		
private:
	SDL_Rect pos;
	SDL_Rect rect;

	Movimiento mov;
	Movimiento lastMov;
	Movimiento corrDir;

	int playerNum;
	int vida;
	int score;
	int velocidad;
	bool correction;
	bool patines;
	bool casco;
	
	int dir;
	clock_t timerAnim;
	clock_t timerVida;
	clock_t timerPwrUp;

};

