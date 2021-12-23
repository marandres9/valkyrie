#ifndef APP_FRAME_HPP
#define APP_FRAME_HPP

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/textctrl.h>

#include "MainList.hpp"
#include "AddItemDialog.hpp"

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

	// list controls
	Item* getHead() const;
	void populateStock();
	void addListItem (Item *item);
	void populateList(Item* listHead);
	
private:
	// declaracion de los miembros
	MainList *mainListView;
	AddItemDialog *addItemDialog;	
	Item* head;

	// sorting
	void sortByColumn(int col);
	static int compareValues(unsigned int u1, unsigned int u2, int uirection);
	static int compareValues(float f1, float f2, int direction);
	static int IDSortCallBack(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
	static int stockSortCallBack(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
	static int priceSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
	int sortDirection = 1;

	// evt handlers
	void onAddItemButton(wxCommandEvent &evt);

	wxDECLARE_EVENT_TABLE();
};

#endif