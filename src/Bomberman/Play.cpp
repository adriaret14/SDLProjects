#include "Play.h"
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include <sstream>



Play::Play( int num ) :
	Escena::Escena(SCREEN_WIDTH, SCREEN_HEIGHT),
	p1(1, BORDER_LEFT + 2 * CELLW, BORDER_TOP + 2 * CELLH, 0),
	p2(2, BORDER_LEFT + 12 * CELLW, BORDER_TOP + 10 * CELLH, 0),
	hud(p1, p2),
	b1(2, 0),
	b2(2, 0),
	tiempo(clock())
{
	//Cargamos el background
	Renderer::Instance()->LoadTexture(BG, PATH_IMG + "bgGame.jpg");
	background = SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//Cargamos todas las texturas necesarias
	Renderer::Instance()->LoadTexture(ITEMS, PATH_IMG + "items.png");
	Renderer::Instance()->LoadTexture(EXPS, PATH_IMG + "explosion.png");

	//Determinamos el path del xml del mapa
	std::string mapPath;
	mapPath = "config.xml";
	
	rapidxml::xml_document<> doc;
	std::ifstream file(mapPath);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	rapidxml::xml_node<> *pRoot = doc.first_node();

	rapidxml::xml_node<> *Level = pRoot->first_node("Level");

	while (std::stoi(Level->first_attribute("id")->value(), nullptr) != num)
	{
		Level = Level->next_sibling();
	}
	rows = 13;
	cols = 15;

	//Posiciones de los jugadores
	if (num == 1)
	{
		p1.setX(BORDER_LEFT +  12 * CELLW);
		p1.setY(BORDER_TOP +  2 * CELLH);
		p2.setX(BORDER_LEFT +  12 * CELLW);
		p2.setY(BORDER_TOP +  10 * CELLH);
	}
	else if (num == 2)
	{
		p1.setX(BORDER_LEFT + 12 *CELLW);
		p1.setY(BORDER_TOP + 3 *CELLH);
		p2.setX(BORDER_LEFT + 12 *CELLW);
		p2.setY(BORDER_TOP + 10 *CELLH);
	}

	//Vidas de los jugadores
	p1.setVida(std::stoi(Level->first_attribute("lives")->value(), nullptr));
	p2.setVida(std::stoi(Level->first_attribute("lives")->value(), nullptr));

	maxTime = std::stoi(Level->first_attribute("time")->value(), nullptr);
	hud.setTime(maxTime);

	//Asignamos el espacio en memoria de la matriz del mapa
	mapa = new Objeto**[cols];
	for (int i = 0; i < cols; i++) {
		mapa[i] = new Objeto*[rows + 1];
		for (int j = 0; j < rows; j++)
		{
			mapa[i][j] = nullptr;
		}
	}

	//Creamos los bordes del mapa
	for (int j = 0; j < rows; j++)
	{
		mapa[0][j] = new NoDest(0, j);

		mapa[cols-1][j] = new NoDest(cols-1, j);
	}
	for (int i = 1; i < cols - 1; i++)
	{
		mapa[i][0] = new NoDest(i, 0);
		mapa[i][rows - 1] = new NoDest(i, rows - 1);
	}

	//Creamos los objetos del mapa
	rapidxml::xml_node<> *Destructible = Level->first_node("Destructible");
	for (rapidxml::xml_node<> *Obstacle = Destructible->first_node("Wall"); Obstacle; Obstacle = Obstacle->next_sibling())
	{
		int i = std::stoi(Obstacle->first_attribute("i")->value(), nullptr);
		int j = std::stoi(Obstacle->first_attribute("j")->value(), nullptr);

		mapa[i][j] = new Dest(i, j);
	}
	rapidxml::xml_node<> *Fixed = Level->first_node("Fixed");
	for (rapidxml::xml_node<> *Obstacle = Fixed->first_node("Wall"); Obstacle; Obstacle = Obstacle->next_sibling())
	{
		int i = std::stoi(Obstacle->first_attribute("i")->value(), nullptr);
		int j = std::stoi(Obstacle->first_attribute("j")->value(), nullptr);

		mapa[i][j] = new NoDest(i, j);
	}

	//Llenamos el unordered map de eventos
	eventos["w"] = false;
	eventos["a"] = false;
	eventos["s"] = false;
	eventos["d"] = false;
	eventos["space"] = false;

	eventos["up"] = false;
	eventos["left"] = false;
	eventos["down"] = false;
	eventos["right"] = false;
	eventos["rctrl"] = false;

	eventos["quit"] = false;
	eventos["esc"] = false;
	eventos["click"] = false;
}


Play::~Play()
{
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			delete mapa[i][j];
		}
		delete mapa[i];
	}
	delete mapa;
}

void Play::draw()
{
	Renderer::Instance()->Clear();
	Renderer::Instance()->PushImage(BG, background);
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			if (mapa[i][j] == nullptr) mapa[i][j] = new Objeto();
			mapa[i][j]->draw();
		}
	}
	p1.draw();
	p2.draw();
	for each (Explosion E in explosions)
	{
		E.draw();
	}
	hud.draw();
	Renderer::Instance()->Render();
}

