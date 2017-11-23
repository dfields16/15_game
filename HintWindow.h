#include <iostream>
#include <sstream>
#include "Graph.h"
#include "GUI.h"
#include "Window.h"
#include "Tile.h"
using namespace Graph_lib;
using namespace std;
struct HintWindow : Graph_lib::Window {
   HintWindow(Point xy, int movesLeft);
   static void createWin(int numMovesLeft);
private:
	string instuctions = "1) Press stuff etc";
//Button Stuff
	int btnH = 50;
	//Close btn
	Button closeBtn;
	static void cb_close(Address, Address);
	void close();
public:
	void showHintWindow();
};

