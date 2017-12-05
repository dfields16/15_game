//DifficultyWindow.h
#include <iostream>
#include <sstream>
#include "Graph.h"
#include "GUI.h"
#include "Window.h"
#include "GameManager.h"
using namespace Graph_lib;
using namespace std;
struct DifficultyWindow : Graph_lib::Window {
   DifficultyWindow(Point xy, int w, int h, const string& title);
   static GameManager::Difficulty getDifficulty();
private:
//Labels
   Text header;
//Button sizes and spacing
   int btnW = 150;
   int btnH = 35;
   int btnSpacing = 10;
//Button Objects
   Button beginnerBtn;
   Button intermedBtn;
   Button advancedBtn;
   Button expertBtn;
   Button quit_button;
//Button Callbacks
   static void cb_beginner		(Address, Address);
   static void cb_intermediate	(Address, Address);
   static void cb_advanced		(Address, Address);
   static void cb_expert		(Address, Address);
   static void cb_quit			(Address, Address);
//Button Functions
   void quit();
   void beginner();
   void intermediate();
   void advanced();
   void expert();
   GameManager::Difficulty difficulty = GameManager::Difficulty::Beginner;
   bool shouldWait = true;
};

