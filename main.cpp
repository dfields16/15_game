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
	splash.wait_for_button();
	GameManager gm(DifficultyWindow::getDifficulty());
	gm.checkWinState(false);
	gm.gameWin.showGameWindow();
	while(Fl::wait()){
		if(gm.checkWinState(false)){
			//Scoreboard stuff and game win state
			cout << "YOU WIN!!!!" << endl;
			
			break;
		}
		
	}
	
	
	return gui_main();
}