void Play::update()
{
	hud.update();
	if (clock() - tiempo >= CLOCKS_PER_SEC * maxTime)
	{
		if (p1.getScore() > p2.getScore())
		{
			createRankingBin(p1.getScore());
		}
		else
		{
			createRankingBin(p2.getScore());
		}		
		Estado = estadoActual::GoToRank;
	}
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (mapa[i][j]->tipo == ObjTipo::PWRUP)
			{
				//Colision con jugador1

				if (abs(p1.getX() - (BORDER_LEFT + i*CELLW)) < CELLW && abs(p1.getY() - (BORDER_TOP + j*CELLH)) < CELLH)
				{
					switch (mapa[i][j]->pwrUp)
					{
					case PwrUpTipo::CASCO:
						p1.setCasco(true);
						p1.setPatines(false);
						break;
					case PwrUpTipo::PATINES:
						p1.setPatines(true);
						p1.setCasco(false);
						break;
					}
					mapa[i][j]->~Objeto();
					mapa[i][j] = new Objeto();
				}

				//Colision con jugador2
				if (abs(p2.getX() - (BORDER_LEFT + i*CELLW)) < CELLW && abs(p2.getY() - (BORDER_TOP + j*CELLH)) < CELLH)
				{
					switch (mapa[i][j]->pwrUp)
					{
					case PwrUpTipo::CASCO:
						p2.setCasco(true);
						p2.setPatines(false);
						break;
					case PwrUpTipo::PATINES:
						std::cout << "patines p1" << std::endl;
						p2.setPatines(true);
						p2.setCasco(false);
						break;
					}
					mapa[i][j]->~Objeto();
					mapa[i][j] = new Objeto();
				}
			}
		}
	}

	//Iteramos las explosiones
	for (std::vector<Explosion>::iterator it = explosions.begin(); it != explosions.end();)
	{
		//Colision con jugador1
		if (abs(p1.getX() - (it->pos.x)) < CELLW && abs(p1.getY() - (it->pos.y)) < CELLH)
		{
			int v = p1.getVida();
			p1.hit();
			if (p1.getVida() < v)
			{
				p2.setScore(KILL_POINTS);
			}
			if (p1.getVida() <= 0)
			{
				if (p1.getScore() > p2.getScore())
				{
					createRankingBin(p1.getScore());
				}
				else
				{
					createRankingBin(p2.getScore());
				}
				Estado = estadoActual::GoToRank;
			}
		}

		//Colision con jugador2
		if (abs(p2.getX() - (it->pos.x)) < CELLW && abs(p2.getY() - (it->pos.y)) < CELLH)
		{
			int v = p2.getVida();
			p2.hit();
			if (p2.getVida() < v)
			{
				p1.setScore(KILL_POINTS);
			}
			if (p2.getVida() <= 0)
			{
				if (p1.getScore() > p2.getScore())
				{
					createRankingBin(p1.getScore());
				}
				else
				{
					createRankingBin(p2.getScore());
				}
				Estado = estadoActual::GoToRank;
			}
		}

		it->update();
		if (it->boom)
		{
			it = explosions.erase(it);
		}
		else
		{
			it++;
		}
	}
	if (p1.bomb)
	{
		mapa[b1[0]][b1[1]]->update();
		if (mapa[b1[0]][b1[1]]->boom)
		{
			mapa[b1[0]][b1[1]]->~Objeto();
			mapa[b1[0]][b1[1]] = new Objeto();
			explosions.push_back(Explosion( b1[0], b1[1], Movimiento::NONE, false));
			std::vector<std::vector<int>> exps = generateExplosionVector(b1[0], b1[1]);
			for (int n = 1; n <= exps[0][0]; n++)
			{
				explosions.push_back(Explosion(b1[0], b1[1] - n, Movimiento::UP, (n == exps[0][0] && exps[1][0] == -1)));
			}
			for (int n = 1; n <= exps[0][1]; n++)
			{
				explosions.push_back(Explosion(b1[0], b1[1] + n, Movimiento::DOWN, (n == exps[0][1] && exps[1][1] == -1)));
			}
			for (int n = 1; n <= exps[0][2]; n++)
			{
				explosions.push_back(Explosion(b1[0] - n, b1[1], Movimiento::LEFT, (n == exps[0][2] && exps[1][2] == -1)));
			}
			for (int n = 1; n <= exps[0][3]; n++)
			{
				explosions.push_back(Explosion(b1[0] + n, b1[1], Movimiento::RIGHT, (n == exps[0][3] && exps[1][3] == -1)));
			}
			std::cout << exps[1][0] << " " << exps[1][1] << " " << exps[1][2] << " " << exps[1][3] << std::endl;
			if (exps[1][0] != -1)
			{
				if (mapa[b1[0]][b1[1] - exps[1][0]]->hit())
				{
					p1.setScore(DESTRUCTION_POINTS);
					PwrUpTipo t = mapa[b1[0]][b1[1] - exps[1][0]]->powerup();
					mapa[b1[0]][b1[1] - exps[1][0]]->~Objeto();
					if (t == PwrUpTipo::NONE)
					{
						mapa[b1[0]][b1[1] - exps[1][0]] = new Objeto();
					}
					else
					{
						mapa[b1[0]][b1[1] - exps[1][0]] = new PowerUp(b1[0], b1[1] - exps[1][0], t);
					}
				}
			}
			if (exps[1][1] != -1)
			{
				if (mapa[b1[0]][b1[1] + exps[1][1]]->hit())
				{
					p1.setScore(DESTRUCTION_POINTS);
					PwrUpTipo t = mapa[b1[0]][b1[1] + exps[1][1]]->powerup();
					mapa[b1[0]][b1[1] + exps[1][1]]->~Objeto();
					if (t == PwrUpTipo::NONE)
					{
						mapa[b1[0]][b1[1] + exps[1][1]] = new Objeto();
					}
					else
					{
						mapa[b1[0]][b1[1] + exps[1][1]] = new PowerUp(b1[0], b1[1] + exps[1][1], t);
					}
				}
			}
			if (exps[1][2] != -1)
			{
				if (mapa[b1[0] - exps[1][2]][b1[1]]->hit())
				{
					p1.setScore(DESTRUCTION_POINTS);
					PwrUpTipo t = mapa[b1[0] - exps[1][2]][b1[1]]->powerup();
					mapa[b1[0] - exps[1][2]][b1[1]]->~Objeto();
					if (t == PwrUpTipo::NONE)
					{
						mapa[b1[0] - exps[1][2]][b1[1]] = new Objeto();
					}
					else
					{
						mapa[b1[0] - exps[1][2]][b1[1]] = new PowerUp(b1[0] - exps[1][2], b1[1], t);
					}
				}
			}
			if (exps[1][3] != -1)
			{
				if (mapa[b1[0] + exps[1][3]][b1[1]]->hit())
				{
					p1.setScore(DESTRUCTION_POINTS);
					PwrUpTipo t = mapa[b1[0]][b1[1] + exps[1][1]]->powerup();
					mapa[b1[0] + exps[1][3]][b1[1]]->~Objeto();
					if (t == PwrUpTipo::NONE)
					{
						mapa[b1[0] + exps[1][3]][b1[1]] = new Objeto();
					}
					else
					{
						mapa[b1[0] + exps[1][3]][b1[1]] = new PowerUp(b1[0] + exps[1][3], b1[1], t);
					}
				}
			}
			p1.bomb = false;
		}
	}
	if (p2.bomb)
	{
		mapa[b2[0]][b2[1]]->update();
		if (mapa[b2[0]][b2[1]]->boom)
		{
			mapa[b2[0]][b2[1]]->~Objeto();
			mapa[b2[0]][b2[1]] = new Objeto();
			explosions.push_back(Explosion(b2[0], b2[1], Movimiento::NONE, false));
			std::vector<std::vector<int>> exps = generateExplosionVector(b2[0], b2[1]);
			for (int n = 1; n <= exps[0][0]; n++)
			{
				explosions.push_back(Explosion(b2[0], b2[1] - n, Movimiento::UP, (n == exps[0][0] && exps[1][0] == -1)));
			}
			for (int n = 1; n <= exps[0][1]; n++)
			{
				explosions.push_back(Explosion(b2[0], b2[1] + n, Movimiento::DOWN, (n == exps[0][1] && exps[1][1] == -1)));
			}
			for (int n = 1; n <= exps[0][2]; n++)
			{
				explosions.push_back(Explosion(b2[0] - n, b2[1], Movimiento::LEFT, (n == exps[0][2] && exps[1][2] == -1)));
			}
			for (int n = 1; n <= exps[0][3]; n++)
			{
				explosions.push_back(Explosion(b2[0] + n, b2[1], Movimiento::RIGHT, (n == exps[0][3] && exps[1][3] == -1)));
			}
			std::cout << exps[1][0] << " " << exps[1][1] << " " << exps[1][2] << " " << exps[1][3] << std::endl;
			if (exps[1][0] != -1)
			{
				if (mapa[b2[0]][b2[1] - exps[1][0]]->hit())
				{
					p2.setScore(DESTRUCTION_POINTS);
					PwrUpTipo t = mapa[b2[0]][b2[1] - exps[1][0]]->powerup();
					mapa[b2[0]][b2[1] - exps[1][0]]->~Objeto();
					if (t == PwrUpTipo::NONE)
					{
						mapa[b2[0]][b2[1] - exps[1][0]] = new Objeto();
					}
					else
					{
						mapa[b2[0]][b2[1] - exps[1][0]] = new PowerUp(b2[0], b2[1] - exps[1][0], t);
					}
				}
			}
			if (exps[1][1] != -1)
			{
				if (mapa[b2[0]][b2[1] + exps[1][1]]->hit())
				{
					p2.setScore(DESTRUCTION_POINTS);
					PwrUpTipo t = mapa[b2[0]][b2[1] + exps[1][1]]->powerup();
					mapa[b2[0]][b2[1] + exps[1][1]]->~Objeto();
					if (t == PwrUpTipo::NONE)
					{
						mapa[b2[0]][b2[1] + exps[1][1]] = new Objeto();
					}
					else
					{
						mapa[b2[0]][b2[1] + exps[1][1]] = new PowerUp(b2[0], b2[1] + exps[1][1], t);
					}
				}
			}
			if (exps[1][2] != -1)
			{
				if (mapa[b2[0] - exps[1][2]][b2[1]]->hit())
				{
					p2.setScore(DESTRUCTION_POINTS);
					PwrUpTipo t = mapa[b2[0] - exps[1][2]][b2[1]]->powerup();
					mapa[b2[0] - exps[1][2]][b2[1]]->~Objeto();
					if (t == PwrUpTipo::NONE)
					{
						mapa[b2[0] - exps[1][2]][b2[1]] = new Objeto();
					}
					else
					{
						mapa[b2[0] - exps[1][2]][b2[1]] = new PowerUp(b2[0] - exps[1][2], b2[1], t);
					}
				}
			}
			if (exps[1][3] != -1)
			{
				if (mapa[b2[0] + exps[1][3]][b2[1]]->hit())
				{
					p2.setScore(DESTRUCTION_POINTS);
					PwrUpTipo t = mapa[b2[0]][b2[1] + exps[1][1]]->powerup();
					mapa[b2[0] + exps[1][3]][b2[1]]->~Objeto();
					if (t == PwrUpTipo::NONE)
					{
						mapa[b2[0] + exps[1][3]][b2[1]] = new Objeto();
					}
					else
					{
						mapa[b2[0] + exps[1][3]][b2[1]] = new PowerUp(b2[0] + exps[1][3], b2[1], t);
					}
				}
			}
			p2.bomb = false;
		}
	}
	if (eventos["esc"])
	{
		Estado = estadoActual::Exit;
		std::cout << "Pulso" << std::endl;
	}
	if (eventos["w"])
	{
		MovCheck c = playerMovementCheck(Movimiento::UP, p1);
		switch (c)
		{
		case MovCheck::GREEN:
			p1.setCorrection(false);
			p1.setMov(Movimiento::UP);
			break;
		case MovCheck::RED:
			p1.setCorrection(false);
			p1.setMov(Movimiento::NONE);
			break;
		case MovCheck::CORRECTION:
			p1.setCorrection(true);
			p1.setMov(Movimiento::NONE);
			p1.setCorrDir(Movimiento::UP);
			break;
		}
	}
	else if (eventos["s"])
	{
		MovCheck c = playerMovementCheck(Movimiento::DOWN, p1);
		switch (c)
		{
		case MovCheck::GREEN:
			p1.setCorrection(false);
			p1.setMov(Movimiento::DOWN);
			break;
		case MovCheck::RED:
			p1.setCorrection(false);
			p1.setMov(Movimiento::NONE);
			break;
		case MovCheck::CORRECTION:
			p1.setCorrection(true);
			p1.setMov(Movimiento::NONE);
			p1.setCorrDir(Movimiento::DOWN);
			break;
		}
	}
	else if (eventos["a"])
	{
		MovCheck c = playerMovementCheck(Movimiento::LEFT, p1);
		switch (c)
		{
		case MovCheck::GREEN:
			p1.setCorrection(false);
			p1.setMov(Movimiento::LEFT);
			break;
		case MovCheck::RED:
			p1.setCorrection(false);
			p1.setMov(Movimiento::NONE);
			break;
		case MovCheck::CORRECTION:
			p1.setCorrection(true);
			p1.setMov(Movimiento::NONE);
			p1.setCorrDir(Movimiento::LEFT);
			break;
		}
	}
	else if (eventos["d"])
	{
		MovCheck c = playerMovementCheck(Movimiento::RIGHT, p1);
		switch (c)
		{
		case MovCheck::GREEN:
			p1.setCorrection(false);
			p1.setMov(Movimiento::RIGHT);
			break;
		case MovCheck::RED:
			p1.setCorrection(false);
			p1.setMov(Movimiento::NONE);
			break;
		case MovCheck::CORRECTION:
			p1.setCorrection(true);
			p1.setMov(Movimiento::NONE);
			p1.setCorrDir(Movimiento::RIGHT);
			break;
		}
	}
	else
	{
		p1.setCorrection(false);
		p1.setMov(Movimiento::NONE);
	}
	if (eventos["up"])
	{
		MovCheck c = playerMovementCheck(Movimiento::UP, p2);
		switch (c)
		{
		case MovCheck::GREEN:
			p2.setCorrection(false);
			p2.setMov(Movimiento::UP);
			break;
		case MovCheck::RED:
			p2.setCorrection(false);
			p2.setMov(Movimiento::NONE);
			break;
		case MovCheck::CORRECTION:
			p2.setCorrection(true);
			p2.setMov(Movimiento::NONE);
			p2.setCorrDir(Movimiento::UP);
			break;
		}
	}
	else if (eventos["down"])
	{
		MovCheck c = playerMovementCheck(Movimiento::DOWN, p2);
		switch (c)
		{
		case MovCheck::GREEN:
			p2.setCorrection(false);
			p2.setMov(Movimiento::DOWN);
			break;
		case MovCheck::RED:
			p2.setCorrection(false);
			p2.setMov(Movimiento::NONE);
			break;
		case MovCheck::CORRECTION:
			p2.setCorrection(true);
			p2.setMov(Movimiento::NONE);
			p2.setCorrDir(Movimiento::DOWN);
			break;
		}
	}
	else if (eventos["left"])
	{
		MovCheck c = playerMovementCheck(Movimiento::LEFT, p2);
		switch (c)
		{
		case MovCheck::GREEN:
			p2.setCorrection(false);
			p2.setMov(Movimiento::LEFT);
			break;
		case MovCheck::RED:
			p2.setCorrection(false);
			p2.setMov(Movimiento::NONE);
			break;
		case MovCheck::CORRECTION:
			p2.setCorrection(true);
			p2.setMov(Movimiento::NONE);
			p2.setCorrDir(Movimiento::LEFT);
			break;
		}
	}
	else if (eventos["right"])
	{
		MovCheck c = playerMovementCheck(Movimiento::RIGHT, p2);
		switch (c)
		{
		case MovCheck::GREEN:
			p2.setCorrection(false);
			p2.setMov(Movimiento::RIGHT);
			break;
		case MovCheck::RED:
			p2.setCorrection(false);
			p2.setMov(Movimiento::NONE);
			break;
		case MovCheck::CORRECTION:
			p2.setCorrection(true);
			p2.setMov(Movimiento::NONE);
			p2.setCorrDir(Movimiento::RIGHT);
			break;
		}
	}	
	else
	{
		p2.setCorrection(false);
		p2.setMov(Movimiento::NONE);
	}
	if (eventos["space"])
	{
		if (!p1.bomb)
		{
			if (bombPlacementCheck(p1.getLastMov(), p1) == MovCheck::GREEN)
			{
				std::cout << "GREEN" << std::endl;
				int i, j;
				switch (p1.getLastMov())
				{
				case Movimiento::UP:
					if ((p1.getX() - BORDER_LEFT) % CELLW >= CELLW - TOL)
					{
						i = (p1.getX() - BORDER_LEFT - (p1.getX() - BORDER_LEFT) % CELLW) / CELLW + 1;
					}
					else
					{
						i = (p1.getX() - BORDER_LEFT - (p1.getX() - BORDER_LEFT) % CELLW) / CELLW;
					}
					j = (p1.getY() - BORDER_TOP - (p1.getY() - BORDER_TOP) % CELLH) / CELLH - 1;
					break;
				case Movimiento::DOWN:
					if ((p1.getX() - BORDER_LEFT) % CELLW >= CELLW - TOL)
					{
						i = (p1.getX() - BORDER_LEFT - (p1.getX() - BORDER_LEFT) % CELLW) / CELLW + 1;
					}
					else
					{
						i = (p1.getX() - BORDER_LEFT - (p1.getX() - BORDER_LEFT) % CELLW) / CELLW;
					}
					if ((p1.getY() - BORDER_TOP) % CELLH == 0)
					{
						j = (p1.getY() - BORDER_TOP - (p1.getY() - BORDER_TOP) % CELLH) / CELLH + 1;
					}
					else
					{
						j = (p1.getY() - BORDER_TOP - (p1.getY() - BORDER_TOP) % CELLH) / CELLH + 2;
					}
					break;
				case Movimiento::LEFT:
					i = (p1.getX() - BORDER_LEFT - (p1.getX() - BORDER_LEFT) % CELLW) / CELLW - 1;
					if ((p1.getY() - BORDER_TOP) % CELLH >= CELLH - TOL)
					{
						j = (p1.getY() - BORDER_TOP - (p1.getY() - BORDER_TOP) % CELLH) / CELLH + 1;
					}
					else
					{
						j = (p1.getY() - BORDER_TOP - (p1.getY() - BORDER_TOP) % CELLH) / CELLH;
					}
					break;
				case Movimiento::RIGHT:
					if ((p1.getX() - BORDER_LEFT) % CELLW == 0)
					{
						i = (p1.getX() - BORDER_LEFT - (p1.getX() - BORDER_LEFT) % CELLW) / CELLW + 1;
					}
					else
					{
						i = (p1.getX() - BORDER_LEFT - (p1.getX() - BORDER_LEFT) % CELLW) / CELLW + 2;
					}
					if ((p1.getY() - BORDER_TOP) % CELLH >= CELLH - TOL)
					{
						j = (p1.getY() - BORDER_TOP - (p1.getY() - BORDER_TOP) % CELLH) / CELLH + 1;
					}
					else
					{
						j = (p1.getY() - BORDER_TOP - (p1.getY() - BORDER_TOP) % CELLH) / CELLH;
					}
					break;
				}
				mapa[i][j]->~Objeto();
				mapa[i][j] = p1.spawnBomba(i, j);
				b1[0] = i; b1[1] = j;
			}
		}
	}
	if (eventos["rctrl"])
	{
		if (!p2.bomb)
		{
			if (bombPlacementCheck(p2.getLastMov(), p2) == MovCheck::GREEN)
			{
				std::cout << "GREEN" << std::endl;
				int i, j;
				switch (p2.getLastMov())
				{
				case Movimiento::UP:
					if ((p2.getX() - BORDER_LEFT) % CELLW >= CELLW - TOL)
					{
						i = (p2.getX() - BORDER_LEFT - (p2.getX() - BORDER_LEFT) % CELLW) / CELLW + 1;
					}
					else
					{
						i = (p2.getX() - BORDER_LEFT - (p2.getX() - BORDER_LEFT) % CELLW) / CELLW;
					}
					j = (p2.getY() - BORDER_TOP - (p2.getY() - BORDER_TOP) % CELLH) / CELLH - 1;
					break;
				case Movimiento::DOWN:
					if ((p2.getX() - BORDER_LEFT) % CELLW >= CELLW - TOL)
					{
						i = (p2.getX() - BORDER_LEFT - (p2.getX() - BORDER_LEFT) % CELLW) / CELLW + 1;
					}
					else
					{
						i = (p2.getX() - BORDER_LEFT - (p2.getX() - BORDER_LEFT) % CELLW) / CELLW;
					}
					if ((p2.getY() - BORDER_TOP) % CELLH == 0)
					{
						j = (p2.getY() - BORDER_TOP - (p2.getY() - BORDER_TOP) % CELLH) / CELLH + 1;
					}
					else
					{
						j = (p2.getY() - BORDER_TOP - (p2.getY() - BORDER_TOP) % CELLH) / CELLH + 2;
					}
					break;
				case Movimiento::LEFT:
					i = (p2.getX() - BORDER_LEFT - (p2.getX() - BORDER_LEFT) % CELLW) / CELLW - 1;
					if ((p2.getY() - BORDER_TOP) % CELLH >= CELLH - TOL)
					{
						j = (p2.getY() - BORDER_TOP - (p2.getY() - BORDER_TOP) % CELLH) / CELLH + 1;
					}
					else
					{
						j = (p2.getY() - BORDER_TOP - (p2.getY() - BORDER_TOP) % CELLH) / CELLH;
					}
					break;
				case Movimiento::RIGHT:
					if ((p2.getX() - BORDER_LEFT) % CELLW == 0)
					{
						i = (p2.getX() - BORDER_LEFT - (p2.getX() - BORDER_LEFT) % CELLW) / CELLW + 1;
					}
					else
					{
						i = (p2.getX() - BORDER_LEFT - (p2.getX() - BORDER_LEFT) % CELLW) / CELLW + 2;
					}
					if ((p2.getY() - BORDER_TOP) % CELLH >= CELLH - TOL)
					{
						j = (p2.getY() - BORDER_TOP - (p2.getY() - BORDER_TOP) % CELLH) / CELLH + 1;
					}
					else
					{
						j = (p2.getY() - BORDER_TOP - (p2.getY() - BORDER_TOP) % CELLH) / CELLH;
					}
					break;
				}
				mapa[i][j]->~Objeto();
				mapa[i][j] = p2.spawnBomba(i, j);
				b2[0] = i; b2[1] = j;
			}
		}
	}

	/*
	std::string s = 
		"w: " + std::to_string(eventos["w"]) + " / "
		+ "s: " + std::to_string(eventos["s"]) + " / "
		+ "a: " + std::to_string(eventos["a"]) + " / "
		+ "d: " + std::to_string(eventos["d"]) + " / "
		+ "up: " + std::to_string(eventos["up"]) + " / "
	+ "down: " + std::to_string(eventos["down"]) + " / "
	+ "left: " + std::to_string(eventos["left"]) + " / "
	+ "right: " + std::to_string(eventos["right"]) + " /// "
	+ "esc: " + std::to_string(eventos["esc"]) + " / "
	+ "click: " + std::to_string(eventos["click"]);

	if (estado != s)
	{
		estado = s;
		std::cout << estado << std::endl;
	}
	*/

	p1.update();
	p2.update();
}

