#include "SplashScreen.h"

void SplashScreen::cb_start(Address, Address pw)
{
	reference_to<SplashScreen>(pw).button_pushed = true;
}

SplashScreen::SplashScreen(Point xy, int w, int h, const string& title)
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

bool SplashScreen::wait_for_button(){
    show();
    button_pushed = false;
    while (!button_pushed) Fl::wait();
	hide();
    return button_pushed;
}