#include "GameManager.h"
#include <string.h>
#include <iostream>

using namespace std;
GameManager::GameManager(Difficulty d):
	difficulty(d)
	{
		switch(difficulty){
			case Beginner:
				memcpy(gamePtrn, BPTRN, sizeof(BPTRN));
			break;
			case Intermediate:
				memcpy(gamePtrn, IPTRN, sizeof(IPTRN));
			break;
			case Advanced:
				memcpy(gamePtrn, APTRN, sizeof(APTRN));
			break;
			case Expert:
				memcpy(gamePtrn, EPTRN, sizeof(EPTRN));
			break;
		}
	}
	
bool GameManager::checkWinState(bool shouldLog){
	bool isCompleted = false;
	for(int x = 0; x < 4; ++x){
		for(int y = 0; y < 4; ++y){
			if(gamePtrn[x][y] == CPTRN[x][y])isCompleted = true;
			if(shouldLog)cout << gamePtrn[x][y] << " ";
		}
		if(shouldLog)cout << endl;
	}
	return isCompleted;
}