void Play::eHandler()
{
	SDL_Event event;
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	
	//Controles jugador 1
	eventos["w"] = state[SDL_SCANCODE_W];
	eventos["s"] = state[SDL_SCANCODE_S];
	eventos["a"] = state[SDL_SCANCODE_A];
	eventos["d"] = state[SDL_SCANCODE_D];
	eventos["space"] = state[SDL_SCANCODE_SPACE];

	//Controles jugador 2
	eventos["up"] = state[SDL_SCANCODE_UP];
	eventos["down"] = state[SDL_SCANCODE_DOWN];
	eventos["left"] = state[SDL_SCANCODE_LEFT];
	eventos["right"] = state[SDL_SCANCODE_RIGHT];
	eventos["rctrl"] = state[SDL_SCANCODE_RCTRL];

	//Misc
	eventos["esc"] = state[SDL_SCANCODE_ESCAPE];
	
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				eventos["quit"] = true;
				break;
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP:
				break;
			case SDL_MOUSEBUTTONDOWN:
				eventos["click"] = true;
				break;
			case SDL_MOUSEBUTTONUP:
				eventos["click"] = false;
			default:
				break;
			}
		}
}

MovCheck Play::playerMovementCheck(Movimiento m, Player p)
{
	switch (m)
	{
	case Movimiento::UP:
		if ((p.getY() - BORDER_TOP) % CELLH != 0)
		{
			return MovCheck::GREEN;
		}
		else
		{
			if ((p.getX() - BORDER_LEFT) % CELLW == 0)
			{
				if (!getAdjCell(p.getX(), p.getY(), 0, -1)->collision)
					return MovCheck::GREEN;
				else
					return MovCheck::RED;
			}
			else
			{
				bool c1 = getAdjCell(p.getX(), p.getY(), 0, -1)->collision;
				bool c2 = getAdjCell(p.getX(), p.getY(), 1, -1)->collision;
				if (c1 && c2)
				{
					return MovCheck::RED;
				}
				else if (!c1 && !c2)
				{
					return MovCheck::GREEN;
				}
				else if (!c1 && c2)
				{
					if ((p.getX() - BORDER_LEFT) % CELLW <= TOL)
					{
						return MovCheck::CORRECTION;
					}
					else
						return MovCheck::RED;
				}
				else if (c1 && !c2)
				{
					if ((p.getX() - BORDER_LEFT) % CELLW >= CELLW - TOL)
					{
						return MovCheck::CORRECTION;
					}
					else
						return MovCheck::RED;
				}
			}
		}
		break;
	case Movimiento::DOWN:
		if ((p.getY() - BORDER_TOP) % CELLH != 0)
		{
			return MovCheck::GREEN;
		}
		else
		{
			if ((p.getX() - BORDER_LEFT) % CELLW == 0)
			{
				if (!getAdjCell(p.getX(), p.getY(), 0, 1)->collision)
					return MovCheck::GREEN;
				else
					return MovCheck::RED;
			}
			else
			{
				bool c1 = getAdjCell(p.getX(), p.getY(), 0, 1)->collision;
				bool c2 = getAdjCell(p.getX(), p.getY(), 1, 1)->collision;
				if (c1 && c2)
				{
					return MovCheck::RED;
				}
				else if (!c1 && !c2)
				{
					return MovCheck::GREEN;
				}
				else if (!c1 && c2)
				{
					if ((p.getX() - BORDER_LEFT) % CELLW <= TOL)
					{
						return MovCheck::CORRECTION;
					}
					else
						return MovCheck::RED;
				}
				else if (c1 && !c2)
				{
					if ((p.getX() - BORDER_LEFT) % CELLW >= CELLW - TOL)
					{
						return MovCheck::CORRECTION;
					}
					else
						return MovCheck::RED;
				}
			}
		}
		break;
	case Movimiento::LEFT:
		if ((p.getX() - BORDER_LEFT) % CELLW != 0)
		{
			return MovCheck::GREEN;
		}
		else
		{
			if ((p.getY() - BORDER_TOP) % CELLH == 0)
			{
				if (!getAdjCell(p.getX(), p.getY(), -1, 0)->collision)
					return MovCheck::GREEN;
				else
					return MovCheck::RED;
			}
			else
			{
				bool c1 = getAdjCell(p.getX(), p.getY(), -1, 0)->collision;
				bool c2 = getAdjCell(p.getX(), p.getY(), -1, 1)->collision;
				if (c1 && c2)
				{
					return MovCheck::RED;
				}
				else if (!c1 && !c2)
				{
					return MovCheck::GREEN;
				}
				else if (!c1 && c2)
				{
					if ((p.getY() - BORDER_TOP) % CELLH <= TOL)
					{
						return MovCheck::CORRECTION;
					}
					else
						return MovCheck::RED;
				}
				else if (c1 && !c2)
				{
					if ((p.getY() - BORDER_TOP) % CELLH >= CELLH - TOL)
					{
						return MovCheck::CORRECTION;
					}
					else
						return MovCheck::RED;
				}
			}
		}
		break;
	case Movimiento::RIGHT:
		if ((p.getX() - BORDER_LEFT) % CELLW != 0)
		{
			return MovCheck::GREEN;
		}
		else
		{
			if ((p.getY() - BORDER_TOP) % CELLH == 0)
			{
				if (!getAdjCell(p.getX(), p.getY(), 1, 0)->collision)
					return MovCheck::GREEN;
				else
					return MovCheck::RED;
			}
			else
			{
				bool c1 = getAdjCell(p.getX(), p.getY(), 1, 0)->collision;
				bool c2 = getAdjCell(p.getX(), p.getY(), 1, 1)->collision;
				if (c1 && c2)
				{
					return MovCheck::RED;
				}
				else if (!c1 && !c2)
				{
					return MovCheck::GREEN;
				}
				else if (!c1 && c2)
				{
					if ((p.getY() - BORDER_TOP) % CELLH <= TOL)
					{
						return MovCheck::CORRECTION;
					}
					else
						return MovCheck::RED;
				}
				else if (c1 && !c2)
				{
					if ((p.getY() - BORDER_TOP) % CELLH >= CELLH - TOL)
					{
						return MovCheck::CORRECTION;
					}
					else
						return MovCheck::RED;
				}
			}
		}
		break;
	case Movimiento::NONE:
		return MovCheck::RED;
		break;
	}
}

