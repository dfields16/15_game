#include "GUI.h"
#include "Window.h"

//Added to namespace Graph_lib
namespace Graph_lib{
	struct Tile : Widget{
		public:
			int tileID;
			static void cb_OnClick(Address, Address);
			void OnClick();
			Tile(Point xy, int w, int h, const string& label, int id)
				: Widget(xy,w,h,label,cb_OnClick),
				tileID(id)
			{}
			
			void attach(Window&);
	};

}