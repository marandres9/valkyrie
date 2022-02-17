#include "Application.hpp"

wxIMPLEMENT_APP(MainApp);

bool MainApp::OnInit()
{
	MainFrame* frame = new MainFrame(wxID_ANY, "Valkyrie", wxDefaultPosition, wxSize(800, 600));
	frame->Show();
	return true;
}

MainFrame::MainFrame(wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(nullptr, id, title, pos, size)
{	
	// crear la lista
	this->mainListView = new MainList(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_VRULES | wxLC_HRULES);	
	// crear panel para botones
	wxPanel *buttonPanel = new wxPanel(this, wxID_ANY);
	// crear botones
	wxButton *addButton = new wxButton(buttonPanel, wxID_ADD);
	wxButton *saveButton = new wxButton(buttonPanel, wxID_SAVE);
	wxButton *deleteButton = new wxButton(buttonPanel, wxID_DELETE);
	
	// sizer para los botones
	wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(deleteButton, 0, wxALL, 5);
	buttonSizer->AddStretchSpacer();
	buttonSizer->Add(addButton, 0, wxALL, 5);
	buttonSizer->Add(saveButton, 0, wxALL, 5);

	buttonPanel->SetSizerAndFit(buttonSizer);

	// panel para registrar los movimientos
	stockMovementPanel = new StockMovementPanel(this);

	// sizer principal, agrega la lista y los botones
	wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(mainListView, 3, wxEXPAND);
	mainSizer->Add(stockMovementPanel, 0, wxEXPAND);
	mainSizer->Add(buttonPanel, 0, wxEXPAND);
	
	// se ajusta el sizer al panel principal
	this->SetSizerAndFit(mainSizer);
}

void MainFrame::onAddItemButton(wxCommandEvent &evt)
{
	AddItemDialog *addItemDialog = new AddItemDialog(this, wxID_ANY, wxDefaultPosition, wxSize(700, 300));
	addItemDialog->Bind(wxEVT_BUTTON, 
						[this, &addItemDialog](wxCommandEvent &evt) {
							// obtiene los datos ingresados en el dialogo
							ItemData newItemData = addItemDialog->onApplyButton();
							// agrega el item a la LL y a la listView
							this->mainListView->addNewItem(newItemData.id, newItemData.name,
															newItemData.stock, newItemData.price);
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
	// si el movimiento es valido, limpia el cuadro del movimiento
	// si no es valido la funcion registerMovement() se encarga de dar el error
	if(this->mainListView->registerMovement(id, movement)) {
		stockMovementPanel->clearMovementEntry();
	}
}
void MainFrame::onSaveButton(wxCommandEvent &evt)
{
	wxDialog *saveDialog = new wxDialog(this, wxID_ANY, "Save...");

	wxTextCtrl *message = new wxTextCtrl(saveDialog, wxID_ANY, "Save changes?", 
										wxDefaultPosition, wxDefaultSize,
										wxTE_CENTER | wxTE_READONLY);

	wxSizer *buttonSizer = saveDialog->CreateButtonSizer(wxCANCEL | wxYES);
	saveDialog->Bind(wxEVT_BUTTON, 
					[this, &saveDialog](wxCommandEvent &evt) {
						this->mainListView->saveList();
						saveDialog->Destroy();
					},
					wxID_YES);

	wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(message, 1, wxEXPAND | wxALL, 10);
	mainSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 5);
	saveDialog->SetSizerAndFit(mainSizer);

	saveDialog->ShowModal();

	saveDialog->Destroy();
}
void MainFrame::onDeleteButton(wxCommandEvent &evt)
{
	// checkear que el usuario haya selecionado un item
	if(mainListView->GetSelectedItemCount() < 1)
	{								
		ErrorBox::callError(ERR_NOT_SELECTED);
		printf("no item selected\n");
		return;
	}
	// instancia un nuevo dialogo
	wxDialog *deleteDialog = new wxDialog(this, wxID_ANY, "Delete item?", wxDefaultPosition, wxSize(700, 300));
	// crea sizer para los botones
	wxSizer *buttonSizer = deleteDialog->CreateButtonSizer(wxYES | wxCANCEL);
	// crea sizer para cuadros de texto que mustran ID y nombre
	wxGridSizer *gridSizer = new wxGridSizer(2, wxSize(10, 10));
	// crea los cuadros de texto y los agrega a su sizer
	wxTextCtrl *idBox = new wxTextCtrl(deleteDialog, wxID_ANY, this->mainListView->getSelectedItemID(), wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CENTER);
	wxTextCtrl *nameBox = new wxTextCtrl(deleteDialog, wxID_ANY, this->mainListView->getSelectedItemName(), wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CENTER);
	gridSizer->Add(idBox, 1, wxEXPAND);
	gridSizer->Add(nameBox, 1, wxEXPAND);
	// sizer principal, se ajusta al dialogo
	wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(gridSizer, 1, wxEXPAND | wxALL, 5);
	mainSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 5);
	deleteDialog->SetSizerAndFit(mainSizer);
	
	// conecta el evento del boton "Yes"
	deleteDialog->Bind(wxEVT_BUTTON, 
						[this, &deleteDialog](wxCommandEvent &evt) {	
							// no need to pass an itemID since the listView keeps
							// track of the selected item
							this->mainListView->deleteItem();
							deleteDialog->Destroy();
						},
						wxID_YES);
	// muestra el dialogo
	deleteDialog->ShowModal();
	deleteDialog->Destroy();
}
void MainFrame::onClose(wxCloseEvent &evt)
{
	// al cerrar la ventana se borra la lista de la memoria
	// first check if list isn't already empty
	if(!mainListView->isEmpty()) {
		mainListView->freeList();
	}
	// cierra la ventana
	Destroy();
}
// al seleccionar un item en la gui guarda el id del item y lo pasa al panel de los movimientos 
void MainFrame::setSelectedItem(wxListEvent &evt)
{
	wxString itemID = evt.GetText();
	long itemIndex = evt.GetIndex();
	
	this->mainListView->setSelectedItemData(itemID, itemIndex);
	this->stockMovementPanel->appendID(itemID);
}

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_BUTTON(wxID_ADD, MainFrame::onAddItemButton)
	EVT_BUTTON(wxID_APPLY, MainFrame::onApplyMovementButton)
	EVT_BUTTON(wxID_SAVE, MainFrame::onSaveButton)
	EVT_BUTTON(wxID_DELETE, MainFrame::onDeleteButton)
	EVT_CLOSE(MainFrame::onClose)
	EVT_LIST_ITEM_SELECTED(wxID_ANY, MainFrame::setSelectedItem)
wxEND_EVENT_TABLE()
