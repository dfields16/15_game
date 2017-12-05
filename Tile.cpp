//Tile.cpp
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include "Tile.h"
#include "Graph.h"
using namespace std;

namespace Graph_lib{
	//Callback for Tile
	void Tile::cb_OnClick(Address, Address pw){  
	   reference_to<Tile>(pw).OnClick();
	} 
	//Callback Function
	void Tile::OnClick(){
	   //cout << "ID:   " << tileID << endl;
	   //cout << "LOC: (" << location.x << ", " << location.y << ")" << endl;
	   if(enabled)beenPressed = true;
	   else beenPressed = false;
	} 
	//Attach Tile
	void Tile::attach(Window& win){
		pw = new Fl_Button(loc.x, loc.y, width, height, label.c_str());
		pw->callback(reinterpret_cast<Fl_Callback*>(do_it), this); // pass the Tile Object
		own = &win;
	}
	//SetColor
	void Tile::setColor(Fl_Color c){
		pw->color(c);
	}
	
	
}