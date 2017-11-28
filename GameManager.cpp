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
	
bool GameManager::checkWinState(){
	vector<vector<int>> tmp = gameWin.getCurrentPattern();
	if(gamePtrn != tmp){
		gameWin.setScore(--movesLeft, false);
		gamePtrn = tmp;
		gameWin.setInstructionText(true, "");
		gameWin.showHint = false;
		printMatrix(gamePtrn);
		prevID = gameWin.prevID;
		showHint();
	}
	if(movesLeft == 0){
		gameWin.setScore(numCorrect*maxMoves, true);
		checkBoardState();
		return true;
	}else return checkBoardState();
}

bool GameManager::checkBoardState(){
	bool isCompleted = true; 
	numCorrect = 0;
	for   (int y = 0; y < 4; ++y){
		for (int x = 0; x < 4; ++x){
			Point p = gameWin.findTile(CPTRN[x][y]);
			if(Point(y,x) == gameWin.btns[p.y][p.x].location){
				if(isCompleted)isCompleted = true;
				gameWin.btns[p.y][p.x].setColor(Color::green);
				numCorrect += 1;
			}else{
				gameWin.btns[p.y][p.x].setColor(Color::red);
				isCompleted = false;
			}
		}
	}
	return isCompleted;
}

int GameManager::findBestPath(){
	vector<vector<int>> tmp = gameWin.getCurrentPattern();
		cout << "CURRENT MATRIX" << endl;
		printMatrix(tmp);
	vector<int> swapID(4,-1);
	vector<int> pathLength(4,-1);
	vector<vector<int>>upM, downM, leftM, rightM;
	upM = createSwapMtrx	(tmp, dUp, &swapID[0]);		//UP
	downM = createSwapMtrx  (tmp, dDown, &swapID[1]);	//DOWN
	leftM = createSwapMtrx  (tmp, dLeft, &swapID[2]);	//LEFT
	rightM = createSwapMtrx (tmp, dRight, &swapID[3]);	//RIGHT
		cout << "UP MATRIX" << endl;
		printMatrix(upM);
		cout << "LEFT MATRIX" << endl;
		printMatrix(leftM);
	for(int i = (movesLeft==maxMoves)? 0:1; i < 16; ++i){
		if(upM   != CPTRN && swapID[0] != prevID)pathLength[0] += manhattanDistance(i, upM);	//UP
		if(downM != CPTRN && swapID[1] != prevID)pathLength[1] += manhattanDistance(i, downM);	//DOWN
		if(leftM != CPTRN && swapID[2] != prevID)pathLength[2] += manhattanDistance(i, leftM);	//LEFT
		if(rightM!= CPTRN && swapID[3] != prevID)pathLength[3] += manhattanDistance(i, rightM);//RIGHT
		cout << "MDistance" << i << ": " << pathLength[0] << " " << pathLength[1] << " " << pathLength[2] << " " << pathLength[3] << " "<< endl;
	}
	int min = 10000;
	for(int i = 0; i < 4; ++i){if(pathLength[i] > 0)min = pathLength[i];break;}
	int returnNum = swapID[0];
	for(int i = 0; i < 4; ++i){
		//cout << "Pathlength " << i << ":" << pathLength[i] << endl;
		//cout << "Swap ID " << i << ":" << swapID[i] << endl;
		if(min > pathLength[i] && pathLength[i] != -1){
			min = pathLength[i];
			returnNum = swapID[i];
			//cout << "chosen: " << min << endl;
		}	
	}
	//cout << "MinMoves: " << min << endl;
	//cout << "Tile ID: " << returnNum << endl;
	return returnNum;
}

vector<vector<int>> GameManager::createSwapMtrx(vector<vector<int>> pattern, Direction dir, int* id){
	vector<vector<int>> rMatrix = pattern;
	Point pZero = findMatrixPos(0,  pattern);
	switch(dir){
			case dUp:
				if(pZero.y-1 >= 0)rMatrix = swapIndices(pattern, pZero, Point(pZero.x,pZero.y-1), id);
				else return CPTRN;
			break;
			case dDown:
				if(pZero.y+1 <= 3)rMatrix = swapIndices(pattern, pZero, Point(pZero.x,pZero.y+1), id);
				else return CPTRN;
			break;
			case dLeft:
				if(pZero.x-1 >= 0)rMatrix = swapIndices(pattern, pZero, Point(pZero.x-1,pZero.y), id);
				else return CPTRN;
			break;
			case dRight:
				if(pZero.x+1 <= 3)rMatrix = swapIndices(pattern, pZero, Point(pZero.x+1,pZero.y), id);
				else return CPTRN;
			break;
	}return rMatrix;
}

