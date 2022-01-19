#ifndef APP_FRAME_HPP
#define APP_FRAME_HPP

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/textctrl.h>

#include "MainList.hpp"
#include "StockMovementPanel.hpp"
#include "AddItemDialog.hpp"
#include "ErrorBox.hpp"

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
	MainFrame(wxWindowID id, const wxString& title,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize);

	// list controls
	Item* getHead() const;
	void populateStock();
	void addListItem (Item *item);
	void populateList(Item* listHead);
	
	void setSelectedItem(wxListEvent &evt);
	const wxString &getSelectedItemID() const;
	long getSelectedItemIndex() const;
	wxString getSelectedItemName() const;
private:
	// declaracion de los miembros
	MainList *mainListView;
	AddItemDialog *addItemDialog;	
	Item* head;

	wxString selectedItemID;
	long selectedItemIndex = 0;

	StockMovementPanel *stockMovementPanel;
	// ErrorBox *errorBox;

	// evt handlers
	void onAddItemButton(wxCommandEvent &evt);
	void onApplyMovementButton(wxCommandEvent &evt);
	void onSaveButton(wxCommandEvent &evt);
	void onDeleteButton(wxCommandEvent &evt);
	void onClose(wxCloseEvent &evt);

	wxDECLARE_EVENT_TABLE();
};

#endif