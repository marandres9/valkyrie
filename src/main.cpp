#include "header.hpp"

wxIMPLEMENT_APP(MainApp);

bool MainApp::OnInit()
{
	MainFrame* frame = new MainFrame("Maaariaano", wxDefaultPosition, wxSize(800, 600));
	frame->Show();
	return true;
}

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	wxPanel *mainPanel = new wxPanel(this);
	
	wxListView *mainList = new wxListView(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	mainList->AppendColumn("ID", wxLIST_FORMAT_CENTER, 100);
	mainList->AppendColumn("Name", wxLIST_FORMAT_CENTER, 500);
	mainList->AppendColumn("Stock", wxLIST_FORMAT_CENTER, 100);
	mainList->AppendColumn("Price", wxLIST_FORMAT_CENTER, 100);

	auto *button = new wxButton(mainPanel, wxID_ANY, "test");

	wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(mainList, 1, wxEXPAND);
	mainSizer->Add(button, 0, wxALIGN_RIGHT);

	mainPanel->SetSizerAndFit(mainSizer);
}