vector<vector<int>> GameManager::swapIndices(vector<vector<int>> pattern, Point p1, Point p2, int* id){
	if(pattern[p1.y][p1.x] == 0) *id = pattern[p2.y][p2.x];
	else if(pattern[p2.y][p2.x] == 0) *id = pattern[p1.y][p1.x];
	int tmp = pattern[p1.y][p1.x];
	pattern[p1.y][p1.x] = pattern[p2.y][p2.x];
	pattern[p2.y][p2.x] = tmp;
	return pattern;
}

void GameManager::printMatrix(vector<vector<int>> pattern){
	cout << "Matrix: " << endl;
	for(int y = 0; y < 4; y++){
		for(int x = 0; x < 4; x++){
			cout << pattern[y][x] << " ";
		}
		cout << endl;
	}
}

int GameManager::manhattanDistance(int id, vector<vector<int>> pattern){
	//Calculates manhattanDistance for id from pattern and CPTRN
	Point p1 = findMatrixPos(id, pattern);
	Point p2 = findMatrixPos(id, CPTRN);
	return abs(p1.x-p2.x) + abs(p1.y-p2.y);
}

Point GameManager::findMatrixPos(int id, vector<vector<int>> pattern){
	//Iterates over pattern looking for a point where id is located
	for   (int y = 0; y < 4; ++y){
		for (int x = 0; x < 4; ++x){
			if(id == pattern[y][x]){
				return Point(x,y);
			}
		}
	}
	//If no point is found, return -1,-1
	return Point(-1,-1);
}

string GameManager::loadHighScores(){
	//Based on difficulty, load separte file
	return "";
}

void GameManager::saveHighScores(string score){
	string loadedScores = loadHighScores();
	cout << "Saving score: " << score << endl;
	//split this into a vector based on '\n'
	//add our current score to the string
	//sort the vector by line score and insert new score appropriatly
	//Each line should look like this '999 userInitials'
	
}

void GameManager::showHighScores(){
	string loadedScores = loadHighScores();
	//add our current score to the string on a new line
	gameWin.setInstructionText(false, loadedScores);
}

void GameManager::showGameWindow(){
	gameWin.show();
}

void GameManager::showHint(){
	if(gameWin.showHint == shouldShowHint)return;
	shouldShowHint = gameWin.showHint;
	if(gameWin.showHint){
		string hintStr = "You should press "
		+ to_string(findBestPath())
		+ "\nPress hint again to close this dialog.";
		gameWin.setInstructionText(false, hintStr);
	}else gameWin.setInstructionText(true, "");
	
}


