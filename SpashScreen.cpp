#include "SplashScreen.h"
#include <ctime>
void SplashScreen::cb_start(Address, Address pw)
{
	reference_to<SplashScreen>(pw).button_pushed = true;
}

SplashScreen::SplashScreen(Point xy, const string& title)
	:Window(xy,500,450,title),
	game_title {Point{10,70},"Puzzle Game!"},
	team_name {Point{130,120}, "Team 18"},
	teammates {Point{20,160}, "Elijah, Bear, Dawson, Michael"},
	start_button(Point(10,310),150,120, "Start", cb_start),
	filenames {"board1.jpg","board2.jpg","board3.jpg","board4.jpg","board5.jpg","board6.jpg","board7.jpg","board8.jpg","board9.jpg","board10.jpg","board11.jpg"}
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

int SplashScreen::dont_wait_for_button(){
    time_t startTime = Time(NULL);
	time_t endTime = startTime;
	show();
    button_pushed = false;
    while(true){
		cout << "test " << difftime(endTime,startTime)<< endl;
	if(button_pushed)
	{
	hide();
	return 12;
	}
	if(difftime(endTime,startTime)<-2){
	hide();
	return 1;
	}
	endTime = endTime + Time(NULL);
	cout << endTime << endl;
	}
    return button_pushed;
}