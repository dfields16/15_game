#include "GameWindow.h"

struct GameManager{
private:
//CONSTANTS
//Format for game patterns
/*Complete*/	const vector<vector<int>> CPTRN = {{1,2,3,4},	{5,6,7,8}, 	 {9,10,11,12},{13,14,15,0}};
/*Beginner*/	const vector<vector<vector<int>>> BPTRN = { {{1,2,3,4},	{5,6,12,7},  {9,10,0,15}, {13,14,8,11}},
															{{5,1,2,4},	{9,7,3 ,8},  {0,6,10,11}, {13,14,15,12}},
															{{1,6,2,4},	{5,10,3,8},  {0,14,7,12}, {9,13,11,15}},
															{{5,1,2,3},	{6,7,11,4},  {9,10,0,8},  {13,14,15,12}}};
/*Intermediate*/const vector<vector<vector<int>>> IPTRN = { {{1,6,3,4},	{5,0,2,11},  {9,10,14,7}, {13,15,12,8}},
															{{1,7,8,2},	{6,3,4,12},  {5,14,10,15},{9,13,11,0}},
															{{1,3,4,8},	{9,2,12,0},  {11,7,5,6},  {13,10,14,15}},
															{{2,3,4,8},	{1,7,10,12}, {0,5,14,11}, {9,6,13,15}}};
/*Advanced*/	const vector<vector<vector<int>>> APTRN = { {{6,5,11,4},{10,13,2,1}, {9,15,7,3},  {14,12,8,0}},
															{{7,9,4,11},{1,5,3,8},   {10,13,14,0},{2,6,15,12}},
															{{11,7,4,3},{9,5,12,15}, {0,6,1,2},   {13,10,8,14}},
															{{4,8,12,15},{3,6,7,14}, {0,10,11,13},{2,1,5,9}}};
/*Expert*/		const vector<vector<vector<int>>> EPTRN = { {{0,12,11,13},{15,14,10,9},{3,7,6,2},   {4,8,5,1}},
															{{8,15,13,4}, {7,0,3,12},  {2,1,6,14},  {10,11,5,9}},
															{{10,15,0,2}, {6,14,11,2}, {13,1,12,8}, {5,9,4,3}},
															{{3,8,13,6},  {9,10,2,7},  {0,14,4,12}, {5,1,15,11}}};
	int prevID, movesLeft = -1;
	int maxMoves, numCorrect = 0;
	bool shouldShowHint = false;
	enum Direction{dUp,dDown,dLeft,dRight};
	vector<vector<int>> createSwapMtrx(vector<vector<int>> original, Direction dir, int* id);
	vector<vector<int>> swapIndices(vector<vector<int>> pattern, Point p1, Point p2, int* id);
	bool checkBoardState();
	void printMatrix(vector<vector<int>> pattern);
	string loadHighScores();
	int manhattanDistance(int id, vector<vector<int>> pattern);
	Point findMatrixPos(int id, vector<vector<int>> pattern);
	void saveTxt(vector<string> out);
	bool shouldReset = false;
public:
	enum Difficulty{Beginner,Intermediate,Advanced,Expert};
	Difficulty difficulty;
	GameManager(Difficulty d);
	vector<vector<int>> gamePtrn;
private: GameWindow gameWin;
public:			
	void showGameWindow();
	bool checkWinState();
	int findBestPath();
	void saveHighScores(string score);
	void showHighScores();
	void showHint();
	bool playAgain();
	bool shouldShowHS = true;
};