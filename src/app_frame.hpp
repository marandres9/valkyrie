#ifndef APP_FRAME_HPP
#define APP_FRAME_HPP

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

	void addListItem (Item *item)
	{
		int index = this->GetItemCount();
	
		this->InsertItem(index, std::to_string(item->id));
		this->SetItem(index, 1, item->name);
		this->SetItem(index, 2, std::to_string(item->stock));
		this->SetItem(index, 3, std::to_string(item->price));

		this->SetItemData(index, (wxIntPtr) item);
	}
	void populateList(Item* listHead)
	{
		while(listHead != NULL)
		{
			addListItem(listHead);
			listHead = listHead->next;
		}
	}
};

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

	Item* getHead();
private:
	MainList *mainListView;

	Item* head;
	void populateStock();


	void sortByColumn(int col);
	static int compareValues(unsigned int u1, unsigned int u2, int uirection);
	static int compareValues(float f1, float f2, int direction);
	static int IDSortCallBack(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
	static int stockSortCallBack(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
	static int priceSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
	int sortDirection = 1;

};

#endif