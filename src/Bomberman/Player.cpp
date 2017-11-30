#include "Player.h"
#include "Renderer.h"


Player::Player(int n, int x, int y):
	playerNum(n),
	dir(1),
	mov(Movimiento::NONE)
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
	pos.w = rect.w = 48;
	pos.h = rect.h = 48;
}


Player::~Player()
{
}

void Player::update()
{
	if (rect.x == 0)
		dir = 1;
	if (rect.x == 96)
		dir = -1;
	bool moviendo;
	switch (mov)
	{
	case Movimiento::UP:
		pos.y -= 5;
		rect.y = 0;
		moviendo = true;
		break;
	case Movimiento::DOWN:
		pos.y += 5;
		rect.y = 96;
		moviendo = true;
		break;
	case Movimiento::LEFT:
		pos.x -= 5;
		rect.y = 48;
		moviendo = true;
		break;
	case Movimiento::RIGHT:
		pos.x += 5;
		rect.y = 144;
		moviendo = true;
		break;
	case Movimiento::NONE:
		moviendo = false;
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
	mov = m;
}
