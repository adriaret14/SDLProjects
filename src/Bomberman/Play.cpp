#include "Play.h"
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include <sstream>



Play::Play( int num ) :
	Escena::Escena(720, 704),
	p1(1, BORDER_LEFT + 2 * CELLW, BORDER_TOP + 2 * CELLH),
	p2(2, BORDER_LEFT + 12 * CELLW, BORDER_TOP + 10 * CELLH),
	b1(2, 0),
	b2(2, 0)
{
	//Cargamos todas las texturas necesarias
	Renderer::Instance()->LoadTexture(ITEMS, PATH_IMG + "items.png");
	Renderer::Instance()->LoadTexture(EXPS, PATH_IMG + "explosion.png");


	//Determinamos el path del xml del mapa
	std::string mapPath;
	switch (num)
	{
	case 1:
		mapPath = "Map1.xml";
		break;
	case 2:
		mapPath = "Map2.xml";
		break;
	}
	
	rapidxml::xml_document<> doc;
	std::ifstream file(mapPath);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	rapidxml::xml_node<> *pRoot = doc.first_node();
	rapidxml::xml_node<> *Mat = pRoot->first_node("Matriz");

	//Leemos el tamaño de la matriz del mapa
	rows = std::stoi(Mat->first_attribute("filas")->value(), nullptr);
	cols = std::stoi(Mat->first_attribute("columnas")->value(), nullptr);

	//Posiciones de los jugadores
	p1.setX(BORDER_LEFT + std::stoi(Mat->first_attribute("x1")->value(), nullptr) * CELLW);
	p1.setY(BORDER_TOP + std::stoi(Mat->first_attribute("y1")->value(), nullptr) * CELLH);
	p2.setX(BORDER_LEFT + std::stoi(Mat->first_attribute("x2")->value(), nullptr) * CELLW);
	p2.setY(BORDER_TOP + std::stoi(Mat->first_attribute("y2")->value(), nullptr) * CELLH);

	//Asignamos el espacio en memoria de la matriz del mapa
	mapa = new Objeto**[cols];
	for (int i = 0; i < cols; i++) {
		mapa[i] = new Objeto*[rows + 1];
	}

	//Creamos los objetos del mapa
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			rapidxml::xml_node<> *celda = Mat
				->first_node(("Columna_" + std::to_string(i)).c_str())
				->first_node(("Celda_" + std::to_string(j)).c_str());
			std::string s = celda->value();
			//std::cout << s << std::endl;
			if (s == "dest")
			{
				mapa[i][j] = new Dest(i, j);
				std::cout << "8";
			}
			else if (s == "nodest")
			{
				mapa[i][j] = new NoDest(i, j);
				std::cout << "O";
			}
			else
			{
				mapa[i][j] = new Objeto();
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}

	//Llenamos el unordered map de eventos
	eventos["w"] = false;
	eventos["a"] = false;
	eventos["s"] = false;
	eventos["d"] = false;
	eventos["g"] = false;

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
}

void Play::draw()
{
	Renderer::Instance()->Clear();
	Renderer::Instance()->PushImage("BG", background);
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			mapa[i][j]->draw();
		}
	}
	p1.draw();
	p2.draw();
	Renderer::Instance()->Render();
}

void Play::update()
{
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (mapa[i][j]->tipo == ObjTipo::EXP)
			{
				mapa[i][j]->update();
				if (mapa[i][j]->boom)
				{
					mapa[i][j]->~Objeto();
					mapa[i][j] = new Objeto();
				}
			}
		}
	}
	if (p1.bomb)
	{
		mapa[b1[0]][b1[1]]->update();
		if (mapa[b1[0]][b1[1]]->boom)
		{
			mapa[b1[0]][b2[1]]->~Objeto();
			mapa[b1[0]][b1[1]] = new Explosion( b1[0], b1[1], Movimiento::NONE, false, 1);
			std::vector<std::vector<int>> exps = generateExplosionVector(b1[0], b1[1]);
			for (int n = 1; n <= exps[0][0]; n++)
			{
				mapa[b1[0]][b1[1] - n]->~Objeto();
				mapa[b1[0]][b1[1] - n] = new Explosion(b1[0], b1[1] - n, Movimiento::UP, (n == exps[0][0] && exps[1][0] == -1), 1);
			}
			for (int n = 1; n <= exps[0][1]; n++)
			{
				mapa[b1[0]][b1[1] + n]->~Objeto();
				mapa[b1[0]][b1[1] + n] = new Explosion(b1[0], b1[1] + n, Movimiento::DOWN, (n == exps[0][1] && exps[1][1] == -1), 1);
			}
			for (int n = 1; n <= exps[0][2]; n++)
			{
				mapa[b1[0] - n][b1[1]]->~Objeto();
				mapa[b1[0] - n][b1[1]] = new Explosion(b1[0] - n, b1[1], Movimiento::LEFT, (n == exps[0][2] && exps[1][2] == -1), 1);
			}
			for (int n = 1; n <= exps[0][3]; n++)
			{
				mapa[b1[0] + n][b1[1]]->~Objeto();
				mapa[b1[0] + n][b1[1]] = new Explosion(b1[0] + n, b1[1], Movimiento::RIGHT, (n == exps[0][3] && exps[1][3] == -1), 1);
			}
			std::cout << exps[1][0] << " " << exps[1][1] << " " << exps[1][2] << " " << exps[1][3] << std::endl;
			if (exps[1][0] != -1)
			{
				if (mapa[b1[0]][b1[1] - exps[1][0]]->hit())
				{
					mapa[b1[0]][b1[1] - exps[1][0]]->~Objeto();
					mapa[b1[0]][b1[1] - exps[1][0]] = new Objeto();
				}
			}
			if (exps[1][1] != -1)
			{
				if (mapa[b1[0]][b1[1] + exps[1][1]]->hit())
				{
					mapa[b1[0]][b1[1] + exps[1][1]]->~Objeto();
					mapa[b1[0]][b1[1] + exps[1][1]] = new Objeto();
				}
			}
			if (exps[1][2] != -1)
			{
				if (mapa[b1[0] - exps[1][2]][b1[1]]->hit())
				{
					mapa[b1[0] - exps[1][2]][b1[1]]->~Objeto();
					mapa[b1[0] - exps[1][2]][b1[1]] = new Objeto();
				}
			}
			if (exps[1][3] != -1)
			{
				if (mapa[b1[0] + exps[1][3]][b1[1]]->hit())
				{
					mapa[b1[0] + exps[1][3]][b1[1]]->~Objeto();
					mapa[b1[0] + exps[1][3]][b1[1]] = new Objeto();
				}
			}
			p1.bomb = false;
		}
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
	if (eventos["g"])
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
	eventos["g"] = state[SDL_SCANCODE_G];

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