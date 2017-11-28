#include "GUI.h"
#include <FL/fl_draw.H>
#include "Window.h"
#include "Point.h"

namespace Graph_lib{
	
	struct MOut_box : Widget {
        MOut_box(Point xy, int w, int h, const string& s)
            :Widget(xy,w,h,s,0) { }
			
        void put(const string&);
        void attach(Window& win);
    };
	
}