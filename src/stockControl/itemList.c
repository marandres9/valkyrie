#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "itemList.h"

#define LISTDIR_PREFIX "listas/"
#define TXT_NAME "lista.txt"
#define BIN_NAME "lista.bin"

unsigned int getID(Item* item)
{
	return item->id;
}
const char* getName(Item* item)
{
	return item->name;
}
unsigned int getStock(Item* item)
{
	return item->stock;
}
float getPrice(Item* item)
{
	return item->price;
}

void setID(Item* item, unsigned int newID)
{
	item->id = newID;
}
void setName(Item* item, const char* newName)
{
	strcpy(item->name, newName);
}
void setStock(Item* item, unsigned int newStock)
{
	item->stock = newStock;
}
void setPrice(Item* item, float newPrice)
{
	item->price = newPrice;
}


Item* getItem(Item* listHead, unsigned int itemID)
{
	if(itemID == 0) return NULL;
	
	Item* temp = listHead;

	while(temp->id != itemID)
	{
		if(temp == NULL) break;
		temp = temp->next;
	}
	return temp;
}
void printByID(Item* listHead, unsigned int itemID)
{
	Item* itemToPrint = getItem(listHead, itemID);

	if(itemToPrint != NULL)
	{
		printByPtr(itemToPrint);
	}
	else
	{
		printf("Item not found\n");
	}
}
void printByPtr(Item* item)
{
	printf("%d\t%s\t%d\t%.2f\n", getID(item), getName(item), getStock(item), getPrice(item));
}
void printAll(Item* listHead)
{
	Item* temp = listHead;

	while (temp != NULL)
	{
		printByPtr(temp);
		temp = temp->next;
	}
}

Item* createItem()
{
	Item* newItem = malloc(sizeof(Item));

	newItem->next = NULL;

	return newItem;
}

void setItem(Item* item, unsigned int newID, const char* newName, unsigned int newStock, float newPrice)
{
	setID(item, newID);
	setName(item, newName);
	setStock(item, newStock);
	setPrice(item, newPrice);
}

Item* insert_atHead(Item** listHead, Item* item)
{
	item->next = *listHead;
	*listHead = item;

	return item;
}
void createAndSet_atHead(Item** listHead, unsigned int newID, const char* newName, unsigned int newStock, float newPrice)
// Los arg se pasan por ref, tengo que cambiar la direc apuntada por head, entonces tengo que pasar un puntero 
// al puntero de head. Cambio el valor de head desreferenciando una vez el puntero, accediendo a la direccion que
// contiene el puntero que quiero modificar
{
	Item* newItem = createItem();
	setItem(newItem, newID, newName, newStock, newPrice);

	// cambio de head
	insert_atHead(listHead, newItem);
}
Item* createAndSet_after(Item** itemToInsertAfter, unsigned int newID, const char* newName, unsigned int newStock, float newPrice)
{
	Item* newItem = createItem();
	setItem(newItem, newID, newName, newStock, newPrice);

	newItem->next = (*itemToInsertAfter)->next;

	(*itemToInsertAfter)->next = newItem;

	return newItem;
}
void deleteItem(Item** listHead, unsigned int itemID)
{
	Item* actual = *listHead;	// creo una variable que apunta a la direccion del head del programa principal
	Item* previous;

	if((*listHead)->id == itemID)
	// si el nodo que se quiere borrar es el primero (el que apunta la cabeza)
	{
		*listHead = (*listHead)->next;	// cambia el puntero de head
		free(actual);				// libera el nodo al que apuntaba la cabeza vieja
		return;
	}

	while(actual->id != itemID)
	// recorre la lista buscando la id
	{
		// si no se encuentra la id termina
		if(actual == NULL) return;

		previous = actual;
		actual = actual->next;
	}

	// se acomodan los punteros y se libera la memoria del nodo que se queire borrar
	previous->next = actual->next;
	free(actual);

}
void deleteList(Item** listHead)
{
	Item* nextItem = (*listHead)->next;

	// borra hasta que llega al ultimo item
	while(nextItem != NULL)
	{
		free(*listHead);
		*listHead = nextItem;
		nextItem = nextItem->next;
	}
	// borra el ultimo item
	free(*listHead);
	// setea el puntero a NULL para que deje de apuntar ya que se borro la lista
	*listHead = NULL;
}

