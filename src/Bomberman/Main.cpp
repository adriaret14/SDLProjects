#include<SDL.h>
#include <exception>
#include "Game.h"
#include <iostream>
#include <time.h> 

int main(int argc, char *argv[]) {

	srand(time(NULL));
	Game a;
	a.update();

	return 0;
}
