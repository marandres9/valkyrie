#ifndef STOCKMOVEMENTPANEL_HPP
#define STOCKMOVEMENTPANEL_HPP

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <iostream>

class StockMovementPanel : public wxPanel
{
public:
    StockMovementPanel(wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size);

    unsigned int getID() const;
    int getMovement() const;
    void appendID(wxListEvent &evt);

private:
    wxTextCtrl *idEntry;
    wxTextCtrl *movementEntry;
};

#endif