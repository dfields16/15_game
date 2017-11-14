#include "GUI.h"
#include "Window.h"
#include "Point.h"
#include <FL/fl_draw.H>
//Added to namespace Graph_lib
namespace Graph_lib{
	struct Tile : Widget{
		public:
			int tileID;
			Point location;
			
			static void cb_OnClick(Address, Address);
			void OnClick();
			Tile(Point xy, int w, int h, const string& label, int id, Point loc)
				: Widget(xy,w,h,label,cb_OnClick),
				tileID(id), location(loc)
			{}
			
			void attach(Window&);
			
			void setColor(Fl_Color c);
	};

}