#include <wx/wx.h>

class StockMovementPanel : public wxPanel
{
public:
    StockMovementPanel(wxWindow *parent, wxWindowID winid = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize)
        : wxPanel(parent, winid, pos, size)
    {
        wxGridSizer *listSizer = new wxGridSizer(2, wxSize(1,1));
        // create textboxes and add them to listSizer
        wxTextCtrl *idBox = new wxTextCtrl(this, wxID_ANY, "ID", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CENTER);
        wxTextCtrl *movementBox = new wxTextCtrl(this, wxID_ANY, "Stock movement", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CENTER);
        listSizer->Add(idBox, 1, wxEXPAND);
        listSizer->Add(movementBox, 1, wxEXPAND);
        idEntry = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTER);
        movementEntry = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTER);
        listSizer->Add(idEntry, 1, wxEXPAND);
        listSizer->Add(movementEntry, 1, wxEXPAND);

        // crea los botones del cuadro de dialogo
        wxButton *applyButton = new wxButton(this, wxID_APPLY, "Apply movement");

        // crea un sizer principal y agrega el sizer de las celdas y el de los botones
        wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
        mainSizer->Add(listSizer, 1, wxEXPAND | wxALL, 5);
        mainSizer->Add(applyButton, 0, wxEXPAND | wxALL, 5);
        this->SetSizerAndFit(mainSizer);
    }

    unsigned int getID() const
    {
        // convierte wxString a int y checkea que no sea negativo
        unsigned int id = wxAtoi(idEntry->GetLineText(0));
        if(id < 0) return 0;

        return id;
    }
    int getMovement() const
    {
        // convierte wxString a int
        int movement = wxAtoi(movementEntry->GetLineText(0));;
        return movement;
    }
private:
    wxTextCtrl *idEntry;
    wxTextCtrl *movementEntry;
};