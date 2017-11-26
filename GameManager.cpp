#include "GameManager.h"
#include <string.h>
#include <iostream>

using namespace std;
GameManager::GameManager(Difficulty d):
	difficulty(d),
	gamePtrn(BPTRN),
	gameWin(Point(0,0), 425, 275, "15Game")
	{
		switch(difficulty){
			case Beginner:
				gamePtrn = BPTRN;
				movesLeft = 10;
			break;
			case Intermediate:
				gamePtrn = IPTRN;
				movesLeft = 20;
			break;
			case Advanced:
				gamePtrn = APTRN;
				movesLeft = 40;
			break;
			case Expert:
				gamePtrn = EPTRN;
				movesLeft = 80;
			break;
		}
		maxMoves = movesLeft;
		gameWin.createButtons(gamePtrn);
		gameWin.setScore(movesLeft, false);
	}
	
bool GameManager::checkWinState(bool shouldLog = false){
	bool isCompleted = false;
	int numCorrect = 0;
	//Get current game board
	if(gamePtrn != gameWin.getCurrentPattern()){
		gamePtrn = gameWin.getCurrentPattern();
		movesLeft -= 1;
		cout << "Moves Left: " << movesLeft << endl;
		gameWin.setScore(movesLeft, false);
	}
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
			if(Point(y,x) == gameWin.btns[p.y][p.x].location){
				gameWin.btns[p.y][p.x].setColor(Color::green);
				numCorrect += 1;
			}
			else gameWin.btns[p.y][p.x].setColor(Color::red);
			//Logs the current board to terminal
			if(shouldLog)cout << gamePtrn[y][x] << " ";
		}
		if(shouldLog)cout << endl;
	}	
	if(shouldLog && isCompleted)cout << "You win!" << endl;
	else if(shouldLog)cout << "You're almost there!" << endl;
	if(movesLeft <= 0){
			gameWin.setScore(numCorrect*maxMoves,true);
			return true;
	}
	return isCompleted;
}








