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
    beginnerBtn(Point{(x_max()-btnW)/2,1*(btnH+btnSpacing) }, btnW, btnH, "Beginner", 	cb_beginner),
	intermedBtn(Point{(x_max()-btnW)/2,2*(btnH+btnSpacing) }, btnW, btnH, "Intermediate",	cb_intermediate),
    advancedBtn(Point{(x_max()-btnW)/2,3*(btnH+btnSpacing) }, btnW, btnH, "Advanced",		cb_advanced),
    expertBtn  (Point{(x_max()-btnW)/2,4*(btnH+btnSpacing) }, btnW, btnH, "Expert", 		cb_expert),
	quit_button(Point{x_max()-btnW,0}	  ,  btnW, btnH, "Quit", 		cb_quit)
   {
	attach(beginnerBtn);
	attach(intermedBtn);
	attach(advancedBtn);
	attach(expertBtn);
	attach(quit_button);
   }

void DifficultyWindow::cb_quit(Address, Address pw){  
   reference_to<DifficultyWindow>(pw).quit();
} 
void DifficultyWindow::quit(){
   hide();
}

void DifficultyWindow::cb_beginner(Address, Address pw){  
   reference_to<DifficultyWindow>(pw).beginner();
} 
void DifficultyWindow::beginner(){
   cout << "Difficulty: Beginner" << endl;
}

void DifficultyWindow::cb_intermediate(Address, Address pw){  
   reference_to<DifficultyWindow>(pw).intermediate();
} 
void DifficultyWindow::intermediate(){
   cout << "Difficulty: Intermediate" << endl;
}

void DifficultyWindow::cb_advanced(Address, Address pw){  
   reference_to<DifficultyWindow>(pw).advanced();
} 
void DifficultyWindow::advanced(){
   cout << "Difficulty: Advanced" << endl;
}

void DifficultyWindow::cb_expert(Address, Address pw){  
   reference_to<DifficultyWindow>(pw).expert();
} 
void DifficultyWindow::expert(){
   cout << "Difficulty: Expert" << endl;
}