#ifndef ADDITEMDIALOG_HPP
#define ADDITEMDIALOG_HPP

#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>

extern "C" {
    #include "stockControl/itemList.h"
}

class AddItemDialog : public wxDialog
{
public:
	AddItemDialog(wxWindow *parent,
                    wxWindowID id = wxID_ANY,
                    const wxPoint &pos = wxDefaultPosition,
                    const wxSize &size = wxDefaultSize);

	unsigned int getID() const;
	std::string getName() const;
	unsigned int getStock() const;
	float getPrice() const;
	
	Item* onApplyButton();

private:
	wxTextCtrl *idEntry;
	wxTextCtrl *nameEntry;
	wxTextCtrl *stockEntry;
	wxTextCtrl *priceEntry;
};

#endif