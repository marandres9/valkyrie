#include "app_frame.hpp"

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
	// crea el panel en el que se ponen los objetos
	wxPanel *mainPanel = new wxPanel(this);
	
	// crea la lista y la conecta al evento de click en una columna
	mainListView = new MainList(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	mainListView->Bind(wxEVT_LIST_COL_CLICK, 
		[this](wxListEvent &evt) {
			this->sortByColumn(evt.GetColumn());
		}
	);
	populateStock();
	mainListView->populateList(getHead());

	createAndSet_atHead(&head, 100, "TestItem", 0, 100);
	mainListView->addListItem(head);
	createAndSet_atHead(&head, 110, "TestItem2", 10, 80);
	mainListView->addListItem(head);

	auto *button = new wxButton(mainPanel, wxID_ANY, "test");

	// sizer principal, agrega la lista y los botones
	wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(mainListView, 1, wxEXPAND);
	mainSizer->Add(button, 0, wxALIGN_RIGHT);
	// se ajusta el sizer al panel principal
	mainPanel->SetSizerAndFit(mainSizer);
}

Item* MainFrame::getHead()
{
	return head;
}
void MainFrame::populateStock()
{
	head = readBin();
}

// SORTING
void MainFrame::sortByColumn(int col)
{
// la funcion recibe la columna clickeada y llama a la funcion que corresponda
	switch (col)
	{
	case 0:
		mainListView->SortItems(IDSortCallBack, this->sortDirection);
		break;
	case 2:
		mainListView->SortItems(stockSortCallBack, this->sortDirection);
		break;
	case 3:
		mainListView->SortItems(priceSortCallback, this->sortDirection);
		break;
	default:
		return;
	}
// refresca la lista e invierte la direccion en la que se van a ordenar los items la proxima vez
	mainListView->Refresh();
	this->sortDirection = -this->sortDirection;
}
// funciones sobrecargadas que comparan los valores en las celdas de cada columna
int MainFrame::compareValues(unsigned int u1, unsigned int u2, int direction)
{
	return (u1 == u2) ? 0 : ((u1 < u2) ? -direction : direction);
}
int MainFrame::compareValues(float f1, float f2, int direction)
{
	return (f1 == f2) ? 0 : ((f1 < f2) ? -direction : direction);
}
// estas funciones intermedias pasan el valor devuelto por las funcinoes de comparacion
// a la funcion SortItems(), la cual se encarga de ordenar los items
int MainFrame::IDSortCallBack(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction)
{
	return compareValues(((Item*) item1)->id, ((Item*) item2)->id, (int) direction);
}
int MainFrame::stockSortCallBack(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction)
{
	return compareValues(((Item*) item1)->stock, ((Item*) item2)->stock, (int) direction);
}
int MainFrame::priceSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction)
{
	return compareValues(((Item*) item1)->price, ((Item*) item2)->price, (int) direction);
}