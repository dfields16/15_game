#include <iostream>
#include <sstream>
#include "Graph.h"
#include "GUI.h"
#include "Window.h"
#include "Tile.h"
using namespace Graph_lib;
using namespace std;
struct GameWindow : Graph_lib::Window {
   GameWindow(Point xy, int w, int h, const string& title);
private:
//Button sizes and spacing
   int btnW = 50;
   int btnH = 50;
   int btnSpacing = 0;
//Button Objects
   Vector_ref<Tile> btns;
   Button quit_button;
//Button Callbacks
   static void cb_quit(Address, Address);
//Button Functions
   void quit();
};

