#include "Menu.h"



Menu::Menu():
	Escena::Escena(720,704)
{
	Font f;
	f.id = SAIYAN_80;
	f.path = PATH_FONT + "saiyan.ttf";
	f.size = 80;
	Renderer::Instance()->LoadFont(f);

	Text textplay1;
	textplay1.color= Color{ 0, 0, 0, 0 };
	textplay1.id = MENU_TEXT_BUTTON_PLAY1;
	textplay1.text = "Play Level A";
	Renderer::Instance()->LoadTextureText(f.id, textplay1);
	Vector2 aux = Renderer::Instance()->GetTextureSize(textplay1.id);
	textplay1.w = aux.x;
	textplay1.h = aux.y;
	play1Rect= SDL_Rect{ 720 / 2 - (textplay1.w / 2), 704 / 6 - (textplay1.h / 2), textplay1.w, textplay1.h };

	Text textplay2;
	textplay2.color = Color{ 0, 0, 0, 0 };
	textplay2.id = MENU_TEXT_BUTTON_PLAY2;
	textplay2.text = "Play Level B";
	Renderer::Instance()->LoadTextureText(f.id, textplay2);
	Vector2 aux2 = Renderer::Instance()->GetTextureSize(textplay2.id);
	textplay2.w = aux2.x;
	textplay2.h = aux2.y;
	play2Rect = SDL_Rect{ 720 / 2 - (textplay2.w / 2), 2 * 704 / 6 - (textplay2.h / 2), textplay2.w, textplay2.h };

	Text rank;
	rank.color = Color{ 0, 0, 0, 0 };
	rank.id = MENU_TEXT_BUTTON_RANK;
	rank.text = "Rankings";
	Renderer::Instance()->LoadTextureText(f.id, rank);
	Vector2 aux3 = Renderer::Instance()->GetTextureSize(rank.id);
	rank.w = aux3.x;
	rank.h = aux3.y;
	rankRect = SDL_Rect{ 720 / 2 - (rank.w / 2), 3 * 704 / 6 - (rank.h / 2), rank.w, rank.h };

	Text mute;
	mute.color = Color{ 0, 0, 0, 0 };
	mute.id = MENU_TEXT_BUTTON_MUTE;
	mute.text = "Mute Game";
	Renderer::Instance()->LoadTextureText(f.id, mute);
	Vector2 aux4 = Renderer::Instance()->GetTextureSize(mute.id);
	mute.w = aux4.x;
	mute.h = aux4.y;
	muteRect = SDL_Rect{ 720 / 2 - (mute.w / 2), 4 * 704 / 6 - (mute.h / 2), mute.w, mute.h };

	Text exit;
	exit.color = Color{ 0, 0, 0, 0 };
	exit.id = MENU_TEXT_BUTTON_EXIT;
	exit.text = "Exit Game";
	Renderer::Instance()->LoadTextureText(f.id, exit);
	Vector2 aux5 = Renderer::Instance()->GetTextureSize(rank.id);
	exit.w = aux5.x;
	exit.h = aux5.y;
	exitRect = SDL_Rect{ 720 / 2 - (exit.w / 2), 5 * 704 / 6 - (exit.h / 2), exit.w, exit.h };

}


Menu::~Menu()
{
}

void Menu::draw()
{
	Renderer::Instance()->Clear();
	Renderer::Instance()->PushImage("BG", background);
	Renderer::Instance()->PushImage(MENU_TEXT_BUTTON_PLAY1, play1Rect);
	Renderer::Instance()->PushImage(MENU_TEXT_BUTTON_PLAY2, play2Rect);
	Renderer::Instance()->PushImage(MENU_TEXT_BUTTON_RANK, rankRect);
	Renderer::Instance()->PushImage(MENU_TEXT_BUTTON_MUTE, muteRect);
	Renderer::Instance()->PushImage(MENU_TEXT_BUTTON_EXIT, exitRect);
	Renderer::Instance()->Render();
}

void Menu::update()
{
	std::cout << "." << std::endl;
}

void Menu::eHandler()
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
			if ((mouseX >= play1Rect.x && mouseX <= play1Rect.x + play1Rect.w) && (mouseY >= play1Rect.y && mouseY <= play1Rect.y + play1Rect.h))
			{
				Estado = estadoActual::GoToLvl1;
			}
			if ((mouseX >= play2Rect.x && mouseX <= play2Rect.x + play2Rect.w) && (mouseY >= play2Rect.y && mouseY <= play2Rect.y + play2Rect.h))
			{
				Estado = estadoActual::GoToLvl2;
			}
			if ((mouseX >= rankRect.x && mouseX <= rankRect.x + rankRect.w) && (mouseY >= rankRect.y && mouseY <= rankRect.y + rankRect.h))
			{
				Estado = estadoActual::GoToRank;
			}
			if ((mouseX >= muteRect.x && mouseX <= muteRect.x + muteRect.w) && (mouseY >= muteRect.y && mouseY <=muteRect.y + muteRect.h))
			{

			}
			if ((mouseX >= exitRect.x && mouseX <= exitRect.x + exitRect.w) && (mouseY >= exitRect.y && mouseY <= exitRect.y + exitRect.h))
			{
				Estado = estadoActual::Exit;
			}

			break;
		}
	}
}
