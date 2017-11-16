#include <iostream>
#include <sstream>
#include "Graph.h"
#include "GUI.h"
#include "Window.h"
#include "Tile.h"
using namespace Graph_lib;
using namespace std;
struct GameWindow : Graph_lib::Window {
   GameWindow(Point xy, int w, int h, const string& title, vector<vector<int>>);
private:
//Button Stuff
   int btnW = 50;
   int btnH = 50;
   int btnSpacing = 0;
   Vector_ref<Tile> btns;
   //quit btn
   Button quitBtn;
   static void cb_quit(Address, Address);
   void quit();
   //hint btn
   Button hintBtn;
   static void cb_hint(Address, Address);
   void hint();
public:
	void showGameWindow();
	vector<vector<int>> getCurrentPattern();
};

