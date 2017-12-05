#include "HUD.h"

HUD::HUD( Player & player1, Player & player2):
	Player1(player1),
	Player2(player2),
	nums(10, "")
{
	nums[0] = NUM0;
	nums[1] = NUM1;
	nums[2] = NUM2;
	nums[3] = NUM3;
	nums[4] = NUM4;
	nums[5] = NUM5;
	nums[6] = NUM6;
	nums[7] = NUM7;
	nums[8] = NUM8;
	nums[9] = NUM9;

	Font f;
	f.id = SAIYAN_80;
	f.path = PATH_FONT + "saiyan.ttf";
	f.size = 80;
	Renderer::Instance()->LoadFont(f);

	Font fnums;
	fnums.id = DBZ_80;
	fnums.path = PATH_FONT + "ColophonDBZ.ttf";
	fnums.size = 80;
	Renderer::Instance()->LoadFont(fnums);

	//TEXTURES--------------------------------------------------------------------------
	//Player
	Text textPlayer;
	textPlayer.color = Color{ 0, 0, 0, 0 };
	textPlayer.id = HUD_TEXT_PLAYER;
	textPlayer.text = "Player";

	Renderer::Instance()->LoadTextureText(f.id, textPlayer);
	Vector2 aux = Renderer::Instance()->GetTextureSize(HUD_TEXT_PLAYER);
	textPlayer.w = aux.x * 30 / aux.y;
	textPlayer.h = 30;

	//Lives
	Text textLives;
	textLives.color = Color{ 0, 0, 0, 0 };
	textLives.id = HUD_TEXT_LIVES;
	textLives.text = "Lives";

	Renderer::Instance()->LoadTextureText(f.id, textLives);
	aux = Renderer::Instance()->GetTextureSize(HUD_TEXT_LIVES);
	textLives.w = aux.x * 25 / aux.y;
	textLives.h = 25;

	//Score
	Text textScore;
	textScore.color = Color{ 0, 0, 0, 0 };
	textScore.id = HUD_TEXT_SCORE;
	textScore.text = "Score";

	Renderer::Instance()->LoadTextureText(f.id, textScore);
	aux = Renderer::Instance()->GetTextureSize(HUD_TEXT_SCORE);
	textScore.w = aux.x * 25 / aux.y;
	textScore.h = 25;

	//Time
	Text textTime;
	textTime.color = Color{ 0, 0, 0, 0 };
	textTime.id = HUD_TEXT_TIME;
	textTime.text = "Time";

	Renderer::Instance()->LoadTextureText(f.id, textTime);
	aux = Renderer::Instance()->GetTextureSize(HUD_TEXT_TIME);
	textTime.w = aux.x * 30 / aux.y;
	textTime.h = 30;

	//Numbers
	//0
	Text Num0;
	Num0.color = Color{ 0, 0, 0, 0 };
	Num0.id = NUM0;
	Num0.text = "0";

	Renderer::Instance()->LoadTextureText(fnums.id, Num0);
	aux = Renderer::Instance()->GetTextureSize(NUM0);
	Num0.w = aux.x * 40 / aux.y;
	Num0.h = 40;

	//1
	Text Num1;
	Num1.color = Color{ 0, 0, 0, 0 };
	Num1.id = NUM1;
	Num1.text = "1";

	Renderer::Instance()->LoadTextureText(fnums.id, Num1);
	aux = Renderer::Instance()->GetTextureSize(NUM1);
	Num1.w = aux.x * 40 / aux.y;
	Num1.h = 40;

	//2
	Text Num2;
	Num2.color = Color{ 0, 0, 0, 0 };
	Num2.id = NUM2;
	Num2.text = "2";

	Renderer::Instance()->LoadTextureText(fnums.id, Num2);
	aux = Renderer::Instance()->GetTextureSize(NUM2);
	Num2.w = aux.x * 40 / aux.y;
	Num2.h = 40;

	//3
	Text Num3;
	Num3.color = Color{ 0, 0, 0, 0 };
	Num3.id = NUM3;
	Num3.text = "3";

	Renderer::Instance()->LoadTextureText(fnums.id, Num3);
	aux = Renderer::Instance()->GetTextureSize(NUM3);
	Num3.w = aux.x * 40 / aux.y;
	Num3.h = 40;

	//4
	Text Num4;
	Num4.color = Color{ 0, 0, 0, 0 };
	Num4.id = NUM4;
	Num4.text = "4";

	Renderer::Instance()->LoadTextureText(fnums.id, Num4);
	aux = Renderer::Instance()->GetTextureSize(NUM4);
	Num4.w = aux.x * 40 / aux.y;
	Num4.h = 40;

	//5
	Text Num5;
	Num5.color = Color{ 0, 0, 0, 0 };
	Num5.id = NUM5;
	Num5.text = "5";

	Renderer::Instance()->LoadTextureText(fnums.id, Num5);
	aux = Renderer::Instance()->GetTextureSize(NUM5);
	Num5.w = aux.x * 40 / aux.y;
	Num5.h = 40;

	//6
	Text Num6;
	Num6.color = Color{ 0, 0, 0, 0 };
	Num6.id = NUM6;
	Num6.text = "6";

	Renderer::Instance()->LoadTextureText(fnums.id, Num6);
	aux = Renderer::Instance()->GetTextureSize(NUM6);
	Num6.w = aux.x * 40 / aux.y;
	Num6.h = 40;

	//7
	Text Num7;
	Num7.color = Color{ 0, 0, 0, 0 };
	Num7.id = NUM7;
	Num7.text = "7";

	Renderer::Instance()->LoadTextureText(fnums.id, Num7);
	aux = Renderer::Instance()->GetTextureSize(NUM7);
	Num7.w = aux.x * 40 / aux.y;
	Num7.h = 40;

	//8
	Text Num8;
	Num8.color = Color{ 0, 0, 0, 0 };
	Num8.id = NUM8;
	Num8.text = "8";

	Renderer::Instance()->LoadTextureText(fnums.id, Num8);
	aux = Renderer::Instance()->GetTextureSize(NUM8);
	Num8.w = aux.x * 40 / aux.y;
	Num8.h = 40;

	//9
	Text Num9;
	Num9.color = Color{ 0, 0, 0, 0 };
	Num9.id = NUM9;
	Num9.text = "9";

	Renderer::Instance()->LoadTextureText(fnums.id, Num9);
	aux = Renderer::Instance()->GetTextureSize(NUM9);
	Num9.w = aux.x * 40 / aux.y;
	Num9.h = 40;

	//Colon
	Text colon;
	colon.color = Color{ 0, 0, 0, 0 };
	colon.id = COLON;
	colon.text = ":";

	Renderer::Instance()->LoadTextureText(fnums.id, colon);
	aux = Renderer::Instance()->GetTextureSize(COLON);
	colon.w = aux.x * 40 / aux.y;
	colon.h = 40;


	//RECTS-------------------------------------------------------------------------

	//Player 1
		//Lives text
		tLives1 = SDL_Rect{ 60, 30, textLives.w, textLives.h };
		//Lives number
		l1 = SDL_Rect{ tLives1.x + tLives1.w / 2 - 11, 50, 21, 25 };
		iL1 = Player1.getVida();

		//Player tag
		tPlayer1 = SDL_Rect{ 60, 5, textPlayer.w, textPlayer.h };
		//Player number
		p1 = SDL_Rect{ 60 + textPlayer.w + 15, 5, 25, 30 };

		//Score text
		tScore1 = SDL_Rect{ tLives1.x + tLives1.w + 50, 30, textScore.w, textScore.h };
		//Score n1
		s11 = SDL_Rect{ tScore1.x + tScore1.w / 2 - 2 * 21, 50, 21, 25 };
		iS11 = 0;
		//Score n2
		s12 = SDL_Rect{ tScore1.x + tScore1.w / 2 - 1 * 21, 50, 21, 25 };
		iS12 = 0;
		//Score n3
		s13 = SDL_Rect{ tScore1.x + tScore1.w / 2, 50, 21, 25 };
		iS13 = 0;
		//Score n4
		s14 = SDL_Rect{ tScore1.x + tScore1.w / 2 + 1 * 21, 50, 21, 25 };
		iS14 = 0;

	//Player 2
		//Score text
		tScore2 = SDL_Rect{ SCREEN_WIDTH - 60 - textScore.w, 30, textScore.w, textScore.h };
		//Score n1
		s21 = SDL_Rect{ tScore2.x + tScore2.w / 2 - 2 * 21, 50, 21, 25 };
		iS21 = 0;
		//Score n2
		s22 = SDL_Rect{ tScore2.x + tScore2.w / 2 - 1 * 21, 50, 21, 25 };
		iS22 = 0;
		//Score n3
		s23 = SDL_Rect{ tScore2.x + tScore2.w / 2, 50, 21, 25 };
		iS23 = 0;
		//Score n4
		s24 = SDL_Rect{ tScore2.x + tScore2.w / 2 + 1 * 21, 50, 21, 25 };
		iS24 = 0;
		
		//Lives text
		tLives2 = SDL_Rect{ tScore2.x - textLives.w - 50, 30, textLives.w, textLives.h };
		//Lives number
		l2 = SDL_Rect{ tLives2.x + tLives2.w / 2 - 11, 50, 21, 25 };
		iL2 = Player2.getVida();

		//Player tag
		tPlayer2 = SDL_Rect{ tLives2.x, 5, textPlayer.w, textPlayer.h };
		//Player number
		p2 = SDL_Rect{ tPlayer2.x + textPlayer.w + 15, 5, 25, 30 };

	//Time
		//Time text
		tTime = SDL_Rect{ SCREEN_WIDTH / 2 - textTime.w / 2, 5, textTime.w, textTime.h };
		//Time colon
		tColon = SDL_Rect{ SCREEN_WIDTH / 2 - colon.w, 35, colon.w, colon.h };
		//Time mins
		tMins = SDL_Rect{ tColon.x - 29, 35, 29, 35 };
		iMins = 0;
		//Time tens
		tTens = SDL_Rect{ SCREEN_WIDTH / 2, 35, 29, 35 };
		iTens = 0;
		//Time secs
		tSecs = SDL_Rect{ tTens.x + 29, 35, 29, 35 };
		iSecs = 0;

		timer = clock();
}

