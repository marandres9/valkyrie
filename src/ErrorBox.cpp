#include "ErrorBox.hpp"

ErrorBox::ErrorBox() {}

void ErrorBox::callError(ERROR_CODE err) {
    wxString msg;
    switch(err) {
        case ERR_NOT_FOUND:
            msg = "Item not found";
            break;
        case ERR_INSUFFICIENT_STOCK:
            msg = "Stock exit exceeds available stock";
            break;
        case ERR_NOT_SELECTED:
            msg = "Please select an item";
            break;
        case ERR_REPEATED_ID:
            msg = "ID is already in use\nPlease use an unique ID";
            break;
        default:
            msg = wxEmptyString;
            break;
    }
    wxMessageDialog(nullptr, msg, "Error", wxOK).ShowModal();
}