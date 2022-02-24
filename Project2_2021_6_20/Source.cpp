#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <WinUser.h>
#include <cstdlib>
#include "GameManager.h"

int main() {

	srand(time(NULL));

	GameManager myGM;
	myGM.startGame();
	while (1) {
		GameManager myGM;
		myGM.startGame();
	}
}