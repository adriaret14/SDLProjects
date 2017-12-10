#include "Ranking.h"



Ranking::Ranking():
	Escena::Escena(720, 704)
{
	Font f;
	f.id = SAIYAN_80;
	f.path = PATH_FONT + "saiyan.ttf";
	f.size = 80;
	Renderer::Instance()->LoadFont(f);

	Text exit;
	exit.color = Color{ 0, 0, 0, 0 };
	exit.id = RANKING_TEXT_BUTTON_MENU;
	exit.text = "Main Menu";
	Renderer::Instance()->LoadTextureText(f.id, exit);
	Vector2 aux = Renderer::Instance()->GetTextureSize(exit.id);
	exit.w = aux.x;
	exit.h = aux.y;
	exitRect = SDL_Rect{ 720 / 2 - (exit.w / 2), 5 * 704 / 6 - (exit.h / 2), exit.w, exit.h };
}


Ranking::~Ranking()
{
	Renderer::Instance()->EmptyRenderer();
}

void Ranking::draw()
{
	Renderer::Instance()->Clear();
	Renderer::Instance()->PushImage("BG", background);
	Renderer::Instance()->PushImage(RANKING_TEXT_BUTTON_MENU, exitRect);
	Renderer::Instance()->Render();
}

void Ranking::update()
{
	//std::cout << "ffff" << std::endl;
}

void Ranking::eHandler()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			Estado = estadoActual::Exit;
			break;
		case SDL_MOUSEBUTTONDOWN:
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			if ((mouseX >= exitRect.x && mouseX <= exitRect.x + exitRect.w) && (mouseY >= exitRect.y && mouseY <= exitRect.y + exitRect.h))
			{
				Estado = estadoActual::Exit;
			}

			break;
		}
	}
}
