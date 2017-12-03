#include "Play.h"
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include <sstream>



Play::Play( int num ) :
	Escena::Escena(720, 704),
	estado(""),
	p1(1, 48 + 1 * 48, 128 + 1 * 48),
	p2(2, 48 + 11 * 48, 128 + 9 * 48)
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
	mapa = new Objeto**[rows];
	for (int i = 0; i < rows; i++) {
		mapa[i] = new Objeto*[cols + 1];
	}

	//Creamos los objetos del mapa
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			rapidxml::xml_node<> *celda = Mat
				->first_node(("Fila_" + std::to_string(i)).c_str())
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
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
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
		p1.setMov(Movimiento::UP);
	}
	else if (eventos["s"])
	{
		p1.setMov(Movimiento::DOWN);
	}
	else if (eventos["a"])
	{
		p1.setMov(Movimiento::LEFT);
	}
	else if (eventos["d"])
	{
		p1.setMov(Movimiento::RIGHT);
	}
	else
	{
		p1.setMov(Movimiento::NONE);
	}
	if (eventos["up"])
	{
		p2.setMov(Movimiento::UP);
	}
	else if (eventos["down"])
	{
		p2.setMov(Movimiento::DOWN);
	}
	else if (eventos["left"])
	{
		p2.setMov(Movimiento::LEFT);
	}
	else if (eventos["right"])
	{
		p2.setMov(Movimiento::RIGHT);
	}	
	else
	{
		p2.setMov(Movimiento::NONE);
	}

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
