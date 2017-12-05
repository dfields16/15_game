//HintWindow.h
#include <iostream>
#include <sstream>
#include "Graph.h"
#include "GUI.h"
#include "Window.h"
using namespace Graph_lib;
using namespace std;
struct HintWindow : Graph_lib::Window {
   HintWindow(Point xy, int w, int h, const string& title, int numMoves);
   static void createWin(int numMoves);
private:
	bool shouldWait = true;
//Close Btn
   Button quit_button;
   static void cb_quit(Address, Address);
   void quit();
//Hint stuff
	int numMovesLeft;
	
};

