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
	quitBtn(Point{x_max()/2,y_max()-btnW}, x_max()/2, btnH, "Quit", cb_quit),
	hintBtn(Point{0,y_max()-btnW}, x_max()/2, btnH, "Hint", cb_hint)
	{
	attach(quitBtn);
	attach(hintBtn);
	
	hide();
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
   cout << "Hint" << endl;
}


void GameWindow::showGameWindow(){
	show();
}

vector<vector<int>> GameWindow::getCurrentPattern(){
	vector<vector<int>> ptrn(4, vector<int>(4));
	for   (int y = 0; y < 4; ++y){
		for (int x = 0; x < 4; ++x){
			ptrn[btns[x][y].location.x][btns[x][y].location.y] = btns[x][y].tileID;
		}
	}
	
	return ptrn;
}

void GameWindow::createButtons(vector<vector<int>> pattern){
	for   (int y = 0; y < 4; ++y){
		for (int x = 0; x < 4; ++x){
			btns[y].push_back(new Tile(Point(x*btnW, y*btnH) , btnW, btnH, to_string(pattern[x][y]), pattern[x][y], Point(x,y)));
		}
	}
	for   (int y = 0; y < 4; ++y){
		for (int x = 0; x < 4; ++x){
			attach(btns[x][y]);
		}
	}
}




