#include <iostream>
#include <sstream>
#include "Graph.h"
#include "GUI.h"
#include "Window.h"
#include "Tile.h"
#include "HintWindow.h"
#include "MOut_box.h"

using namespace Graph_lib;
using namespace std;
struct GameWindow : Graph_lib::Window {
   GameWindow(Point xy, int w, int h, const string& title);
private:
//Button Stuff
   int btnW = 50;
   int btnH = 50;
   int btnSpacing = 0;
   //quit btn
   Button quitBtn;
   static void cb_quit(Address, Address);
   void quit();
   //hint btn
   Button hintBtn;
   static void cb_hint(Address, Address);
   void hint();
   void updateTiles();
   void checkAdjacentTiles(int x, int y);
   void swapTiles(Point t1, Point t2);
//Score & Instruction items
	Out_box scoreBox;
	string instrStr = "Instructions:\n1) The goal is to arrange as many tiles in the correct order as possible within the allotted amount of moves\n2) Click on a tile next to the blank one to swap its position\n3) ";
	MOut_box instrBox;
public:
	void showGameWindow();
	void createButtons(vector<vector<int>> pattern);
	void setScore(int score, bool isFinal);
	vector<vector<int>> getCurrentPattern();
	vector<Vector_ref<Tile>> btns{{Vector_ref<Tile>()},{Vector_ref<Tile>()},{Vector_ref<Tile>()},{Vector_ref<Tile>()}};
    Point findTile(Point loc);
	Point findTile(int id);
};