MovCheck Play::bombPlacementCheck(Movimiento m, Player p)
{

	switch (m)
	{
	case Movimiento::UP:
		if ((p.getX() - BORDER_LEFT) % CELLW == 0)
		{
			if (getAdjCell(p.getX(), p.getY(), 0, -1)->collision)
			{
				return MovCheck::RED;
			}
			else
			{
				return MovCheck::GREEN;
			}
		}
		else
		{
			bool c1 = getAdjCell(p.getX(), p.getY(), 0, -1)->collision;
			bool c2 = getAdjCell(p.getX(), p.getY(), 1, -1)->collision;
			if (c1 && c2)
			{
				return MovCheck::RED;
			}
			else if (!c1 && !c2)
			{
				return MovCheck::GREEN;
			}
			else if (!c1 && c2)
			{
				if ((p.getX() - BORDER_LEFT) % CELLW <= TOL)
				{
					return MovCheck::GREEN;
				}
				else
					return MovCheck::RED;
			}
			else if (c1 && !c2)
			{
				if ((p.getX() - BORDER_LEFT) % CELLW >= CELLW - TOL)
				{
					return MovCheck::GREEN;
				}
				else
					return MovCheck::RED;
			}
		}
		break;
	case Movimiento::DOWN:
		if ((p.getX() - BORDER_LEFT) % CELLW == 0)
		{
			if ((p.getY() - BORDER_TOP) % CELLH == 0)
			{
				if (getAdjCell(p.getX(), p.getY(), 0, 1)->collision)
				{
					return MovCheck::RED;
				}
				else
				{
					return MovCheck::GREEN;
				}
			}
			else
			{
				if (getAdjCell(p.getX(), p.getY(), 0, 2)->collision)
				{
					return MovCheck::RED;
				}
				else
				{
					return MovCheck::GREEN;
				}
			}
		}
		else
		{
			bool c1 = getAdjCell(p.getX(), p.getY(), 0, 1)->collision;
			bool c2 = getAdjCell(p.getX(), p.getY(), 1, 1)->collision;
			if (c1 && c2)
			{
				return MovCheck::RED;
			}
			else if (!c1 && !c2)
			{
				return MovCheck::GREEN;
			}
			else if (!c1 && c2)
			{
				if ((p.getX() - BORDER_LEFT) % CELLW <= TOL)
				{
					return MovCheck::GREEN;
				}
				else
					return MovCheck::RED;
			}
			else if (c1 && !c2)
			{
				if ((p.getX() - BORDER_LEFT) % CELLW >= CELLW - TOL)
				{
					return MovCheck::GREEN;
				}
				else
					return MovCheck::RED;
			}
		}
		break;
	case Movimiento::LEFT:
		if ((p.getY() - BORDER_TOP) % CELLH == 0)
		{
			if (!getAdjCell(p.getX(), p.getY(), -1, 0)->collision)
				return MovCheck::GREEN;
			else
				return MovCheck::RED;
		}
		else
		{
			bool c1 = getAdjCell(p.getX(), p.getY(), -1, 0)->collision;
			bool c2 = getAdjCell(p.getX(), p.getY(), -1, 1)->collision;
			if (c1 && c2)
			{
				return MovCheck::RED;
			}
			else if (!c1 && !c2)
			{
				return MovCheck::GREEN;
			}
			else if (!c1 && c2)
			{
				if ((p.getY() - BORDER_TOP) % CELLH <= TOL)
				{
					return MovCheck::GREEN;
				}
				else
					return MovCheck::RED;
			}
			else if (c1 && !c2)
			{
				if ((p.getY() - BORDER_TOP) % CELLH >= CELLH - TOL)
				{
					return MovCheck::GREEN;
				}
				else
					return MovCheck::RED;
			}
		}
		break;
	case Movimiento::RIGHT:
		if ((p.getY() - BORDER_TOP) % CELLH == 0)
		{
			if ((p.getX() - BORDER_LEFT) % CELLW == 0)
			{
				if (!getAdjCell(p.getX(), p.getY(), 1, 0)->collision)
					return MovCheck::GREEN;
				else
					return MovCheck::RED;
			}
			else
			{
				if (!getAdjCell(p.getX(), p.getY(), 2, 0)->collision)
					return MovCheck::GREEN;
				else
					return MovCheck::RED;
			}
			
		}
		else
		{
			bool c1 = getAdjCell(p.getX(), p.getY(), 1, 0)->collision;
			bool c2 = getAdjCell(p.getX(), p.getY(), 1, 1)->collision;
			if (c1 && c2)
			{
				return MovCheck::RED;
			}
			else if (!c1 && !c2)
			{
				return MovCheck::GREEN;
			}
			else if (!c1 && c2)
			{
				if ((p.getY() - BORDER_TOP) % CELLH <= TOL)
				{
					return MovCheck::GREEN;
				}
				else
					return MovCheck::RED;
			}
			else if (c1 && !c2)
			{
				if ((p.getY() - BORDER_TOP) % CELLH >= CELLH - TOL)
				{
					return MovCheck::GREEN;
				}
				else
					return MovCheck::RED;
			}
		}
		break;
	case Movimiento::NONE:
		return MovCheck::RED;
		break;
	}
}

