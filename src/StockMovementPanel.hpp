#ifndef STOCKMOVEMENTPANEL_HPP
#define STOCKMOVEMENTPANEL_HPP

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <iostream>

class StockMovementPanel : public wxPanel
{
public:
    StockMovementPanel(wxWindow *parent, wxWindowID winid = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);

    unsigned int getID() const;
    int getMovement() const;
    void appendID(const wxString &id_str);

private:
    wxTextCtrl *idEntry;
    wxTextCtrl *movementEntry;
};

#endif