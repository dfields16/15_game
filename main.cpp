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

void launchGame();

int main(){
	//Splash Screen
	SplashScreen splash(Point(0,0), "15Game");
	splash.wait_for_button();
	//Start Game
	launchGame();	
	return gui_main();
}

void launchGame(){
	//Game Manager
	GameManager gm(DifficultyWindow::getDifficulty());
	gm.checkWinState();
	gm.showGameWindow();
	while(Fl::wait()){
		if(gm.checkWinState()){
			if(!gm.playAgain()){
				//Scoreboard stuff and game win state
				//C++ 17 feature 'u8' gives the string "Game Over" values from UTF-8 
				if(gm.shouldShowHS){
					cout << u8"Game Over" << endl;
					gm.showHighScores();
					gm.shouldShowHS = false;
				}
			}else{
				launchGame();
				break;
			} 
		}else gm.showHint();
		
	}
}