std::vector<std::vector<int>> Play::generateExplosionVector(int i, int j)
{
	bool pwrup = false;
	std::vector<std::vector<int>> exps;
	exps.push_back(std::vector<int>(4, 0));
	exps.push_back(std::vector<int>(4, -1));
	//UP
	if (!mapa[i][j - 1]->collision)
	{
		exps[0][0]++;
		if (!mapa[i][j - 2]->collision)
		{
			exps[0][0]++;
			if (pwrup && !mapa[i][j - 3]->collision)
			{
				exps[0][0]++;
				if (!mapa[i][j - 4]->collision)
				{
					exps[0][0]++;
				}
				else if (mapa[i][j - 4]->tipo == ObjTipo::DEST)
				{
					exps[1][0] = 4;
				}
			}
			else if (pwrup && mapa[i][j - 3]->tipo == ObjTipo::DEST)
			{
				exps[1][0] = 3;
			}
		}
		else if (mapa[i][j - 2]->tipo == ObjTipo::DEST)
		{
			exps[1][0] = 2;
		}
	}
	else if (mapa[i][j - 1]->tipo == ObjTipo::DEST)
	{
		exps[1][0] = 1;
	}
	//DOWN
	if (!mapa[i][j + 1]->collision)
	{
		exps[0][1]++;
		if (!mapa[i][j + 2]->collision)
		{
			exps[0][1]++;
			if (pwrup && !mapa[i][j + 3]->collision)
			{
				exps[0][1]++;
				if (!mapa[i][j + 4]->collision)
				{
					exps[0][1]++;
				}
				else if (mapa[i][j + 4]->tipo == ObjTipo::DEST)
				{
					exps[1][1] = 4;
				}
			}
			else if (pwrup && mapa[i][j + 3]->tipo == ObjTipo::DEST)
			{
				exps[1][1] = 3;
			}
		}
		else if (mapa[i][j + 2]->tipo == ObjTipo::DEST)
		{
			exps[1][1] = 2;
		}
	}
	else if (mapa[i][j + 1]->tipo == ObjTipo::DEST)
	{
		exps[1][1] = 1;
	}
	//LEFT
	if (!mapa[i - 1][j]->collision)
	{
		exps[0][2]++;
		if (!mapa[i - 2][j]->collision)
		{
			exps[0][2]++;
			if (pwrup && !mapa[i - 3][j]->collision)
			{
				exps[0][2]++;
				if (!mapa[i - 4][j]->collision)
				{
					exps[0][2]++;
				}
				else if (mapa[i - 4][j]->tipo == ObjTipo::DEST)
				{
					exps[1][2] = 4;
				}
			}
			else if (mapa[i - 3][j]->tipo == ObjTipo::DEST)
			{
				exps[1][2] = 3;
			}
		}
		else if (mapa[i - 2][j]->tipo == ObjTipo::DEST)
		{
			exps[1][2] = 2;
		}
	}
	else if (mapa[i - 1][j]->tipo == ObjTipo::DEST)
	{
		exps[1][2] = 1;
	}
	//RIGHT
	if (!mapa[i + 1][j]->collision)
	{
		exps[0][3]++;
		if (!mapa[i + 2][j]->collision)
		{
			exps[0][3]++;
			if (pwrup && !mapa[i + 3][j]->collision)
			{
				exps[0][3]++;
				if (!mapa[i + 4][j]->collision)
				{
					exps[0][3]++;
				}
				else if (mapa[i + 4][j]->tipo == ObjTipo::DEST)
				{
					exps[1][3] = 4;
				}
			}
			else if (mapa[i + 3][j]->tipo == ObjTipo::DEST)
			{
				exps[1][3] = 3;
			}
		}
		else if (mapa[i + 2][j]->tipo == ObjTipo::DEST)
		{
			exps[1][3] = 2;
		}
	}
	else if (mapa[i + 1][j]->tipo == ObjTipo::DEST)
	{
		exps[1][3] = 1;
	}
	return exps;
}

