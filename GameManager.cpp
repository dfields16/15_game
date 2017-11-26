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






