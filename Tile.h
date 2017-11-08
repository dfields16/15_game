#include "GUI.h"
#include "Window.h"
#include "Graph.h"

using namespace Graph_lib;

namespace Board{
	struct Tile : Button{
		public:
			int tileID;
			static void cb_OnClick(Address, Address);
			void OnClick();
			Tile(Point xy, int w, int h, const string& label, int id)
				: tileID(id),
				Button(xy,w,h,label,cb_OnClick)
				
			{}
			
		
	};

}