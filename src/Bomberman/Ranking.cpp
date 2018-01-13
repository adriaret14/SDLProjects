#include "Ranking.h"
#include <sstream>
#include <fstream>

Ranking::Ranking():
	Escena::Escena(720, 704)
{
	Font fText;
	fText.id = SAIYAN_80;
	fText.path = PATH_FONT + "saiyan.ttf";
	fText.size = 80;
	Renderer::Instance()->LoadFont(fText);

	Font fNums;
	fNums.id = GAMEOVER_80;
	fNums.path = PATH_FONT + "game_over.ttf";
	fNums.size = 80;
	Renderer::Instance()->LoadFont(fNums);

	//Menu button text
	Text exit;
	exit.color = Color{ 0, 0, 0, 0 };
	exit.id = RANKING_TEXT_BUTTON_MENU;
	exit.text = "Main Menu";
	Renderer::Instance()->LoadTextureText(fText.id, exit);
	Vector2 aux = Renderer::Instance()->GetTextureSize(exit.id);
	exit.w = aux.x;
	exit.h = aux.y;
	exitRect = SDL_Rect{ 720 / 2 - (exit.w / 2), 704 - exit.h - 10, exit.w, exit.h };

	//Top ten Title
	Text topTen;
	topTen.color = Color{ 0, 0, 0, 0 };
	topTen.id = "TOP_TEN";
	topTen.text = "TOP TEN";
	Renderer::Instance()->LoadTextureText(fText.id, topTen);
	aux = Renderer::Instance()->GetTextureSize(topTen.id);
	topTen.w = aux.x;
	topTen.h = aux.y;
	topTenRect = SDL_Rect{ 720 / 2 - (topTen.w / 2), 10, topTen.w, topTen.h };

	//Pos Numbers
		//One
	Text posOneNum;
	posOneNum.color = Color{ 0, 0, 0, 0 };
	posOneNum.id = "POS_ONE_NUM";
	posOneNum.text = "1.";
	Renderer::Instance()->LoadTextureText(fNums.id, posOneNum);
	aux = Renderer::Instance()->GetTextureSize(posOneNum.id);
	posOneNum.w = 118;
	posOneNum.h = 118;
	posOneNumRect = SDL_Rect{ 60, ((704 - 90) / 5) * 0 + 50, posOneNum.w, posOneNum.h };
		//Two
	Text posTwoNum;
	posTwoNum.color = Color{ 0, 0, 0, 0 };
	posTwoNum.id = "POS_TWO_NUM";
	posTwoNum.text = "2.";
	Renderer::Instance()->LoadTextureText(fNums.id, posTwoNum);
	aux = Renderer::Instance()->GetTextureSize(posTwoNum.id);
	posTwoNum.w = 118;
	posTwoNum.h = 118;
	posTwoNumRect = SDL_Rect{ 60, ((704 - 90) / 5) * 1 + 50, posTwoNum.w, posTwoNum.h };
		//Three
	Text posThrNum;
	posThrNum.color = Color{ 0, 0, 0, 0 };
	posThrNum.id = "POS_THR_NUM";
	posThrNum.text = "3.";
	Renderer::Instance()->LoadTextureText(fNums.id, posThrNum);
	aux = Renderer::Instance()->GetTextureSize(posThrNum.id);
	posThrNum.w = 118;
	posThrNum.h = 118;
	posThrNumRect = SDL_Rect{ 60, ((704 - 90) / 5) * 2 + 50, posThrNum.w, posThrNum.h };
		//Four
	Text posForNum;
	posForNum.color = Color{ 0, 0, 0, 0 };
	posForNum.id = "POS_FOR_NUM";
	posForNum.text = "4.";
	Renderer::Instance()->LoadTextureText(fNums.id, posForNum);
	aux = Renderer::Instance()->GetTextureSize(posForNum.id);
	posForNum.w = 118;
	posForNum.h = 118;
	posForNumRect = SDL_Rect{ 60, ((704 - 90) / 5) * 3 + 50, posForNum.w, posForNum.h };
		//Five
	Text posFivNum;
	posFivNum.color = Color{ 0, 0, 0, 0 };
	posFivNum.id = "POS_FIV_NUM";
	posFivNum.text = "5.";
	Renderer::Instance()->LoadTextureText(fNums.id, posFivNum);
	aux = Renderer::Instance()->GetTextureSize(posFivNum.id);
	posFivNum.w = 118;
	posFivNum.h = 118;
	posFivNumRect = SDL_Rect{ 60, ((704 - 90) / 5) * 4 + 50, posFivNum.w, posFivNum.h };
		//Six
	Text posSixNum;
	posSixNum.color = Color{ 0, 0, 0, 0 };
	posSixNum.id = "POS_SIX_NUM";
	posSixNum.text = "6.";
	Renderer::Instance()->LoadTextureText(fNums.id, posSixNum);
	aux = Renderer::Instance()->GetTextureSize(posSixNum.id);
	posSixNum.w = 118;
	posSixNum.h = 118;
	posSixNumRect = SDL_Rect{ 720 / 2 + 15, ((704 - 90) / 5) * 0 + 50, posSixNum.w, posSixNum.h };
		//Seven
	Text posSevNum;
	posSevNum.color = Color{ 0, 0, 0, 0 };
	posSevNum.id = "POS_SEV_NUM";
	posSevNum.text = "7.";
	Renderer::Instance()->LoadTextureText(fNums.id, posSevNum);
	aux = Renderer::Instance()->GetTextureSize(posSevNum.id);
	posSevNum.w = 118;
	posSevNum.h = 118;
	posSevNumRect = SDL_Rect{ 720 / 2 + 15, ((704 - 90) / 5) * 1 + 50, posSevNum.w, posSevNum.h };
		//Eight
	Text posEitNum;
	posEitNum.color = Color{ 0, 0, 0, 0 };
	posEitNum.id = "POS_EIT_NUM";
	posEitNum.text = "8.";
	Renderer::Instance()->LoadTextureText(fNums.id, posEitNum);
	aux = Renderer::Instance()->GetTextureSize(posEitNum.id);
	posEitNum.w = 118;
	posEitNum.h = 118;
	posEitNumRect = SDL_Rect{ 720 / 2 + 15, ((704 - 90) / 5) * 2 + 50, posEitNum.w, posEitNum.h };
		//Nine
	Text posNinNum;
	posNinNum.color = Color{ 0, 0, 0, 0 };
	posNinNum.id = "POS_NIN_NUM";
	posNinNum.text = "9.";
	Renderer::Instance()->LoadTextureText(fNums.id, posNinNum);
	aux = Renderer::Instance()->GetTextureSize(posNinNum.id);
	posNinNum.w = 118;
	posNinNum.h = 118;
	posNinNumRect = SDL_Rect{ 720 / 2 + 15, ((704 - 90) / 5) * 3 + 50, posNinNum.w, posNinNum.h };
		//Ten
	Text posTenNum;
	posTenNum.color = Color{ 0, 0, 0, 0 };
	posTenNum.id = "POS_TEN_NUM";
	posTenNum.text = "10.";
	Renderer::Instance()->LoadTextureText(fNums.id, posTenNum);
	aux = Renderer::Instance()->GetTextureSize(posTenNum.id);
	posTenNum.w = 118;
	posTenNum.h = 118;
	posTenNumRect = SDL_Rect{ 720 / 2 + 15, ((704 - 90) / 5) * 4 + 50, posTenNum.w, posTenNum.h };
}