Objeto * Play::getAdjCell(int x, int y, int i, int j)
{
	return mapa[(x - BORDER_LEFT - (x - BORDER_LEFT) % CELLW) / CELLW + i][(y - BORDER_TOP - (y - BORDER_TOP) % CELLH) / CELLH + j];
}

void Play::createRankingBin( int highScore)
 {
	RankStruct auxStruct;
	std::list<RankStruct> auxRanking;
	char auxName[10];
	int auxScore;
	std::ifstream rankingBin("../../res/files/ranking.bin", std::ios::in | std::ios::binary);
	if (!rankingBin.peek() == std::ifstream::traits_type::eof())
	{
		//LEER Y GUARDAR
		for (int i = 0; rankingBin.eof() != true; i++)
		{
			rankingBin.read(reinterpret_cast<char *>(&auxName), sizeof(char) * 10);
			rankingBin.read(reinterpret_cast<char *>(&auxScore), sizeof(auxScore));

			auxStruct.name = auxName;
			auxStruct.score = auxScore;
			auxRanking.push_back(auxStruct);
		}
		rankingBin.close();
		std::string answer1;
		do
		{
			std::cout << "Quieres guardar tu puntuacion? (y/n)" << std::endl;
			std::cin >> answer1;
			std::cout << std::endl;
		} while (answer1 != "y" && answer1 != "n" && answer1 != "Y" && answer1 != "N");
		if (answer1 == "y" || answer1 == "Y")
		{
			std::cout << "Tu nombre? (Maximo 10 caracteres alfabeticos)" << std::endl;
			std::cin >> auxName;
			std::cout << std::endl;
			auxScore = highScore;

			auxStruct.name = auxName;
			auxStruct.score = auxScore;

			if (auxRanking.size() == 10)
			{
				auxRanking.push_back(auxStruct);
				auxRanking.sort();
				auxRanking.reverse();
				auxRanking.pop_back();
			}
			else
			{
				auxRanking.push_back(auxStruct);
				auxRanking.sort();
				auxRanking.reverse();
			}
			std::ofstream rankingBin("ranking.bin", std::ios::out | std::ios::binary);
			rankingBin.clear();
			for each (RankStruct rs in auxRanking)
			{
				rankingBin.write(reinterpret_cast<char *>(&rs.name), sizeof(char) * 10);
				rankingBin.write(reinterpret_cast<char *>(&rs.score), sizeof(rs.score));				
			}
			rankingBin.close();
		}
	}
	else
	{
		//GUARDADO UNICO
		rankingBin.close();
		std::string answer1;
		do
		{
			std::cout << "Quieres guardar tu puntuación? (y/n)" << std::endl;
			std::cin >> answer1;
			std::cout << std::endl;
		} while (answer1 != "y" && answer1 != "n" && answer1 != "Y" && answer1 != "N");
		if (answer1 == "y" || answer1 == "Y")
		{
			std::cout << "Tu nombre? (Máximo 30 caracteres)" << std::endl;
			std::cin >> auxName;
			std::cout << std::endl;
			auxScore = highScore;

			std::ofstream rankingBin("ranking.bin", std::ios::out | std::ios::binary);
			rankingBin.write(reinterpret_cast<char *>(&auxName), sizeof(char) * 10);
			rankingBin.write(reinterpret_cast<char *>(&auxScore), sizeof(auxScore));
			rankingBin.close();
		}
	}
}
