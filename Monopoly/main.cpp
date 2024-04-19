#include "gameEngine.h"


int main(){


	try {
		gameEngine game;
		game.RunGame();

	}
	catch (const char* msg) { cout << msg << endl; }
	catch (...) {
		std::cout << "unhandeled eception";
	};


	
	system("pause");

	return 0;
}