Ranking::~Ranking()
{
}

void Ranking::draw()
{
	Renderer::Instance()->Clear();
	Renderer::Instance()->PushImage("BG", background);
	Renderer::Instance()->PushImage(RANKING_TEXT_BUTTON_MENU, exitRect);
	Renderer::Instance()->PushImage("TOP_TEN", topTenRect);
	Renderer::Instance()->PushImage("POS_ONE_NUM", posOneNumRect);
	Renderer::Instance()->PushImage("POS_TWO_NUM", posTwoNumRect);
	Renderer::Instance()->PushImage("POS_THR_NUM", posThrNumRect);
	Renderer::Instance()->PushImage("POS_FOR_NUM", posForNumRect);
	Renderer::Instance()->PushImage("POS_FIV_NUM", posFivNumRect);
	Renderer::Instance()->PushImage("POS_SIX_NUM", posSixNumRect);
	Renderer::Instance()->PushImage("POS_SEV_NUM", posSevNumRect);
	Renderer::Instance()->PushImage("POS_EIT_NUM", posEitNumRect);
	Renderer::Instance()->PushImage("POS_NIN_NUM", posNinNumRect);
	Renderer::Instance()->PushImage("POS_TEN_NUM", posTenNumRect);
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

std::list<RankStruct> Ranking::createRankingList()
{
	std::list<RankStruct> rankingList;
	RankStruct auxStruct;
	char auxName[30];
	int auxScore;

	std::ifstream rankingBin("../../res/files/ranking.bin", std::ios::in | std::ios::binary);

	while (!rankingBin.eof())
	{
		rankingBin.read(reinterpret_cast<char *>(&auxName), sizeof(char) * 30);
		rankingBin.read(reinterpret_cast<char *>(&auxScore), sizeof(auxScore));

		auxStruct.name = auxName;
		auxStruct.score = auxScore;
		rankingList.push_back(auxStruct);
	}
	rankingBin.close();
	return rankingList;
}


