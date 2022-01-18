#include <wx/msgdlg.h>

enum ERROR_CODE {
    ERR_NOT_FOUND,
    ERR_INSUFFICIENT_STOCK,
    ERR_NOT_SELECTED,
    ERR_REPEATED_ID,
};

class ErrorBox
{
public:
    static void callError(ERROR_CODE err);

private:
    wxString msg;
    ErrorBox();
};