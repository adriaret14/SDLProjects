#include "HUD.h"

HUD::HUD()
{
	Font f;
	f.id = SAIYAN_80;
	f.path = PATH_FONT + "saiyan.ttf";
	f.size = 80;
	Renderer::Instance()->LoadFont(f);

	//TEXTURES--------------------------------------------------------------------------
	//Player
	Text textPlayer;
	textPlayer.color = Color{ 0, 0, 0, 0 };
	textPlayer.id = HUD_TEXT_PLAYER;
	textPlayer.text = "Player";

	Renderer::Instance()->LoadTextureText(f.id, textPlayer);
	Vector2 aux = Renderer::Instance()->GetTextureSize(HUD_TEXT_PLAYER);
	textPlayer.w = aux.x * 20 / aux.y;
	textPlayer.h = 20;

	//Lives
	Text textLives;
	textLives.color = Color{ 0, 0, 0, 0 };
	textLives.id = HUD_TEXT_LIVES;
	textLives.text = "Lives";

	Renderer::Instance()->LoadTextureText(f.id, textLives);
	aux = Renderer::Instance()->GetTextureSize(HUD_TEXT_LIVES);
	textLives.w = aux.x;
	textLives.h = aux.y;

	//Score
	Text textScore;
	textScore.color = Color{ 0, 0, 0, 0 };
	textScore.id = HUD_TEXT_SCORE;
	textScore.text = "Score";

	Renderer::Instance()->LoadTextureText(f.id, textScore);
	aux = Renderer::Instance()->GetTextureSize(HUD_TEXT_SCORE);
	textScore.w = aux.x;
	textScore.h = aux.y;

	//Time
	Text textTime;
	textTime.color = Color{ 0, 0, 0, 0 };
	textTime.id = HUD_TEXT_TIME;
	textTime.text = "Time";

	Renderer::Instance()->LoadTextureText(f.id, textTime);
	aux = Renderer::Instance()->GetTextureSize(HUD_TEXT_TIME);
	textTime.w = aux.x;
	textTime.h = aux.y;

	//Numbers
	//0
	Text Num0;
	Num0.color = Color{ 0, 0, 0, 0 };
	Num0.id = NUM0;
	Num0.text = "0";

	Renderer::Instance()->LoadTextureText(f.id, Num0);
	aux = Renderer::Instance()->GetTextureSize(NUM0);
	Num0.w = aux.x * 15 / aux.y;
	Num0.h = 15;

	//1
	Text Num1;
	Num1.color = Color{ 0, 0, 0, 0 };
	Num1.id = NUM1;
	Num1.text = "1";

	Renderer::Instance()->LoadTextureText(f.id, Num1);
	aux = Renderer::Instance()->GetTextureSize(NUM1);
	Num1.w = aux.x * 15 / aux.y;
	Num1.h = 15;

	//2
	Text Num2;
	Num2.color = Color{ 0, 0, 0, 0 };
	Num2.id = NUM2;
	Num2.text = "2";

	Renderer::Instance()->LoadTextureText(f.id, Num2);
	aux = Renderer::Instance()->GetTextureSize(NUM2);
	Num2.w = aux.x * 15 / aux.y;
	Num2.h = 15;

	//3
	Text Num3;
	Num3.color = Color{ 0, 0, 0, 0 };
	Num3.id = NUM3;
	Num3.text = "3";

	Renderer::Instance()->LoadTextureText(f.id, Num3);
	aux = Renderer::Instance()->GetTextureSize(NUM3);
	Num3.w = aux.x * 15 / aux.y;
	Num3.h = 15;

	//4
	Text Num4;
	Num4.color = Color{ 0, 0, 0, 0 };
	Num4.id = NUM4;
	Num4.text = "4";

	Renderer::Instance()->LoadTextureText(f.id, Num4);
	aux = Renderer::Instance()->GetTextureSize(NUM4);
	Num4.w = aux.x * 15 / aux.y;
	Num4.h = 15;

	//5
	Text Num5;
	Num5.color = Color{ 0, 0, 0, 0 };
	Num5.id = NUM5;
	Num5.text = "5";

	Renderer::Instance()->LoadTextureText(f.id, Num5);
	aux = Renderer::Instance()->GetTextureSize(NUM5);
	Num5.w = aux.x * 15 / aux.y;
	Num5.h = 15;

	//6
	Text Num6;
	Num6.color = Color{ 0, 0, 0, 0 };
	Num6.id = NUM6;
	Num6.text = "6";

	Renderer::Instance()->LoadTextureText(f.id, Num6);
	aux = Renderer::Instance()->GetTextureSize(NUM6);
	Num6.w = aux.x * 15 / aux.y;
	Num6.h = 15;

	//7
	Text Num7;
	Num7.color = Color{ 0, 0, 0, 0 };
	Num7.id = NUM7;
	Num7.text = "7";

	Renderer::Instance()->LoadTextureText(f.id, Num7);
	aux = Renderer::Instance()->GetTextureSize(NUM7);
	Num7.w = aux.x * 15 / aux.y;
	Num7.h = 15;

	//8
	Text Num8;
	Num8.color = Color{ 0, 0, 0, 0 };
	Num8.id = NUM8;
	Num8.text = "8";

	Renderer::Instance()->LoadTextureText(f.id, Num8);
	aux = Renderer::Instance()->GetTextureSize(NUM8);
	Num8.w = aux.x * 15 / aux.y;
	Num8.h = 15;

	//9
	Text Num9;
	Num9.color = Color{ 0, 0, 0, 0 };
	Num9.id = NUM9;
	Num9.text = "9";

	Renderer::Instance()->LoadTextureText(f.id, Num9);
	aux = Renderer::Instance()->GetTextureSize(NUM9);
	Num9.w = aux.x * 15 / aux.y;
	Num9.h = 15;

	//Colon
	Text colon;
	colon.color = Color{ 0, 0, 0, 0 };
	colon.id = COLON;
	colon.text = ":";

	Renderer::Instance()->LoadTextureText(f.id, colon);
	aux = Renderer::Instance()->GetTextureSize(COLON);
	colon.w = aux.x * 15 / aux.y;
	colon.h = 15;


	//RECTS-------------------------------------------------------------------------

	//Player 1
		//Player tag
		tPlayer1 = SDL_Rect{ 5, 5, textPlayer.w, textPlayer.h };

		//Player number
		p1 = SDL_Rect{  5 + textPlayer.w + 15, 5,  };
	tPlayer2 = SDL_Rect{ SCREEN_WIDTH - 5 - textPlayer.w, 5, textPlayer.w, 20 };
	tPlayer1 = SDL_Rect{ 5, 5, textLives.w, 20 };
	tPlayer2 = SDL_Rect{ SCREEN_WIDTH - 5 - textLives.w, 5, textLives.w, 20 };	
}

void HUD::update()
{
}

void HUD::draw()
{
}

HUD::~HUD()
{
}
