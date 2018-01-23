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

	std::vector<RankStruct> rankingVector = createRankingList();

	for (int i = 1; i <= 10; i++)
	{
		Text posNum;
		posNum.color = Color{ 0, 0, 0, 0 };
		posNum.id = "POS_" + std::to_string(i) + "_NUM";
		posNum.text = std::to_string(i) + ".";
		Renderer::Instance()->LoadTextureText(fNums.id, posNum);
		aux = Renderer::Instance()->GetTextureSize(posNum.id);
		posNum.w = 100;
		posNum.h = 100;
		rankNums.push_back(SDL_Rect{ (i < 6) ? 60 : (720 / 2 + 15), ((704 - 120) / 5) * ((i % 6) - ((i<6) ? 1 : 0)) + 50, posNum.w, posNum.h });

		RankRectStruct rectStruct;

		Text posName;
		posName.color = Color{ 0, 0, 0, 0 };
		posName.id = "POS_" + std::to_string(i) + "_NAME";
		posName.text = rankingVector[i - 1].name;
		Renderer::Instance()->LoadTextureText(fText.id, posName);
		aux = Renderer::Instance()->GetTextureSize(posName.id);
		posName.h = 40;
		posName.w = aux.x * posName.h / aux.y;
		rectStruct.nameRect = SDL_Rect{ posNum.w + 15 + ((i < 6) ? 60 : (720 / 2 + 15)), 25 + (((704 - 120) / 5) * ((i % 6) - ((i < 6) ? 1 : 0)) + 50), posName.w, posName.h };

		Text posScore;
		posScore.color = Color{ 0, 0, 0, 0 };
		posScore.id = "POS_" + std::to_string(i) + "_SCORE";
		posScore.text = ((rankingVector[i-1].score < 0) ? "----" : std::to_string(rankingVector[i - 1].score));
		Renderer::Instance()->LoadTextureText(fNums.id, posScore);
		aux = Renderer::Instance()->GetTextureSize(posScore.id);
		posScore.h = 40;
		posScore.w = aux.x * posScore.h / aux.y;
		rectStruct.scoreRect = SDL_Rect{ posNum.w + 15 + ((i < 6) ? 60 : (720 / 2 + 15)), 50 + (((704 - 120) / 5) * ((i % 6) - ((i < 6) ? 1 : 0)) + 50), posScore.w, posScore.h };

		rankRects.push_back(rectStruct);
	}
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
	for (int i = 0; i < 10; i++)
	{
		Renderer::Instance()->PushImage("POS_" + std::to_string(i + 1) + "_NUM", rankNums[i]);
		Renderer::Instance()->PushImage("POS_" + std::to_string(i + 1) + "_NAME", rankRects[i].nameRect);
		Renderer::Instance()->PushImage("POS_" + std::to_string(i + 1) + "_SCORE", rankRects[i].scoreRect);
	}
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

std::vector<RankStruct> Ranking::createRankingList()
{
	std::vector<RankStruct> rankingList;
	RankStruct auxStruct;
	std::string auxName;
	int auxScore;
	int i = 0;
	std::ifstream rankingBin("ranking.bin", std::ios::in | std::ios::binary);

	rankingBin.seekg(0, std::ios::end);
	int size = (int)rankingBin.tellg();
	rankingBin.seekg(0, std::ios::beg);

	while (/*rankingBin.tellg() < size*/ true)
	{
		if (!rankingBin) break;
		rankingBin.read(reinterpret_cast<char *>(&auxScore), sizeof(auxScore));
		size_t stringSize = 0;
		rankingBin.read(reinterpret_cast<char *>(&stringSize), sizeof(size_t));
		char* temp = new char[stringSize + 1];
		rankingBin.read(temp, stringSize);
		temp[stringSize] = '\0';
		auxName = temp;
		delete[]temp;

		auxStruct.name = auxName;
		auxStruct.score = auxScore;
		rankingList.push_back(auxStruct);
		i++;		
	}
	rankingBin.close();

	auxStruct.name = "----";
	auxStruct.score = -1;
	while (i < 10)
	{
		rankingList.push_back(auxStruct);
		i++;
	}
	
	return rankingList;
}


