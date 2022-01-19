#include "AddItemDialog.hpp"

AddItemDialog::AddItemDialog(wxWindow *parent,
                            wxWindowID id,
                            const wxPoint &pos,
                            const wxSize &size)
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

unsigned int AddItemDialog::getID() const {
    unsigned int id;
    sscanf(idEntry->GetLineText(0), "%u", &id);

    return id;
}
std::string AddItemDialog::getName() const {
    return nameEntry->GetLineText(0).ToStdString();
}
unsigned int AddItemDialog::getStock() const {
    unsigned int stock;
    sscanf(stockEntry->GetLineText(0), "%u", &stock);

    return stock;
}
float AddItemDialog::getPrice() const {
    float price;
    sscanf(priceEntry->GetLineText(0), "%f", &price);

    return price;
}

ItemData AddItemDialog::onApplyButton() 
{
    ItemData itemData = {.id = getID(),
                        .stock = getStock(),
                        .price = getPrice()
                        };
    strcpy(itemData.name, getName().c_str());
    
    return itemData;
}