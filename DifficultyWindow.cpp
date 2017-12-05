//DifficultyWindow.cpp
#include <iostream>
#include <sstream>
#include "Graph.h"
#include "GUI.h"
#include "Window.h"
#include "DifficultyWindow.h"
using namespace Graph_lib;
using namespace std;

DifficultyWindow::DifficultyWindow(Point xy, int w, int h, const string& title)
   :Window{xy,w,h,title},
    header(Point{(x_max()-btnW)/2-50, 25}, "Pick a difficulty"),
    beginnerBtn(Point{(x_max()-btnW)/2,1*(btnH+btnSpacing) }, btnW, btnH, "Beginner",   	cb_beginner),
	intermedBtn(Point{(x_max()-btnW)/2,2*(btnH+btnSpacing) }, btnW, btnH, "Intermediate",	cb_intermediate),
    advancedBtn(Point{(x_max()-btnW)/2,3*(btnH+btnSpacing) }, btnW, btnH, "Advanced",		cb_advanced),
    expertBtn  (Point{(x_max()-btnW)/2,4*(btnH+btnSpacing) }, btnW, btnH, "Expert", 		cb_expert),
	quit_button(Point{0,y_max()-btnH}, x_max(), btnH, "Quit", cb_quit)
   {
	//Attach objs
	attach(header);
	attach(beginnerBtn);
	attach(intermedBtn);
	attach(advancedBtn);
	attach(expertBtn);
	attach(quit_button);
   }

GameManager::Difficulty DifficultyWindow::getDifficulty(){
	//Creates a difficulty window and outputs a difficulty depending on the button pressed
	DifficultyWindow win(Point(0,0), 225, 260, "Difficulty");
	while(win.shouldWait)Fl::wait();
	win.hide();
	win.shouldWait = false;
	return win.difficulty;
}
   
   
void DifficultyWindow::cb_quit(Address, Address pw){  
   reference_to<DifficultyWindow>(pw).quit();
} 
void DifficultyWindow::quit(){
	//Quits the program if 'quit' is pressed
	hide();
	shouldWait = false;
	exit(0);
}

//Callbacks and functions that return different difficulties depending on the btn pressed
void DifficultyWindow::cb_beginner(Address, Address pw){  
   reference_to<DifficultyWindow>(pw).beginner();
} 
void DifficultyWindow::beginner(){
	difficulty = GameManager::Difficulty::Beginner;
	shouldWait = false;
	cout << "Difficulty: Beginner" << endl;
}

void DifficultyWindow::cb_intermediate(Address, Address pw){  
   reference_to<DifficultyWindow>(pw).intermediate();
} 
void DifficultyWindow::intermediate(){
	difficulty = GameManager::Difficulty::Intermediate;
	shouldWait = false;
	cout << "Difficulty: Intermediate" << endl;
}

void DifficultyWindow::cb_advanced(Address, Address pw){  
   reference_to<DifficultyWindow>(pw).advanced();
} 
void DifficultyWindow::advanced(){
	difficulty = GameManager::Difficulty::Advanced;
	shouldWait = false;
   cout << "Difficulty: Advanced" << endl;
}

void DifficultyWindow::cb_expert(Address, Address pw){  
   reference_to<DifficultyWindow>(pw).expert();
} 
void DifficultyWindow::expert(){
	difficulty = GameManager::Difficulty::Expert;
	shouldWait = false;
   cout << "Difficulty: Expert" << endl;
}