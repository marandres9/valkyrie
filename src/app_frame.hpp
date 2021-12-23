#ifndef APP_FRAME_HPP
#define APP_FRAME_HPP

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/textctrl.h>

#include "mainList.hpp"

extern "C" {
	#include "stockControl/itemList.h"
}

class MainApp : public wxApp
{
public:
	bool OnInit();
};

class AddItemDialog : public wxDialog
{
public:
	AddItemDialog(wxWindow *parent, wxWindowID id, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize)
		: wxDialog(parent, id, "Add Item", pos, size)
	{
		wxGridSizer *listSizer = new wxGridSizer(4, wxSize(1,1));
		// create textboxes and add them to listSizer
		wxTextCtrl *idBox = new wxTextCtrl(this, wxID_ANY, "ID", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CENTER);
		wxTextCtrl *nameBox = new wxTextCtrl(this, wxID_ANY, "Name", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CENTER);
		wxTextCtrl *stockBox = new wxTextCtrl(this, wxID_ANY, "Stock", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CENTER);
		wxTextCtrl *priceBox = new wxTextCtrl(this, wxID_ANY, "Price", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CENTER);
		listSizer->Add(idBox, 1, wxEXPAND);
		listSizer->Add(nameBox, 1, wxEXPAND);
		listSizer->Add(stockBox, 1, wxEXPAND);
		listSizer->Add(priceBox, 1, wxEXPAND);
		idEntry = new wxTextCtrl(this, wxID_ANY);
		nameEntry = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
		stockEntry = new wxTextCtrl(this, wxID_ANY);
		priceEntry = new wxTextCtrl(this, wxID_ANY);
		// seteo el largo maximo para la celda del nombre
		nameEntry->SetMaxLength(MAX_NAME_LENGTH);
		listSizer->Add(idEntry, 1, wxEXPAND);
		listSizer->Add(nameEntry, 1, wxEXPAND);
		listSizer->Add(stockEntry, 1, wxEXPAND);
		listSizer->Add(priceEntry, 1, wxEXPAND);

		// crea los botones del cuadro de dialogo
		wxSizer *buttonSizer = this->CreateButtonSizer(wxCLOSE | wxAPPLY);

		// crea un sizer principal y agrega el sizer de las celdas y el de los botones
		wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
		mainSizer->Add(listSizer, 1, wxEXPAND | wxALL, 5);
		mainSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 5);
		this->SetSizerAndFit(mainSizer);
	}

	unsigned int getID() const {
		unsigned int id;

		sscanf(idEntry->GetLineText(0), "%u", &id);

		return id;
	}
	Item* onOkButton() 
	{
		Item* item = createItem();

		unsigned int id = getID();

		setItem(item, id, "test", 1, 1);		

		return item;
	}

private:
	wxTextCtrl *idEntry;
	wxTextCtrl *nameEntry;
	wxTextCtrl *stockEntry;
	wxTextCtrl *priceEntry;
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