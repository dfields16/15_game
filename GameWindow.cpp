#include <iostream>
#include <sstream>
#include "Graph.h"
#include "GUI.h"
#include "Window.h"
#include "GameWindow.h"
using namespace Graph_lib;
using namespace std;

GameWindow::GameWindow(Point xy, int w, int h, const string& title, vector<vector<int>> pattern)
   :Window{xy,w,h,title},
	quitBtn(Point{x_max()/2,y_max()-btnW}, x_max()/2, btnH, "Quit", cb_quit),
	hintBtn(Point{0,y_max()-btnW}, x_max()/2, btnH, "Hint", cb_hint)
	{
	attach(quitBtn);
	attach(hintBtn);
	for   (int y = 0; y < 4; ++y){
		for (int x = 0; x < 4; ++x){
			btns.push_back(new Tile(Point(x*btnW, y*btnH) , btnW, btnH, to_string(pattern[x][y]), pattern[x][y], Point(x,y)));
		}
	}
	for (int i = 0; i<btns.size(); ++i){
		attach(btns[i]);
	}
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
	for(int i = 0; i < btns.size(); ++i){
		ptrn[i/4][i%4] = btns[i].tileID;
	}
	return ptrn;
}






