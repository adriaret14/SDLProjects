#include <string>
#pragma once

enum estadoActual {Running, Exit, GoTo};
enum escenaActual {Menu, Play1, Play2, Ranking};
class Game
{
public:
	Game();
	~Game();
	void update();
private:
	estadoActual Estado;
	escenaActual Escena;
};

