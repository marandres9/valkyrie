#include "app_frame.hpp"

wxIMPLEMENT_APP(MainApp);

bool MainApp::OnInit()
{
	wxWindowID mainFrameID = wxWindow::NewControlId();
	MainFrame* frame = new MainFrame(mainFrameID, "Maaaariaano", wxDefaultPosition, wxSize(800, 600));
	frame->Show();
	return true;
}

MainFrame::MainFrame(wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(nullptr, id, title, pos, size)
{	
	// crea la lista y la conecta al evento de click en una columna
	mainListView = new MainList(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_VRULES | wxLC_HRULES);

	// sizer para la lista principal
	// wxBoxSizer *mainListViewSizer = new wxBoxSizer(wxHORIZONTAL);
	// mainListViewSizer->Add(mainListView, 1, wxEXPAND);
	
	mainListView->Bind(wxEVT_LIST_COL_CLICK, 
		[this](wxListEvent &evt) {
			this->sortByColumn(evt.GetColumn());
		}
	);
	populateStock();
	// cargar items desde archivo .bin
	populateList(getHead());

	wxPanel *buttonPanel = new wxPanel(this, wxID_ANY);
	wxButton *newButton = new wxButton(buttonPanel, wxID_ADD);
	wxButton *saveButton = new wxButton(buttonPanel, wxID_SAVE);
	// sizer para los botones
	wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(newButton, 0, wxALL, 5);
	buttonSizer->Add(saveButton, 0, wxALL, 5);
	buttonPanel->SetSizerAndFit(buttonSizer);

	// panel para registrar los movimientos
	stockMovementPanel = new StockMovementPanel(this);

	// sizer principal, agrega la lista y los botones
	wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(mainListView, 3, wxEXPAND);
	mainSizer->Add(stockMovementPanel, 0, wxEXPAND);
	mainSizer->Add(buttonPanel, 0, wxALIGN_RIGHT);
	
	// se ajusta el sizer al panel principal

	this->SetSizerAndFit(mainSizer);
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
	// agrega el item a la lista
	int index = mainListView->GetItemCount();

	mainListView->InsertItem(index, std::to_string(item->id));
	mainListView->SetItem(index, 1, item->name);
	mainListView->SetItem(index, 2, std::to_string(item->stock));
	mainListView->SetItem(index, 3, std::to_string(item->price));

	// el puntero al item se pasa como metadata para el item de la lista en la gui
	mainListView->SetItemPtrData(index, (wxUIntPtr) item);
}
void MainFrame::populateList(Item* listHead)
{
	while(listHead != NULL)
	{
		addListItem(listHead);
		listHead = listHead->next;
	}
}

void MainFrame::onAddItemButton(wxCommandEvent &evt)
{
	addItemDialog = new AddItemDialog(this, wxID_ANY, wxDefaultPosition, wxSize(700, 300));
	addItemDialog->Bind(wxEVT_BUTTON, 
						[this](wxCommandEvent &evt) {
							Item* newItem = addItemDialog->onApplyButton();
							insert_atHead(&head, newItem);

							this->addListItem(newItem);
						},
						wxID_APPLY);

	// muestra el dialogo
	addItemDialog->ShowModal();
	
	// limpia la memoria asignada al dialogo
	addItemDialog->Destroy();
}
void MainFrame::onApplyMovementButton(wxCommandEvent &evt)
{
	// obtener los datos ingresados
	unsigned int id = stockMovementPanel->getID();
	int movement = stockMovementPanel->getMovement();
	// // encontrar el puntero del item asociado al ID ingresado.
	// // si no se encuentra termina
	Item* item = findItem(head, id);

	if (item == NULL) {
		printf("item not found\n(implement message)\n"); 
		return;
	}
	// registra el movimiento
	if (registerMovement(item, movement) == 0) {
		printf("error, insufficient stock\n(implement message)\n"); 
		return;
	}

	// luego busca el item en la lista y lo borra
	// cada item en la GUI tiene metadata asociada a su puntero en la memoria del programa
	long itemIndex = mainListView->FindItem(-1, (wxUIntPtr) item);
	mainListView->DeleteItem(itemIndex);	
	// mostrar nuevamente el item modificado
	this->addListItem(item);
}
void MainFrame::onClose(wxCloseEvent &evt)
{
	// al cerrar la ventana se borra la lista de la memoria
	deleteList(&head);
	// cierra la ventana
	Destroy();
}

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_BUTTON(wxID_ADD, MainFrame::onAddItemButton)
	EVT_BUTTON(wxID_APPLY, MainFrame::onApplyMovementButton)
	EVT_CLOSE(MainFrame::onClose)
wxEND_EVENT_TABLE()
