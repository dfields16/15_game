#include <iostream>
#include <sstream>
#include "Graph.h"
#include "GUI.h"
#include "Window.h"
#include "HintWindow.h"
using namespace Graph_lib;
using namespace std;

HintWindow::HintWindow(Point xy, int w, int h, const string& title, int numMoves)
   :Window(xy, w, h, title),
	quit_button(Point{x_max()/2-x_max()/4,y_max()-35}, x_max()/2, 25, "Quit", cb_quit),
	numMovesLeft(numMoves)
   {
	attach(quit_button);
	
	}

void HintWindow::createWin(int numMoves){
	HintWindow win(Point(0,0), 350, 200, "Hint", numMoves);
	while(win.shouldWait)Fl::wait();
	win.quit();
}
   
   
void HintWindow::cb_quit(Address, Address pw){  
   reference_to<HintWindow>(pw).quit();
} 
void HintWindow::quit(){
	shouldWait = false;
}
