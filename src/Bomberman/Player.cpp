#include "Player.h"
#include "Renderer.h"


Player::Player(int n, int x, int y, int vida):
	playerNum(n),
	dir(1),
	vida(vida),
	velocidad(VEL_1),
	timerVida(clock()),
	timerPwrUp(clock()),
	score(0),
	mov(Movimiento::NONE),
	correction(false),
	casco(false),
	patines(false)
{
	std::string ID;
	std::string path;
	switch (n)
	{
	case 1:
		ID = PLAYER_1;
		path = "player1.png";
		break;
	case 2:
		ID = PLAYER_2;
		path = "player2.png";
		break;
	}
	Renderer::Instance()->LoadTexture(ID, PATH_IMG + path);
	pos.x = x;
	pos.y = y;
	rect.x = 48;
	rect.y = 96;
	pos.w = rect.w = CELLW;
	pos.h = rect.h = CELLH;
}


Player::~Player()
{
}

void Player::update()
{
	if (clock() - timerPwrUp >= CLOCKS_PER_SEC * PWRUP_DURATION)
	{
		patines = false;
		casco = false;
	}
	
	if (rect.x == 0)
		dir = 1;
	if (rect.x == 96)
		dir = -1;
	bool moviendo;
	switch (mov)
	{
	case Movimiento::UP:
		pos.y -= velocidad;
		rect.y = 0;
		moviendo = true;
		break;
	case Movimiento::DOWN:
		pos.y += velocidad;
		rect.y = 96;
		moviendo = true;
		break;
	case Movimiento::LEFT:
		pos.x -= velocidad;
		rect.y = 48;
		moviendo = true;
		break;
	case Movimiento::RIGHT:
		pos.x += velocidad;
		rect.y = 144;
		moviendo = true;
		break;
	case Movimiento::NONE:
		if (correction)
		{
			switch (corrDir)
			{
			case Movimiento::UP:
				if ((pos.x - BORDER_LEFT) % CELLW <= TOL)
					pos.x -= 4;
				else if ((pos.x - BORDER_LEFT) % CELLW >= CELLW - TOL)
					pos.x += 4;
				rect.y = 0;
				moviendo = true;
				break;
			case Movimiento::DOWN:
				if ((pos.x - BORDER_LEFT) % CELLW <= TOL)
					pos.x -= 4;
				else if ((pos.x - BORDER_LEFT) % CELLW >= CELLW - TOL)
					pos.x += 4;
				pos.y += 4;
				rect.y = 96;
				moviendo = true;
				break;
			case Movimiento::LEFT:
				if ((pos.y - BORDER_TOP) % CELLH <= TOL)
					pos.y -= 4;
				else if ((pos.y - BORDER_TOP) % CELLH >= CELLH - TOL)
					pos.y += 4;
				rect.y = 48;
				moviendo = true;
				break;
			case Movimiento::RIGHT:
				if ((pos.y - BORDER_TOP) % CELLH <= TOL)
					pos.y -= 4;
				else if ((pos.y - BORDER_TOP) % CELLH >= CELLH - TOL)
					pos.y += 4;
				rect.y = 144;
				moviendo = true;
				break;
			case Movimiento::NONE:
				moviendo = false;
				break;
			}
		}
		else
		{
			moviendo = false;
		}
		break;
	}
	if (moviendo)
	{
		rect.x += dir * 48;
	}
	else
	{
		rect.x = 48;
	}

	if (patines)
	{
		velocidad = VEL_2;
	}
	else
	{
		velocidad = VEL_1;
	}
}

void Player::draw()
{
	switch (playerNum) {
	case 1:
		Renderer::Instance()->PushSprite(PLAYER_1, rect, pos);
		break;
	case 2:
		Renderer::Instance()->PushSprite(PLAYER_2, rect, pos);
		break;
	}
}

void Player::setMov( Movimiento m )
{
	if (m != Movimiento::NONE) lastMov = mov;
	mov = m;
}

void Player::setCorrDir(Movimiento m)
{
	corrDir = m;
}

int Player::getX()
{
	return pos.x;
}

int Player::getY()
{
	return pos.y;
}

void Player::setX(int i)
{
	pos.x = i;
}

void Player::setY(int j)
{
	pos.y = j;
}

Movimiento Player::getLastMov()
{
	return lastMov;
}

void Player::setCorrection(bool b)
{
	correction = b;
}

Bomba * Player::spawnBomba(int i, int j)
{
	bomb = true;
	return new Bomba(i, j);
}

void Player::setVida(int n)
{
	vida = vida + n;
}

int Player::getVida()
{
	std::cout << vida << std::endl;
	return vida;
}

void Player::hit()
{
	if (clock() - timerVida >= CLOCKS_PER_SEC)
	{
		if (!casco)
		{
			vida--;
		}
		timerVida = clock();
	}
}

void Player::setScore(int n)
{
	score += n;
}

int Player::getScore()
{
	return score;
}

void Player::setPatines(bool b)
{
	patines = b;
	if(b) timerPwrUp = clock();
}

bool Player::getPatines()
{
	return patines;
}

void Player::setCasco(bool b)
{
	casco = b;
	if (b) timerPwrUp = clock();
}

bool Player::getCasco()
{
	return casco;
}


