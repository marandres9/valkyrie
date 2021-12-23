#include "app_frame.hpp"

wxIMPLEMENT_APP(MainApp);

bool MainApp::OnInit()
{
	MainFrame* frame = new MainFrame("Mariaano", wxDefaultPosition, wxSize(800, 600));
	frame->Show();
	return true;
}

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	// crea el panel en el que se ponen los objetos
	wxPanel *mainPanel = new wxPanel(this);
	
	// crea la lista y la conecta al evento de click en una columna
	mainListView = new MainList(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_VRULES | wxLC_HRULES);
	mainListView->Bind(wxEVT_LIST_COL_CLICK, 
		[this](wxListEvent &evt) {
			this->sortByColumn(evt.GetColumn());
		}
	);
	populateStock();
	// cargar items desde archivo .bin
	populateList(getHead());

	wxButton *newButton = new wxButton(mainPanel, wxID_ADD);
	wxButton *movButton = new wxButton(mainPanel, wxID_ANY, "Movimiento");
	wxButton *saveButton = new wxButton(mainPanel, wxID_SAVE);

	// sizer para los botones
	wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(newButton, 0, wxALL, 5);
	buttonSizer->Add(movButton, 0, wxALL, 5);
	buttonSizer->Add(saveButton, 0, wxALL, 5);

	// sizer principal, agrega la lista y los botones
	wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(mainListView, 1, wxEXPAND);
	mainSizer->Add(buttonSizer, 0, wxALIGN_RIGHT);
	
	// se ajusta el sizer al panel principal
	mainPanel->SetBackgroundColour(wxColour("Cyan"));
	mainPanel->SetSizerAndFit(mainSizer);
}

Item* MainFrame::getHead() const
{
	return head;
}
void MainFrame::populateStock()
{
	head = readBin();
}
void MainFrame::addListItem (Item *item)
{
	// agrega el item a la lista y modifica la bandera status para que no se vuelva a agregar

	int index = mainListView->GetItemCount();

	mainListView->InsertItem(index, std::to_string(item->id));
	mainListView->SetItem(index, 1, item->name);
	mainListView->SetItem(index, 2, std::to_string(item->stock));
	mainListView->SetItem(index, 3, std::to_string(item->price));

	mainListView->SetItemData(index, (wxIntPtr) item);

	item->status = SHOWN_ON_LIST;
}
void MainFrame::populateList(Item* listHead)
{
	// solo agrega a la lista items que no hayan sido linkeados previamente
	while(listHead != NULL)
	{
		if (listHead->status == NOT_SHOWN_ON_LIST) {
			addListItem(listHead);

			listHead = listHead->next;
		}
		else {
			listHead = listHead->next;
		}
	}
}

void MainFrame::onAddItemButton(wxCommandEvent &evt)
{
	addItemDialog = new AddItemDialog(this, wxID_ANY, wxDefaultPosition, wxSize(700, 300));
	addItemDialog->Bind(wxEVT_BUTTON, 
		[this](wxCommandEvent &evt) {
			this->addListItem(addItemDialog->onOkButton());
		},
		 wxID_APPLY);
	// muestra el dialogo
	addItemDialog->ShowModal();
	
	// limpia la memoria asignada al dialogo
	addItemDialog->Destroy();
	printf("dialog gone\n");
}


wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_BUTTON(wxID_ADD, MainFrame::onAddItemButton)
wxEND_EVENT_TABLE()
