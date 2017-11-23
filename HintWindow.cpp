#include <iostream>
#include <sstream>
#include "Graph.h"
#include "GUI.h"
#include "Window.h"
#include "HintWindow.h"
using namespace Graph_lib;
using namespace std;

HintWindow::HintWindow(Point xy, int movesLeft)
   :Window(xy,250,100,"Hint"),
	closeBtn(Point(0,y_max()-btnH), x_max(), btnH, "Close", cb_close)
	{
		attach(closeBtn);	
	}

void HintWindow::createWin(int numMovesLeft){
	HintWindow win(Point(0,0), numMovesLeft);
	win.show();
}
	
void HintWindow::cb_close(Address, Address pw){  
   reference_to<HintWindow>(pw).close();
} 
void HintWindow::close(){
   hide();
}









