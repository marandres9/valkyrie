#include <wx/wx.h>
#include <wx/listctrl.h>

extern "C" {
	#include "stockControl/itemList.h"
}

class MainApp : public wxApp
{
public:
	bool OnInit();
};

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
};