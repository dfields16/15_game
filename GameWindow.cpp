#include <iostream>
#include <sstream>
#include "Graph.h"
#include "GUI.h"
#include "Window.h"
#include "GameWindow.h"
using namespace Graph_lib;
using namespace std;

GameWindow::GameWindow(Point xy, int w, int h, const string& title)
   :Window{xy,w,h,title},
	quitBtn(Point{btnW*4,y_max()-btnW}, x_max()-btnW*4, btnH, "Quit", cb_quit),
	hintBtn(Point{0,y_max()-btnW}, btnW*4, btnH, "Hint", cb_hint),
	scoreBox(Point{0,0}, btnW*4, 25, "Moves left: 99"),
	initialBox(Point{btnW*4,0}, x_max()-btnW*4, 25, ""),
	instrBox(Point{btnW*4,25}, x_max()-btnW*4, btnH*4, "")
	{
	attach(quitBtn);
	attach(hintBtn);
	attach(scoreBox);
	attach(instrBox);
	attach(initialBox);
	instrStr = "Instructions:\n1) The goal is to arrange as many tiles in "
	 "the correct order as possible within the allotted amount of moves\n" 
	 "2) Click on a tile next to the blank one to swap its position\n"
	 "3) If a tile is green, it is in the correct position. Otherwise"
	 " it will be red and in the wrong position\n"
	 "If you need help press the hint button!";
	instrBox.put(instrStr);
	hide();
	}

void GameWindow::setScore(int score, bool isFinal){
	if(!isFinal)scoreBox.put("Moves left: " + to_string(score));
	else 		scoreBox.put("Final Score: " + to_string(score));
}

	
void GameWindow::cb_quit(Address, Address pw){  
   reference_to<GameWindow>(pw).quit();
} 
void GameWindow::quit(){
   hide();
}

void GameWindow::cb_hint(Address, Address pw){  
   reference_to<GameWindow>(pw).hint();
}

void GameWindow::hint(){
	showHint = !showHint;
}

vector<vector<int>> GameWindow::getCurrentPattern(){
	updateTiles();
	vector<vector<int>> ptrn(4, vector<int>(4));
	for   (int y = 0; y < 4; ++y){
		for (int x = 0; x < 4; ++x){
			Point p = findTile(x+y*4);
			ptrn[btns[p.y][p.x].location.y][btns[p.y][p.x].location.x] = btns[p.y][p.x].tileID;
		}
	}
	
	return ptrn;
}

void GameWindow::createButtons(vector<vector<int>> pattern){
	for   (int y = 0; y < 4; ++y){
		for (int x = 0; x < 4; ++x){
			if(pattern[x][y] == 0)
				 btns[y].push_back(new Tile(Point(x*btnW, y*btnH+25), btnW, btnH, "", pattern[y][x], Point(x,y)));
			else btns[y].push_back(new Tile(Point(x*btnW, y*btnH+25), btnW, btnH, to_string(pattern[y][x]), pattern[y][x], Point(x,y)));
		}
	}
	for   (int y = 0; y < 4; ++y){
		for (int x = 0; x < 4; ++x){
			attach(btns[x][y]);
		}
	}
}

void GameWindow::updateTiles(){
	for   (int y = 0; y < 4; ++y){
		for (int x = 0; x < 4; ++x){
			if(btns[x][y].beenPressed){
				btns[x][y].beenPressed = false;
				prevID = btns[x][y].tileID;
				checkAdjacentTiles(x,y);
			}
		}
	}
}

void GameWindow::checkAdjacentTiles(int x, int y){
	cout << "Tile Pressed\t("  << btns[x][y].location.x << ", " << btns[x][y].location.y << "): " << btns[x][y].tileID << endl;
	if((btns[x][y].location.x-1) >= 0){//Right exchange
		Point p = findTile(Point(btns[x][y].location.x-1,btns[x][y].location.y));
		//cout << "Tile Right\t("  << btns[p.y][p.x].location.x << ", " << btns[p.y][p.x].location.y << "): " << btns[p.y][p.x].tileID << endl;
		if(btns[p.y][p.x].tileID == 0){
			swapTiles(Point(x,y), Point(p.y,p.x));
			return;
		}
	}
	if((btns[x][y].location.x+1) <= 3){//Left exchange
		Point p = findTile(Point(btns[x][y].location.x+1,btns[x][y].location.y));
		//cout << "Tile Left\t("  << btns[p.y][p.x].location.x << ", " << btns[p.y][p.x].location.y << "): " << btns[p.y][p.x].tileID << endl;
		if(btns[p.y][p.x].tileID == 0){
			swapTiles(Point(x,y), Point(p.y,p.x));
			return;
		}
	}
	if((btns[x][y].location.y-1) >= 0){//Up exchange
		Point p = findTile(Point(btns[x][y].location.x,btns[x][y].location.y-1));
		//cout << "Tile Up\t\t("  << btns[p.y][p.x].location.x << ", " << btns[p.y][p.x].location.y << "): " << btns[p.y][p.x].tileID << endl;
		if(btns[p.y][p.x].tileID == 0){
			swapTiles(Point(x,y), Point(p.y,p.x));
			return;
		}
	}
	if((btns[x][y].location.y+1) <= 3){//Down exchange
		Point p = findTile(Point(btns[x][y].location.x,btns[x][y].location.y+1));
		//cout << "Tile Down\t("  << btns[p.y][p.x].location.x << ", " << btns[p.y][p.x].location.y << "): " << btns[p.y][p.x].tileID << endl;
		if(btns[p.y][p.x].tileID == 0){
			swapTiles(Point(x,y), Point(p.y,p.x));
			return;
		}
	}
}

void GameWindow::swapTiles(Point t1, Point t2){
	//Swap Indices
	Point p = btns[t1.x][t1.y].location;
	btns[t1.x][t1.y].location = btns[t2.x][t2.y].location;
	btns[t2.x][t2.y].location = p;
	//Swap Positions
	Point p1 = btns[t1.x][t1.y].loc;
	btns[t1.x][t1.y].move(btns[t2.x][t2.y].loc.x, btns[t2.x][t2.y].loc.y);
	btns[t2.x][t2.y].move(p1.x, p1.y);
}

Point GameWindow::findTile(Point loc){
	for   (int y = 0; y < 4; ++y){
		for (int x = 0; x < 4; ++x){
			if(btns[x][y].location == loc)return Point(y,x);
		}
	}
	return Point(-1,-1);
}

Point GameWindow::findTile(int id){
	for   (int y = 0; y < 4; ++y){
		for (int x = 0; x < 4; ++x){
			if(btns[x][y].tileID == id)return Point(y,x);
		}
	}
	return Point(-1,-1);
}

void GameWindow::setInstructionText(bool shouldReset, string txt = ""){
	if(shouldReset)instrBox.put(instrStr);
	else instrBox.put(txt);
}





