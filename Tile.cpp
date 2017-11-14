#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include "Tile.h"
using namespace std;

namespace Graph_lib{
	//Callback for Tile
	void Tile::cb_OnClick(Address, Address pw){  
	   reference_to<Tile>(pw).OnClick();
	} 
	//Callback Function
	void Tile::OnClick(){
	   cout << "Index: " << tileID << endl;
	} 
	//Attach Tile
	void Tile::attach(Window& win){
		pw = new Fl_Button(loc.x, loc.y, width, height, label.c_str());
		pw->callback(reinterpret_cast<Fl_Callback*>(do_it), this); // pass the Tile Object
		own = &win;
	}
}