void HUD::update()
{
	if (clock() - timer >= CLOCKS_PER_SEC)
	{
		timer = clock();
		if (iSecs == 0)
		{
			if (iTens == 0)
			{
				if (iMins == 0)
				{

				}
				else
				{
					iMins--;
					iTens = 5;
					iSecs = 9;
				}
			}
			else
			{
				iTens--;
				iSecs = 9;
			}
		}
		else
		{
			iSecs--;
		}
	}

	iL1 = Player1.getVida();
	iL2 = Player2.getVida();
	int score1 = Player1.getScore();
	int score2 = Player2.getScore();

	iS11 = floor(score1 / 1000);
	score1 -= iS11;
	iS12 = floor(score1 / 100);
	score1 -= iS12;
	iS13 = floor(score1 / 10);
	score1 -= iS13;
	iS14 = score1;

	iS21 = floor(score2 / 1000);
	score2 -= iS21;
	iS22 = floor(score2 / 100);
	score2 -= iS22;
	iS23 = floor(score2 / 10);
	score2 -= iS23;
	iS24 = score2;
}

void HUD::draw()
{
	Renderer::Instance()->PushImage(HUD_TEXT_PLAYER, tPlayer1);
	Renderer::Instance()->PushImage(NUM1, p1);

	Renderer::Instance()->PushImage(HUD_TEXT_PLAYER, tPlayer2);
	Renderer::Instance()->PushImage(NUM2, p2);

	Renderer::Instance()->PushImage(HUD_TEXT_LIVES, tLives1);
	Renderer::Instance()->PushImage(nums[iL1], l1);

	Renderer::Instance()->PushImage(HUD_TEXT_LIVES, tLives2);
	Renderer::Instance()->PushImage(nums[iL2], l2);

	Renderer::Instance()->PushImage(HUD_TEXT_SCORE, tScore1);
	Renderer::Instance()->PushImage(nums[iS11], s11);
	Renderer::Instance()->PushImage(nums[iS12], s12);
	Renderer::Instance()->PushImage(nums[iS13], s13);
	Renderer::Instance()->PushImage(nums[iS14], s14);

	Renderer::Instance()->PushImage(HUD_TEXT_SCORE, tScore2);
	Renderer::Instance()->PushImage(nums[iS21], s21);
	Renderer::Instance()->PushImage(nums[iS22], s22);
	Renderer::Instance()->PushImage(nums[iS23], s23);
	Renderer::Instance()->PushImage(nums[iS24], s24);

	Renderer::Instance()->PushImage(HUD_TEXT_TIME, tTime);
	Renderer::Instance()->PushImage(COLON, tColon);
	Renderer::Instance()->PushImage(nums[iMins], tMins);
	Renderer::Instance()->PushImage(nums[iTens], tTens);
	Renderer::Instance()->PushImage(nums[iSecs], tSecs);
}

void HUD::setTime(int n)
{
	int time = n;
	iMins = floor(time/60);
	time -= iMins * 60;
	iTens = floor(time/10);
	time -= iTens * 10;
	iSecs = time;
}

HUD::~HUD()
{
}
