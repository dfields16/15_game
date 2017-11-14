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
	quit_button(Point{0,y_max()-btnW}, x_max(), btnH, "Quit", cb_quit)
	{
	attach(quit_button);
	for   (int y = 0; y < 4; ++y){
		for (int x = 0; x < 4; ++x){
			btns.push_back(new Tile(Point(x*btnW, y*btnH) , btnW, btnH, to_string(btns.size()+1), btns.size()+1, Point(x,y)));
		}
	}
	for (int i = 0; i<btns.size(); ++i){
		attach(btns[i]);
	}
}

void GameWindow::cb_quit(Address, Address pw){  
   reference_to<GameWindow>(pw).quit();
} 
void GameWindow::quit(){
   hide();
}
