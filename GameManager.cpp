#include "GameManager.h"
#include <string.h>
#include <iostream>

using namespace std;
GameManager::GameManager(Difficulty d):
	difficulty(d),
	gamePtrn(BPTRN),
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
		gameWin.createButtons(gamePtrn);
	}
	
bool GameManager::checkWinState(bool shouldLog = false){
	bool isCompleted = false;
	//Get current game board
	gamePtrn = gameWin.getCurrentPattern();
	for   (int y = 0; y < 4; ++y){
		for (int x = 0; x < 4; ++x){
			//If Tiles are in the right spot, they are colored green
			Point p = gameWin.findTile(CPTRN[x][y]);
			if(Point(y,x) == gameWin.btns[p.y][p.x].location)isCompleted = true;
			else {
				isCompleted = false;
				break;
			}
		}
	}
	
	for   (int y = 0; y < 4; ++y){
		for (int x = 0; x < 4; ++x){
			//If Tiles are in the right spot, they are colored green
			Point p = gameWin.findTile(CPTRN[x][y]);
			if(Point(y,x) == gameWin.btns[p.y][p.x].location)gameWin.btns[p.y][p.x].setColor(Color::green);
			else gameWin.btns[p.y][p.x].setColor(Color::red);
			//Logs the current board to terminal
			if(shouldLog)cout << gamePtrn[y][x] << " ";
		}
		if(shouldLog)cout << endl;
	}	
	if(shouldLog && isCompleted)cout << "You win!" << endl;
	else if(shouldLog)cout << "You're almost there!" << endl;
	return isCompleted;
}








