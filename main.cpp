#include <iostream>
#include <sstream>
#include "std_lib_facilities_5.h"
#include "FL/Fl_JPEG_Image.H"
#include "GameWindow.h"
#include "SplashScreen.h"
using namespace Graph_lib;
using namespace std;
int main(){
  //GameWindow gw(Point(100,100), 200, 250, "15Game");
  Puzzle_game win(Point(0,0),500,500,"puzzle game");
  return gui_main();
}

/*

Vector_ref<Tile>btns;
  vector<int> index;
  int numColsRows = 4;
  int width = 50;
  int k=0;
  Simple_window window(Point(100,200),width*numColsRows,width*numColsRows,"Test");
  for   (int y = 0; y < numColsRows; ++y){
    for (int x = 0; x < numColsRows; ++x){
      btns.push_back(new Tile(Point(x*width, y*width) , width, width, to_string(btns.size()+1), btns.size()+1, Point(x,y)));
      index.push_back(k++);
    }
  }
	for (int i = 0; i<btns.size(); ++i){
		window.attach(btns[i]);
	}

  window.wait_for_button();
  return 0;

*/
