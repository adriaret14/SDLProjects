#include "Play.h"
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include <sstream>



Play::Play( int num ) :
	Escena::Escena(720, 704),
	estado(""),
	p1(1, BORDER_LEFT + 2 * CELLW, BORDER_TOP + 2 * CELLH),
	p2(2, BORDER_LEFT + 12 * CELLW, BORDER_TOP + 10 * CELLH)
{
	//Cargamos todas las texturas necesarias
	Renderer::Instance()->LoadTexture(ITEMS, PATH_IMG + "items.png");


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

	eventos["up"] = false;
	eventos["left"] = false;
	eventos["down"] = false;
	eventos["right"] = false;

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

	//Controles jugador 2
	eventos["up"] = state[SDL_SCANCODE_UP];
	eventos["down"] = state[SDL_SCANCODE_DOWN];
	eventos["left"] = state[SDL_SCANCODE_LEFT];
	eventos["right"] = state[SDL_SCANCODE_RIGHT];

	//Misc
	eventos["esc"] = state[SDL_SCANCODE_ESCAPE];

			/*if (state[SDL_SCANCODE_W])
			{
				p1.setMov(Movimiento::UP);
			}
			if (state[SDL_SCANCODE_S])
			{
				p1.setMov(Movimiento::DOWN);
			}
			if (state[SDL_SCANCODE_A])
			{
				p1.setMov(Movimiento::LEFT);
			}
			if (state[SDL_SCANCODE_D])
			{
				p1.setMov(Movimiento::RIGHT);
			}
			if (state[SDL_SCANCODE_UP])
			{
				p2.setMov(Movimiento::UP);
			}
			if (state[SDL_SCANCODE_DOWN])
			{
				p2.setMov(Movimiento::DOWN);
			}
			if (state[SDL_SCANCODE_LEFT])
			{
				p2.setMov(Movimiento::LEFT);
			}
			if (state[SDL_SCANCODE_RIGHT])
			{
				p2.setMov(Movimiento::RIGHT);
			}
			if (!state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_S] && !state[SDL_SCANCODE_D])
			{
				p1.setMov(Movimiento::NONE);
			}
			if (!state[SDL_SCANCODE_UP] && !state[SDL_SCANCODE_DOWN] && !state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT])
			{
				p2.setMov(Movimiento::NONE);
			}*/

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:		
				//isRunning = false;
				eventos["quit"] = true;
				break;
			case SDL_KEYDOWN:
				//if (event.key.keysym.sym == SDLK_ESCAPE && escena == 1) escena = 0;
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_a)
				{
					//p1.setMov(Movimiento::NONE);
				}
				if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT)
				{
					//p2.setMov(Movimiento::NONE);
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				eventos["click"] = true;
				/*int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				if ((mouseX >= textRectPlay.x && mouseX <= textRectPlay.x + textRectPlay.w) && (mouseY >= textRectPlay.y && mouseY <= textRectPlay.y + textRectPlay.h))
				{
					escena = 1;
				}
				if ((mouseX >= textRectExit.x && mouseX <= textRectExit.x + textRectExit.w) && (mouseY >= textRectExit.y && mouseY <= textRectExit.y + textRectExit.h))
				{
					isRunning = false;
				}*/
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

Objeto * Play::getAdjCell(int x, int y, int i, int j)
{
	return mapa[(x - BORDER_LEFT - (x - BORDER_LEFT) % CELLW) / CELLW + i][(y - BORDER_TOP - (y - BORDER_TOP) % CELLH) / CELLH + j];
}