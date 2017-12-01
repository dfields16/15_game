#include "GameManager.h"
#include <string.h>
#include <iostream>
#include <stdlib.h> 

using namespace std;
GameManager::GameManager(Difficulty d):
	difficulty(d),
	gamePtrn(BPTRN[0]),
	gameWin(Point(0,0), 425, 275, "15Game")
	{
		int patternID = rand() % 4;
		switch(difficulty){
			case Beginner:
				gamePtrn = BPTRN[patternID];
				movesLeft = 10;
			break;
			case Intermediate:
				gamePtrn = IPTRN[patternID];
				movesLeft = 20;
			break;
			case Advanced:
				gamePtrn = APTRN[patternID];
				movesLeft = 40;
			break;
			case Expert:
				gamePtrn = EPTRN[patternID];
				movesLeft = 80;
			break;
		}
		maxMoves = movesLeft;
		printMatrix(gamePtrn);
		gameWin.createButtons(gamePtrn);
		gameWin.setScore(movesLeft, false);
	}
	
bool GameManager::checkWinState(){
	//Check for board updates
	vector<vector<int>> tmp = gameWin.getCurrentPattern();
	if(gamePtrn != tmp){
		//if change, subtract a move and update gamePtrn
		gameWin.setScore(--movesLeft, false);
		gamePtrn = tmp;
		gameWin.setInstructionText(true);
		gameWin.showHint = false;
		prevID = gameWin.prevID;
		showHint();
	}
	//If moves are < 0, Game Over
	//Otherwise return checkBoardState
	if(movesLeft == 0){
		checkBoardState();
		gameWin.setScore(numCorrect*maxMoves, true);
		return true;
	}else return checkBoardState();
}

