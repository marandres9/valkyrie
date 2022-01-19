#include "MainList.hpp"

MainList::MainList(wxWindow *parent,
                    wxWindowID winid,
                    const wxPoint& pos,
                    const wxSize& size,
                    long style)
		: wxListView(parent, winid, pos, size, style)
{

    this->AppendColumn("ID", wxLIST_FORMAT_CENTER, 100);
    this->AppendColumn("Name", wxLIST_FORMAT_CENTER, 500);
    this->AppendColumn("Stock", wxLIST_FORMAT_CENTER, 100);
    this->AppendColumn("Price", wxLIST_FORMAT_CENTER, 100);

    this->Bind(wxEVT_LIST_COL_CLICK, 
		[this](wxListEvent &evt) {
			this->sortByColumn(evt.GetColumn());
		}
	);
}

Item* MainList::getHead() const
{
	return this->head;
}
void MainList::createListFromFile()
{
    // creates linked list from listas.bin
	this->head = readBin();
}
void MainList::addNewItem(unsigned int newID, const char *newName, unsigned int newStock, float newPrice)
{
    // agregar item a la lista
    Item* newItem = createAndSet_atHead(&(this->head), newID, newName, newStock, newPrice);
    // newItem es NULL si no se pudo crear el item (por id repetido)
    if(newItem == NULL) {
        ErrorBox::callError(ERR_REPEATED_ID);
    }
    // agrega newItem a la listView
    this->addListViewItem(newItem);
}
void MainList::addListViewItem (Item *item)
{
	// agrega el item a la lista
	int index = this->GetItemCount();

	this->InsertItem(index, std::to_string(item->id));
	this->SetItem(index, 1, item->name);
	this->SetItem(index, 2, std::to_string(item->stock));
	this->SetItem(index, 3, std::to_string(item->price));

	// el puntero al item se pasa como metadata para el item de la lista en la gui
	this->SetItemPtrData(index, (wxUIntPtr) item);
}
void MainList::populateListView()
{
    // creates a copy of the head ptr
    Item* listHead = this->head;

    // copy linked list contents to listView
	while(listHead != NULL)
	{
		this->addListViewItem(listHead);
		listHead = listHead->next;
	}
}

Item* MainList::findItem(uint itemID)
{
    return _findItem(this->head, itemID);
}
void MainList::saveList() 
{
    writeBin(this->head);
    writeTxt(this->head);

}
void MainList::freeList() {
    _deleteList(&(this->head));
}