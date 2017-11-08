#include "GUI.h"
#include "Window.h"
#include "Graph.h"
#include "Tile.h"
using namespace Graph_lib;
using namespace std;

namespace Board{
	void Tile::cb_OnClick(Address, Address pw){  
	   reference_to<Tile>(pw).OnClick();
	} 

	void Tile::OnClick(){
	   cout << "Index: " << tileID << endl;
	}

}