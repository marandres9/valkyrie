#ifndef MAINLIST_HPP
#define MAINLIST_HPP

#include <iostream>
#include <wx/listctrl.h>

#include "ErrorBox.hpp"
#include "StockMovementPanel.hpp"

extern "C" {
	#include "linkedList/linkedList.h"
}

class MainList : public wxListView
{
public:
	MainList(wxWindow *parent,
			wxWindowID winid = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxLC_REPORT
			);

	// list controls
	Item* getHead() const;
	// parses listas.bin and loads list to memory
	void createListFromFile();
	// displays list items to listView
	void populateListView();
	// adds to LL and listView
	void addNewItem(unsigned int newID, const char *newName, unsigned int newStock, float newPrice);
	// adds to listView
	void addListViewItem (Item *item);
	// find_item() wrapper
	Item* findItem(uint itemID);
	// register_movement() wrapper
	bool registerMovement(uint itemID, int movement);
	// write_bin() & write_txt() wrapper
	void saveList();
	// delete item from memory, delete_item() wrapper
	void deleteItem();
	// deletes list from memory, delete_list() wrapper
	void freeList();

	void setSelectedItem(wxListEvent &evt);
	const wxString &getSelectedItemID() const;
	long getSelectedItemIndex() const;
	wxString getSelectedItemName() const;

private:
	// list head
	Item* head;

	wxString selectedItemID;
	long selectedItemIndex = 0;

	StockMovementPanel *stockMovementPanel;


	// sorting
	void sortByColumn(int col);
	static int compareValues(unsigned int u1, unsigned int u2, int uirection);
	static int compareValues(float f1, float f2, int direction);
	static int IDSortCallBack(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
	static int stockSortCallBack(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
	static int priceSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
	int sortDirection = 1;
};

#endif