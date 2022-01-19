#include "MainList.hpp"

// SORTING
void MainList::sortByColumn(int col)
{
// la funcion recibe la columna clickeada y llama a la funcion que corresponda
	switch (col)
	{
	case 0:
		this->SortItems(IDSortCallBack, this->sortDirection);
		break;
	case 2:
		this->SortItems(stockSortCallBack, this->sortDirection);
		break;
	case 3:
		this->SortItems(priceSortCallback, this->sortDirection);
		break;
	default:
		return;
	}
// refresca la lista e invierte la direccion en la que se van a ordenar los items la proxima vez
	this->Refresh();
	this->sortDirection = -this->sortDirection;
}
// funciones sobrecargadas que comparan los valores en las celdas de cada columna
int MainList::compareValues(unsigned int u1, unsigned int u2, int direction)
{
	return (u1 == u2) ? 0 : ((u1 < u2) ? -direction : direction);
}
int MainList::compareValues(float f1, float f2, int direction)
{
	return (f1 == f2) ? 0 : ((f1 < f2) ? -direction : direction);
}
// estas funciones intermedias pasan el valor devuelto por las funcinoes de comparacion
// a la funcion SortItems(), la cual se encarga de ordenar los items
int MainList::IDSortCallBack(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction)
{
	return compareValues(((Item*) item1)->id, ((Item*) item2)->id, (int) direction);
}
int MainList::stockSortCallBack(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction)
{
	return compareValues(((Item*) item1)->stock, ((Item*) item2)->stock, (int) direction);
}
int MainList::priceSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction)
{
	return compareValues(((Item*) item1)->price, ((Item*) item2)->price, (int) direction);
}

