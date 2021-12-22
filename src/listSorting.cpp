#include "app_frame.hpp"

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

