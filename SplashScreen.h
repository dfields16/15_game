#include "std_lib_facilities_5.h"
#include "Simple_window.h"
#include "Graph.h"
#include "FL/Fl_JPEG_Image.h"

struct SplashScreen:Graph_lib::Window
{
	SplashScreen(Point xy, const string& title);
	bool wait_for_button();
//Text objs
	Text game_title;
	Text team_name;
	Text teammates;
	vector<string> filenames;
private:
	Button start_button;
	void start();
	static void cb_start(Address, Address window);
	bool button_pushed;
	Vector_ref<Image> gameImgs{};
	static void loopImgs();
};