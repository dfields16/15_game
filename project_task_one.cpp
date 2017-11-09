#include "std_lib_facilities_5.h"
#include "Simple_window.h"
#include "Graph.h"
#include "FL/Fl_JPEG_Image.h"

struct Puzzle_game:Graph_lib::Window
{
	Puzzle_game(Point xy, int w, int h, const string& title);
	Text game_title;
	Text team_name;
	Text teammates;
private:
	Button start_button;
	void start();
	static void cb_start(Address, Address window);
};

void Puzzle_game::start()
{
	hide();
}

void Puzzle_game::cb_start(Address, Address pw)
{
	reference_to<Puzzle_game>(pw).start();
}

Puzzle_game::Puzzle_game(Point xy, int w, int h, const string& title)
	:Window(xy,w,h,title),
	game_title {Point{10,70},"Puzzle Game!"},
	team_name {Point{130,170}, "Team 18"},
	teammates {Point{20,270}, "Elijah, Bear, Dawson, Michael"},
	start_button(Point(160,310),150,120, "Start", cb_start)
{
	game_title.set_color(Color::blue);
	game_title.set_font_size(70);
	team_name.set_color(Color::green);
	team_name.set_font_size(50);
	teammates.set_color(Color::red);
	teammates.set_font_size(30);
	attach(game_title);
	attach(team_name);
	attach(teammates);
	attach(start_button);
}

int main()
try{
	Puzzle_game win(Point(0,0),500,500,"puzzle game");
	
	return gui_main();
}
catch(exception& e){
	cerr<<"error: "<<e.what();
	keep_window_open();
	return 1;
}
catch(...){
	cerr<<"Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}