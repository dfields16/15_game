#include "GameWindow.h"

struct GameManager{
	private:
	//CONSTANTS
		//Format for game patterns
		/*Complete*/	const vector<vector<int>> CPTRN = {{1,2,3,4},	{5,6,7,8}, 	 {9,10,11,12},{13,14,15,0}};
		/*Beginner*/	const vector<vector<int>> BPTRN = {{1,2,3,4},	{5,6,12,7},  {9,10,0,15}, {13,14,8,11}};
		/*Intermediate*/const vector<vector<int>> IPTRN = {{1,6,3,4},	{5,0,2,11},  {9,10,14,7}, {13,15,12,8}};
		/*Advanced*/	const vector<vector<int>> APTRN = {{6,5,11,4},	{10,13,2,1}, {9,15,7,3},  {14,12,8,0}};
		/*Expert*/		const vector<vector<int>> EPTRN = {{0,12,11,13},{15,14,10,9},{3,7,6,2},	  {4,8,5,1}};
		int movesLeft = -1;
		int maxMoves = 0;
		int numCorrect = 0;
		bool shouldShowHint = false;
		enum Direction{dUp,dDown,dLeft,dRight};
		vector<vector<int>> createSwapMtrx(vector<vector<int>> original, Direction dir, int* id);
		vector<vector<int>> swapIndices(vector<vector<int>> pattern, Point p1, Point p2, int* id);
		void printMatrix(vector<vector<int>> pattern);
		int prevID = -1;
	public:
		enum Difficulty{Beginner,Intermediate,Advanced,Expert};
		Difficulty difficulty;
		vector<vector<int>> gamePtrn;
		GameManager(Difficulty d);
		
		GameWindow gameWin;
			
		void showGameWindow();
		bool checkWinState();
		bool checkBoardState();
		int findBestPath();
		int manhattanDistance(int id, vector<vector<int>> pattern);
		Point findMatrixPos(int id, vector<vector<int>> pattern);
		string loadHighScores();
		void saveHighScores(string score);
		void showHighScores();
		void showHint();
		
};