/*
//FIXME: link this function to the hint window;
//FIXME: Figure out how to display the value that this function returns in the hint window;
//FIXME: link this function to be able to pull the current gameboard pattern;
int GameManager::ManhattanDistance(){
	
	//Gets the current board pattern and finds where the blank tile is.
	gamePtrn = gameWin.getCurrentPattern();
	Point p = gameWin.findTile(0);
	
	//The following if case is if the blank tile can be swapped with four different choices.
	//All possible swaps are made and the sum of the remaining moves is calculated.
	if ((p.x == 1 && p.y == 1) || (p.x == 1 && p.y == 2) || (p.x == 2 && p.y == 1) || (p.x == 2 && p.y == 2)){
		
		int ManhattanSumTop = 0;
		int ManhattanSumRight = 0;
		int ManhattanSumDown = 0;
		int ManhattanSumLeft = 0;
		
		//Finds the sum after a top swap;
		Point pTop = {p.y-1,p.x};
		gameWin.swapTiles(p, pTop);
		for   (int y = 0; y < 4; ++y){
			for (int x = 0; x < 4; ++x){
				Point z = gameWin.findTile(CPTRN[x][y]);
				if(Point(y,x) != gameWin.btns[z.y][z.x].location){
					ManhattanSumTop += (abs(y - z.y) + abs(x - z.x));
				}
			}
		}
		gameWin.swapTiles(pTop, p);
		
		
		//Finds the sum after a right swap;
		Point pRight = {p.y,p.x+1};
		gameWin.swapTiles(p, pRight);
		for   (int y = 0; y < 4; ++y){
			for (int x = 0; x < 4; ++x){
				Point z = gameWin.findTile(CPTRN[x][y]);
				if(Point(y,x) != gameWin.btns[z.y][z.x].location){
					ManhattanSumRight += abs(y - z.y) + abs(x - z.x);
				}
			}
		}
		gameWin.swapTiles(pRight, p);
		
		//Finds the sum after a bottom swap;
		Point pDown = {p.y+1,p.x};
		gameWin.swapTiles(p, pDown);
		for   (int y = 0; y < 4; ++y){
			for (int x = 0; x < 4; ++x){
				Point z = gameWin.findTile(CPTRN[x][y]);
				if(Point(y,x) != gameWin.btns[z.y][z.x].location){
					ManhattanSumDown += abs(y - z.y) + abs(x - z.x);
				}
			}
		}
		gameWin.swapTiles(pDown, p);
		
		//Finds the sum after a left swap;
		Point pLeft = {p.y,p.x-1};
		gameWin.swapTiles(p, pLeft);
		for   (int y = 0; y < 4; ++y){
			for (int x = 0; x < 4; ++x){
				Point z = gameWin.findTile(CPTRN[x][y]);
				if(Point(y,x) != gameWin.btns[z.y][z.x].location){
					ManhattanSumLeft += abs(y - z.y) + abs(x - z.x);
				}
			}
		}
		gameWin.swapTiles(pLeft, p);
		
		//Finds which sum is the least and returns the ID of the tile which belongs to the swap;
		if ((ManhattanSumTop <= ManhattanSumDown) && (ManhattanSumTop <= ManhattanSumLeft) && (ManhattanSumTop <= ManhattanSumRight)){
			return gameWin.btns[pTop.x][pTop.y].tileID;
		}
		
		if ((ManhattanSumRight <= ManhattanSumDown) && (ManhattanSumRight <= ManhattanSumLeft) && (ManhattanSumRight <= ManhattanSumTop)){
			return gameWin.btns[pRight.x][pRight.y].tileID;
		}
		
		if ((ManhattanSumDown <= ManhattanSumLeft) && (ManhattanSumDown <= ManhattanSumTop) && (ManhattanSumDown <= ManhattanSumRight)){
			return gameWin.btns[pDown.x][pDown.y].tileID;
		}
		
		if ((ManhattanSumLeft <= ManhattanSumTop) && (ManhattanSumLeft <= ManhattanSumRight) && (ManhattanSumLeft <= ManhattanSumDown)){
			return gameWin.btns[pLeft.x][pLeft.y].tileID;
		}
	
	}
	
	//The following if case covers the cases where there are three different possible swaps;
	if ((p.x == 1 && p.y == 0) || (p.x == 2 && p.y == 0) || (p.x == 0 && p.y == 1) || (p.x == 3 && p.y == 1) || (p.x == 0 && p.y == 2) || (p.x == 3 && p.y == 2) || (p.x == 1 && p.y == 3) || (p.x == 2 && p.y == 3)){
		
		//If the blank tile is in the top row;
		if ((p.x == 1 && p.y == 0) || (p.x == 2 && p.y == 0)){
			
			int ManhattanSumRight = 0;
			int ManhattanSumDown = 0;
			int ManhattanSumLeft = 0;
			
			Point pRight = {p.y,p.x+1};
			gameWin.swapTiles(p, pRight);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
				Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumRight += abs(y - z.y) + abs(x - z.x);
					}
				}
			}
			gameWin.swapTiles(pRight, p);
			
			Point pDown = {p.y+1,p.x};
			gameWin.swapTiles(p, pDown);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
					Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumDown += abs(y - z.y) + abs(x - z.x);
					}
				}
			}
			gameWin.swapTiles(pDown, p);
			
			Point pLeft = {p.y,p.x-1};
			gameWin.swapTiles(p, pLeft);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
					Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumLeft += abs(y - z.y) + abs(x - z.x);
					}
				}
			}
			gameWin.swapTiles(pLeft, p);
			
			if ((ManhattanSumRight <= ManhattanSumDown) && (ManhattanSumRight <= ManhattanSumLeft)){
				return gameWin.btns[pRight.x][pRight.y].tileID;
			} 
			
			if ((ManhattanSumDown <= ManhattanSumRight) && (ManhattanSumDown <= ManhattanSumLeft)){
				return gameWin.btns[pDown.x][pDown.y].tileID;
			}
			
			if ((ManhattanSumLeft <= ManhattanSumRight) && (ManhattanSumLeft <= ManhattanSumDown)){
				return gameWin.btns[pLeft.x][pLeft.y].tileID;
			}
		}
		
		//if the blank tile is in the right column;
		if ((p.x == 3 && p.y == 2) || (p.x == 3 && p.y == 1)){
			
			int ManhattanSumTop = 0;
			int ManhattanSumDown = 0;
			int ManhattanSumLeft = 0;
			
			Point pTop = {p.y-1,p.x};
			gameWin.swapTiles(p, pTop);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
					Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumTop += (abs(y - z.y) + abs(x - z.x));
					}
				}
			}
			gameWin.swapTiles(pTop, p);
			
			Point pDown = {p.y+1,p.x};
			gameWin.swapTiles(p, pDown);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
					Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumDown += abs(y - z.y) + abs(x - z.x);
					}
				}
			}
			gameWin.swapTiles(pDown, p);
			
			Point pLeft = {p.y,p.x-1};
			gameWin.swapTiles(p, pLeft);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
					Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumLeft += abs(y - z.y) + abs(x - z.x);
					}
				}
			}
			gameWin.swapTiles(pLeft, p);
			
			if ((ManhattanSumTop <= ManhattanSumDown) && (ManhattanSumTop <= ManhattanSumLeft)){
				return gameWin.btns[pTop.x][pTop.y].tileID;
			}
			
			if ((ManhattanSumLeft <= ManhattanSumTop) && (ManhattanSumLeft <= ManhattanSumDown)){
				return gameWin.btns[pLeft.x][pLeft.y].tileID;
			}
			
			if ((ManhattanSumDown <= ManhattanSumLeft) && (ManhattanSumDown <= ManhattanSumTop)){
				return gameWin.btns[pDown.x][pDown.y].tileID;
			}
		}
		
		//If the blank tile is in the bottom row;
		if ((p.x == 1 && p.y == 3) || (p.x == 2 && p.y == 3)){
		
			int ManhattanSumTop = 0;
			int ManhattanSumRight = 0;
			int ManhattanSumLeft = 0;
			
			Point pTop = {p.y-1,p.x};
			gameWin.swapTiles(p, pTop);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
					Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumTop += (abs(y - z.y) + abs(x - z.x));
					}
				}
			}
			gameWin.swapTiles(pTop, p);
			
			Point pRight = {p.y,p.x+1};
			gameWin.swapTiles(p, pRight);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
				Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumRight += abs(y - z.y) + abs(x - z.x);
					}
				}
			}
			gameWin.swapTiles(pRight, p);
			
			Point pLeft = {p.y,p.x-1};
			gameWin.swapTiles(p, pLeft);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
					Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumLeft += abs(y - z.y) + abs(x - z.x);
					}
				}
			}
			gameWin.swapTiles(pLeft, p);
		
			if ((ManhattanSumTop <= ManhattanSumRight) && (ManhattanSumTop <= ManhattanSumLeft)){
				return gameWin.btns[pTop.x][pTop.y].tileID;
			}
			
			if ((ManhattanSumRight <= ManhattanSumTop) && (ManhattanSumRight <= ManhattanSumLeft)){
				return gameWin.btns[pRight.x][pRight.y].tileID;
			}

			if ((ManhattanSumLeft <= ManhattanSumTop) && (ManhattanSumLeft <= ManhattanSumRight)){
				return gameWin.btns[pLeft.x][pLeft.y].tileID;
			}
		}

		//If the blank is in the leftmost column;
		if ((p.x == 0 && p.y == 1) || (p.x == 0 && p.y == 2)){
			
			int ManhattanSumTop = 0;
			int ManhattanSumRight = 0;
			int ManhattanSumDown = 0;
			
			Point pTop = {p.y-1,p.x};
			gameWin.swapTiles(p, pTop);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
					Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumTop += (abs(y - z.y) + abs(x - z.x));
					}
				}
			}
			gameWin.swapTiles(pTop, p);
			
			Point pRight = {p.y,p.x+1};
			gameWin.swapTiles(p, pRight);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
				Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumRight += abs(y - z.y) + abs(x - z.x);
					}
				}
			}
			gameWin.swapTiles(pRight, p);
			
			Point pDown = {p.y+1,p.x};
			gameWin.swapTiles(p, pDown);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
					Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumDown += abs(y - z.y) + abs(x - z.x);
					}
				}
			}
			gameWin.swapTiles(pDown, p);
			
			if ((ManhattanSumTop <= ManhattanSumRight) && (ManhattanSumTop <= ManhattanSumDown)){
				return gameWin.btns[pTop.x][pTop.y].tileID;
			}
			
			if ((ManhattanSumRight <= ManhattanSumTop) && (ManhattanSumRight <= ManhattanSumDown)){
				return gameWin.btns[pRight.x][pRight.y].tileID;
			}
			
			if ((ManhattanSumDown <= ManhattanSumTop) && (ManhattanSumDown <= ManhattanSumRight)){
				return gameWin.btns[pDown.x][pDown.y].tileID;
			}
			
		}
		
	}
	
	//The following covers the case where there are two possible swaps;
	if ((p.x == 0 && p.y == 0) || (p.x == 3 && p.y == 0) || (p.x == 0 && p.y == 3) || (p.x == 3 && p.y ==3)){
		
		//If the blank is in the top left corner;
		if (p.x == 0 && p.y == 0){
			
			int ManhattanSumRight = 0;
			int ManhattanSumDown = 0;
			
			Point pRight = {p.y,p.x+1};
			gameWin.swapTiles(p, pRight);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
				Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumRight += abs(y - z.y) + abs(x - z.x);
					}
				}
			}
			gameWin.swapTiles(pRight, p);
			
			Point pDown = {p.y+1,p.x};
			gameWin.swapTiles(p, pDown);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
					Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumDown += abs(y - z.y) + abs(x - z.x);
					}
				}
			}
			gameWin.swapTiles(pDown, p);
			
			if (ManhattanSumRight <= ManhattanSumDown){
				return gameWin.btns[pRight.x][pRight.y].tileID;
			}
			else {
				return gameWin.btns[pDown.x][pDown.y].tileID;
			}
		}
		
		//If the blank is in the top right corner;
		if (p.x == 3 && p.y == 0){
			
			int ManhattanSumLeft = 0;
			int ManhattanSumDown = 0;
			
			Point pDown = {p.y+1,p.x};
			gameWin.swapTiles(p, pDown);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
					Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumDown += abs(y - z.y) + abs(x - z.x);
					}
				}
			}
			gameWin.swapTiles(pDown, p);
			
			Point pLeft = {p.y,p.x-1};
			gameWin.swapTiles(p, pLeft);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
					Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumLeft += abs(y - z.y) + abs(x - z.x);
					}
				}
			}
			gameWin.swapTiles(pLeft, p);
			
			if (ManhattanSumDown <= ManhattanSumLeft){
				return gameWin.btns[pDown.x][pDown.y].tileID;
			}
			else {
				return gameWin.btns[pLeft.x][pLeft.y].tileID;
			}
		}
		
		//If the blank is in the bottom right corner;
		if (p.x == 3 && p.y == 3){
			
			int ManhattanSumTop = 0;
			int ManhattanSumLeft = 0;
			
			Point pLeft = {p.y,p.x-1};
			gameWin.swapTiles(p, pLeft);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
					Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumLeft += abs(y - z.y) + abs(x - z.x);
					}
				}
			}
			gameWin.swapTiles(pLeft, p);
			
			Point pTop = {p.y-1,p.x};
			gameWin.swapTiles(p, pTop);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
					Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumTop += (abs(y - z.y) + abs(x - z.x));
					}
				}
			}
			gameWin.swapTiles(pTop, p);
			
			if (ManhattanSumTop <= ManhattanSumLeft){
				return gameWin.btns[pTop.x][pTop.y].tileID;
			}
			else {
				return gameWin.btns[pLeft.x][pLeft.y].tileID;
			}
			
		}
		
		//If the blank is in the bottom left;
		if (p.x == 0 && p.y == 3){
			
			int ManhattanSumTop = 0;
			int ManhattanSumRight = 0;
			
			Point pTop = {p.y-1,p.x};
			gameWin.swapTiles(p, pTop);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
					Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumTop += (abs(y - z.y) + abs(x - z.x));
					}
				}
			}
			gameWin.swapTiles(pTop, p);
			
			Point pRight = {p.y,p.x+1};
			gameWin.swapTiles(p, pRight);
			for   (int y = 0; y < 4; ++y){
				for (int x = 0; x < 4; ++x){
				Point z = gameWin.findTile(CPTRN[x][y]);
					if(Point(y,x) != gameWin.btns[z.y][z.x].location){
						ManhattanSumRight += abs(y - z.y) + abs(x - z.x);
					}
				}
			}
			gameWin.swapTiles(pRight, p);
			
			if (ManhattanSumTop <= ManhattanSumRight){
				return gameWin.btns[pTop.x][pTop.y].tileID;
			}
			else {
				return gameWin.btns[pRight.x][pRight.y].tileID;
			}
			
		}
		
	}
	
	//The function returns the ID of the tile that is to be recommended.
	
}


*/



