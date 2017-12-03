#include "Play.h"
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include <sstream>



Play::Play( int num ) :
	Escena::Escena(720, 704),
	p1(1, 300, 300),
	p2(2, 400, 300)
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
	p1.update();
	p2.update();
}

void Play::eHandler()
{
	SDL_Event event;
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	
			//Controles jugador 1
			if (state[SDL_SCANCODE_W])
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
			}

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:		
				//isRunning = false; 
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
			default:
				break;
			}
		}
}