void changeName(Item* listHead, unsigned int itemID, const char* newName)
{
	setName(getItem(listHead, itemID), newName);
}
void changeID(Item* listHead, unsigned int oldID, unsigned int newID)
{
	setID(getItem(listHead, oldID), newID);
}
void changeStock(Item* listHead, unsigned int itemID, unsigned int newStock)
{
	setStock(getItem(listHead, itemID), newStock);
}
void changePrice(Item* listHead, unsigned int itemID, float newPrice)
{
	setPrice(getItem(listHead, itemID), newPrice);
}

Item* getItemAndRegisterMovement(Item* listHead, unsigned int itemID, Operacion op, unsigned int cantidad)
{
	Item* temp = getItem(listHead, itemID);
	if (temp == NULL)
	{
		printf("ID %u not found.\n", itemID);
		return temp;
	}

	switch (op)
	{
	case ENTRADA:
		temp->stock += cantidad;
		break;
	case SALIDA:
		temp->stock -= cantidad;
		break;	
	default:
		printf("Error al registrar la opearcion\n");
		return NULL;
	}
	return temp;
}
int registerMovement(Item* item, int movimiento)
{
	// el movimiento puede ser positivo(entrada) o negativo(salida)

	if(item->stock < abs(movimiento) && movimiento < 0)
	{
		printf("Insufficient stock\n");
		return 0;
	}

	item->stock += movimiento;
	return 1;
}

void writeTxt(Item* listHead)
{
	FILE* fptr;
	fptr = fopen(LISTDIR_PREFIX""TXT_NAME, "w");
	if (fptr == NULL)
	{
		printf("Error al abrir el archivo %s\n", LISTDIR_PREFIX""TXT_NAME);
		printf("Asegurese de crear el directorio listas/\n");
		fclose(fptr);
		return;
	}
	
	Item* temp = listHead;
	while(temp != NULL)
	{
		fprintf(fptr, "%d\t%s\t%d\t%.2f\n", temp->id, temp->name, temp->stock, temp->price);
		temp = temp->next;
	}

	fclose(fptr);
}
void writeBin(Item* listHead)
{
	FILE* fptr;
	fptr = fopen(LISTDIR_PREFIX""BIN_NAME, "wb");
	if (fptr == NULL)
	{
		printf("Error al abrir el archivo %s\n", LISTDIR_PREFIX""TXT_NAME);
		printf("Asegurese de crear el directorio listas/\n");
		fclose(fptr);
		return;
	}

	Item* temp = listHead;
	while(temp != NULL)
	{
		fwrite(temp, sizeof(Item), 1, fptr);
		temp = temp->next;
	}

	fclose (fptr);
}
void readAndPrintBin()
{
	FILE *fptr;
	fptr = fopen(LISTDIR_PREFIX""BIN_NAME, "rb");
	if (fptr == NULL)
	{
		printf("Error al abrir el archivo %s\n", LISTDIR_PREFIX""BIN_NAME);
		return;
	}

	Item* itemToPrint = malloc(sizeof(Item));
	
	// usa do-while porque checkea el puntero al siguiente item del item leido
	// no hace falta saber la cantidad de items escritos de antemano
	// porque el ultimo item de la lista no apunta a ningun lado (NULL)
	// Solo se deben escribir items en el archivo .bin
	do
	{
		fread(itemToPrint, sizeof(Item), 1, fptr);

		printByPtr(itemToPrint);
	}
	while (itemToPrint->next != NULL);

	// limpieza final
	free(itemToPrint);
	fclose(fptr);
}

Item* readBin()
{
	FILE *fptr;
	fptr = fopen(LISTDIR_PREFIX""BIN_NAME, "rb");
	if (fptr == NULL)
	{
		printf("Error al abrir el archivo %s\n", LISTDIR_PREFIX""BIN_NAME);
		fclose(fptr);
		return NULL;
	}

	Item* head = NULL;

	// averiguar cant de items escritos
	fseek(fptr, 0, SEEK_END);
	int size = ftell(fptr);
	int numItems = size / sizeof(Item);

	for (int n = 1; n <= numItems; n++)
	{
		// posiciona el cursor "n" Items hacia atras desde el final del archivo
		fseek(fptr, -n*sizeof(Item), SEEK_END);

		// instancia y lee el item
		Item* newItem = createItem();
		fread(newItem, sizeof(Item), 1, fptr);
		
		// acomoda los punteros
		insert_atHead(&head, newItem);
	}
	fclose(fptr);

	return head;
}