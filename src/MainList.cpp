#include "MainList.hpp"
#include <iostream>

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
    // read lista.bin file contents, load list to memory
    this->createListFromFile();
    // copy list contents to listView
    this->populateListView();
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
        return;
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
    return find_item(this->head, itemID);
}
void MainList::saveList() 
{
    write_bin(this->head);
    write_txt(this->head);

}
bool MainList::registerMovement(uint itemID, int movement)
{
	// encontrar el puntero del item asociado al ID ingresado.
	// si no se encuentra termina
    Item* item = this->findItem(itemID);

    if (item == NULL) {
		ErrorBox::callError(ERR_NOT_FOUND);
		printf("item not found\n"); 
		return false;
	}
	// registra y checkea el movimiento
	if (register_movement(item, movement) == 0) {
		ErrorBox::callError(ERR_INSUFFICIENT_STOCK);
		printf("error, insufficient stock\n"); 
		return false;
	}
	// luego busca el item en la lista y lo borra
	// cada item en la GUI tiene metadata asociada a su puntero en la memoria del programa
	long itemIndex = this->FindItem(-1, (wxUIntPtr) item);
	this->DeleteItem(itemIndex);	
	// mostrar nuevamente el item modificado
	this->addListViewItem(item);

    return true;
}
void MainList::deleteItem() {
    uint itemID = wxAtoi(getSelectedItemID());

    // if item isn't found call error and return false
    if (findItem(itemID) == NULL) {
        ErrorBox::callError(ERR_NOT_FOUND);
        printf("Item not found\n");
        return;
    }

    // delete item from memory
    delete_item(&(this->head), itemID);
    // delete item from listView
    this->DeleteItem(this->getSelectedItemIndex());
}
void MainList::freeList() {
    delete_list(&(this->head));
}

bool MainList::isEmpty() const {
    if(this->head == NULL) return true;
    else return false;
}

void MainList::setSelectedItemData(wxString itemID, long itemIndex)
{
	selectedItemID = itemID;
	selectedItemIndex = itemIndex;
}
const wxString &MainList::getSelectedItemID() const
{
	return selectedItemID;
}
long MainList::getSelectedItemIndex() const 
{
	return selectedItemIndex;
}
wxString MainList::getSelectedItemName() const
{
	return this->GetItemText(selectedItemIndex, 1);
}