bool GameManager::checkBoardState(){
	//Updates the board's tiles making them green or red
	bool isCompleted = true; 
	numCorrect = 0;
	//Counts the number correct and determines if the game is completed
	for   (int y = 0; y < 4; ++y){
		for (int x = 0; x < 4; ++x){
			Point p = gameWin.findTile(CPTRN[x][y]);
			if(Point(y,x) == gameWin.btns[p.y][p.x].location){
				//if an incorrect tile is found, make it impossible to be completed
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
	gamePtrn = gameWin.getCurrentPattern();
	//Create vectors and matrices to determine the best path
	//each matrix upM downM... holds the swapped matrix
	vector<int> swapID(4,-1), pathLength(4,-1);
	vector<vector<int>>upM, downM, leftM, rightM;
	upM = createSwapMtrx	(gamePtrn, dUp, &swapID[0]);	//UP
	downM = createSwapMtrx  (gamePtrn, dDown, &swapID[1]);	//DOWN
	leftM = createSwapMtrx  (gamePtrn, dLeft, &swapID[2]);	//LEFT
	rightM = createSwapMtrx (gamePtrn, dRight, &swapID[3]);	//RIGHT
	//Compute pathLength by adding manhattanDistance for each possible path
	for(int i = (movesLeft==maxMoves)? 0:1; i < 16; ++i){
		if(upM   != CPTRN && swapID[0] != prevID)pathLength[0] += manhattanDistance(i, upM);	//UP
		if(downM != CPTRN && swapID[1] != prevID)pathLength[1] += manhattanDistance(i, downM);	//DOWN
		if(leftM != CPTRN && swapID[2] != prevID)pathLength[2] += manhattanDistance(i, leftM);	//LEFT
		if(rightM!= CPTRN && swapID[3] != prevID)pathLength[3] += manhattanDistance(i, rightM);//RIGHT
	}
	int min = 10000;
	//Set min to any possible value given; impossible values are <= 0
	for(int i = 0; i < 4; ++i){if(pathLength[i] > 0)min = pathLength[i];break;}
	int returnNum = swapID[0];
	//Determine smallest pathLength and set returnNum to the smallest
	//corresponding swapID value
	for(int i = 0; i < 4; ++i){
		if(min > pathLength[i] && pathLength[i] != -1){
			min = pathLength[i];
			returnNum = swapID[i];
		}	
	}return returnNum;
}

vector<vector<int>> GameManager::createSwapMtrx(vector<vector<int>> pattern, Direction dir, int* id){
	vector<vector<int>> rMatrix = pattern;
	Point pZero = findMatrixPos(0,  pattern);
	//Depending on swap direction create a new matrix by swapping values if possible
	//Otherwise, return CPTRN
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
	//Sets *id to the non-zero value located at point p1 or p2
	if(pattern[p1.y][p1.x] == 0) *id = pattern[p2.y][p2.x];
	else if(pattern[p2.y][p2.x] == 0) *id = pattern[p1.y][p1.x];
	//Swaps number position in matrix
	int tmp = pattern[p1.y][p1.x];
	pattern[p1.y][p1.x] = pattern[p2.y][p2.x];
	pattern[p2.y][p2.x] = tmp;
	return pattern;
}

void GameManager::printMatrix(vector<vector<int>> pattern){
	//Print a matrix
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
	string fileLoc = "";
	switch(difficulty){
			case Beginner:
				fileLoc = "bScores.txt";
			break;
			case Intermediate:
				fileLoc = "iScores.txt";
			break;
			case Advanced:
				fileLoc = "aScores.txt";
			break;
			case Expert:
				fileLoc = "eScores.txt";
			break;
	}
	//Load text
	ifstream ist {fileLoc};
	if (!ist) error("can't open input file ", "data.txt");
	string data = "";
	string tScore,tInit = "";
	if(ist.good())ist >> tScore >> tInit;
	data += tScore + " " + tInit;
	while(ist.good()){
		ist >> tScore >> tInit;
		data += "\n" + tScore + " " + tInit;
	}
	ist.close();
	cout << data << endl;
	return data;
}

void GameManager::saveHighScores(string score){
	//add our current score to the string
	string loadedScores = loadHighScores();
	loadedScores = score + "\n" + loadedScores;
	//split this into a vector based on '\n'
	vector<string>scores;
	string delimiter = "\n";
	size_t pos = 0;
	while ((pos = loadedScores.find(delimiter)) != string::npos) {
		scores.push_back(loadedScores.substr(0, pos));
		loadedScores.erase(0, pos + delimiter.length());
	}
	//Sort vector
	sort (scores.begin(), scores.end(), [](const string &lhs, const string &rhs){
		stringstream ls, rs;
		ls << lhs;
		rs << rhs;
		int l; ls >> l;
		int r; rs >> r;
		cout << "BS: " << l << " " << r << endl;
		return l > r;
	}); 
	saveTxt(scores);
}

void GameManager::saveTxt(vector<string> out){
	//Based on difficulty, save separte file
	string fileLoc = "";
	switch(difficulty){
			case Beginner:
				fileLoc = "bScores.txt";
			break;
			case Intermediate:
				fileLoc = "iScores.txt";
			break;
			case Advanced:
				fileLoc = "aScores.txt";
			break;
			case Expert:
				fileLoc = "eScores.txt";
			break;
	}
	//Save txt
	ofstream ost {fileLoc};
	if (!ost) error("can't open output file ", fileLoc);
	for(int i = 0; i < out.size(); ++i){
		ost << out[i] << endl;
	}
	ost.close();
}

void GameManager::showHighScores(){
	if(gameWin.getInitialTxt() != "")saveHighScores(to_string(numCorrect*maxMoves) + " " + gameWin.getInitialTxt());
	//add our current score to the string on a new line
	gameWin.setInstructionText(false, "High Scores: \n" + loadHighScores());
	gameWin.onGameOver();
}

void GameManager::showGameWindow(){
	gameWin.show();
}

void GameManager::showHint(){
	//Checks to see if it should show hint based on GameWindow's showHint
	if(gameWin.showHint == shouldShowHint)return;
	shouldShowHint = gameWin.showHint;
	//if true, shows hint with the string hintStr,
	//Otherwise sets it to the default string
	if(gameWin.showHint){
		//C++ 11 feature 'auto'
		auto hintStr = "You should press "
		+ to_string(findBestPath())
		+ "\nPress hint or any tile to close this dialog.";
		gameWin.setInstructionText(false, hintStr);
	}else gameWin.setInstructionText(true);
	
}

bool GameManager::playAgain(){
	if(gameWin.playAgain == shouldReset)return false;
	shouldReset = gameWin.playAgain;
	if(shouldReset)gameWin.hide();
	return shouldReset;
	
}