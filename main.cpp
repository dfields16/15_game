#include <iostream>
#include <sstream>
#include "std_lib_facilities_5.h"
#include "FL/Fl_JPEG_Image.H"
#include "SplashScreen.h"
#include "GameManager.h"
using namespace Graph_lib;
using namespace std;
int main(){
  GameManager gm(GameManager::Difficulty::Intermediate);
  gm.checkWinState(false);
  gm.gameWin.showGameWindow();
  return gui_main();
}
