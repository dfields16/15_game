#include "GameManager.h"
#include <string.h>
#include <iostream>

using namespace std;
GameManager::GameManager(Difficulty d):
	difficulty(d),
	gameWin(Point(0,0), 200, 250, "15Game")
	{
		switch(difficulty){
			case Beginner:
				gamePtrn = BPTRN;
			break;
			case Intermediate:
				gamePtrn = IPTRN;
			break;
			case Advanced:
				gamePtrn = APTRN;
			break;
			case Expert:
				gamePtrn = EPTRN;
			break;
		}
	}
	
bool GameManager::checkWinState(bool shouldLog){
	bool isCompleted = false;
	//memcpy(gamePtrn, gameWin.getCurrentPattern(), sizeof(CPTRN));
	gamePtrn = gameWin.getCurrentPattern();
	for(int x = 0; x < 4; ++x){
		for(int y = 0; y < 4; ++y){
			if(gamePtrn[x][y] == CPTRN[x][y])isCompleted = true;
			if(shouldLog)cout << gamePtrn[x][y] << " ";
		}
		if(shouldLog)cout << endl;
	}
	return isCompleted;
}









