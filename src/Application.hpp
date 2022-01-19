#ifndef APP_FRAME_HPP
#define APP_FRAME_HPP

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/textctrl.h>

#include "MainList.hpp"
#include "StockMovementPanel.hpp"
#include "AddItemDialog.hpp"
#include "ErrorBox.hpp"

// extern "C" {
// 	#include "linkedList/linkedList.h"
// }

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

	void setSelectedItem(wxListEvent &evt);
private:
	// declaracion de los miembros
	MainList *mainListView;
	AddItemDialog *addItemDialog;	

	StockMovementPanel *stockMovementPanel;

	// evt handlers
	void onAddItemButton(wxCommandEvent &evt);
	void onApplyMovementButton(wxCommandEvent &evt);
	void onSaveButton(wxCommandEvent &evt);
	void onDeleteButton(wxCommandEvent &evt);
	void onClose(wxCloseEvent &evt);

	wxDECLARE_EVENT_TABLE();
};

#endif