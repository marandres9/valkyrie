#ifndef MAINLIST_HPP
#define MAINLIST_HPP

#include <wx/listctrl.h>
#include <iostream>

class MainList : public wxListView
{
public:
	MainList(wxWindow *parent,
			wxWindowID winid = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxLC_REPORT
			)
		: wxListView(parent, winid, pos, size, style)
	{
		this->AppendColumn("ID", wxLIST_FORMAT_CENTER, 100);
		this->AppendColumn("Name", wxLIST_FORMAT_CENTER, 500);
		this->AppendColumn("Stock", wxLIST_FORMAT_CENTER, 100);
		this->AppendColumn("Price", wxLIST_FORMAT_CENTER, 100);
	}
};

#endif