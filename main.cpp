#include <iostream>
#include <sstream>
#include "std_lib_facilities_5.h"
#include <FL/Fl.H>
#include "FL/Fl_JPEG_Image.H"
#include "SplashScreen.h"
//#include "GameManager.h"
#include "DifficultyWindow.h"



using namespace Graph_lib;
using namespace std;
int main(){
	SplashScreen splash(Point(0,0), "15Game");
	//loop for the GIF like display
	
	int i = 0;	
	while(i < 11){
		
		Image board_gif {Point{240,195},splash.filenames[i]};
		splash.attach(board_gif);
		i = i + splash.dont_wait_for_button();
		if(i == 11)
			i = 0;
	}
	
	splash.wait_for_button();
	GameManager gm(DifficultyWindow::getDifficulty());
	gm.checkWinState();
	gm.showGameWindow();
	while(Fl::wait()){
		if(gm.checkWinState()){
			//Scoreboard stuff and game win state
			//C++ 17 feature 'u8' gives the string "Game Over" values from UTF-8 
			cout << u8"Game Over" << endl;
			gm.showHighScores();
			break;
		}else gm.showHint();
		
	}
	
	
	return gui_main();
}
