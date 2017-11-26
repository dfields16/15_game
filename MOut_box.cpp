#include "MOut_box.h"
#include <FL/Fl.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include "Graph.h"

namespace Graph_lib{
	
	void MOut_box::put(const string& s)	{		
		Fl_Text_Buffer *buff = new Fl_Text_Buffer();
		buff->text(s.c_str());
		delete(reference_to<Fl_Text_Display>(pw).buffer());
		reference_to<Fl_Text_Display>(pw).buffer(buff);
	}

	void MOut_box::attach(Window& win){
		pw = new Fl_Text_Display(loc.x, loc.y, width, height, label.c_str());
		reference_to<Fl_Text_Display>(pw).wrap_mode(1,0);
		own = &win;
	}
	
	
}