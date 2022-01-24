#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

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


Item* find_item(Item* listHead, unsigned int itemID)
{	
	if(listHead == NULL) return NULL;
	
	Item* temp = listHead;

	while(temp->id != itemID && temp != NULL)	
	{
		temp = temp->next;
		if(temp == NULL) break;
	}
	return temp;
}
void printByID(Item* listHead, unsigned int itemID)
{
	Item* itemToPrint = find_item(listHead, itemID);

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

int setItem(Item* listHead, Item* item, unsigned int newID, const char* newName, unsigned int newStock, float newPrice)
{
	if (find_item(listHead, newID) == NULL) 
	{
		setID(item, newID);
		setName(item, newName);
		setStock(item, newStock);
		setPrice(item, newPrice);
		return 1;
	}
	else
	{
		printf("ID %u already exists, use unique IDs\n", newID);
		return 0;
	}
}

Item* insert_atHead(Item** listHead, Item* item)
{
	item->next = *listHead;
	*listHead = item;

	return item;
}
Item* createAndSet_atHead(Item** listHead, unsigned int newID, const char* newName, unsigned int newStock, float newPrice)
// Se toma un puntero que apunta a la cabeza de la lista (que es un puntero), ya que 
// se necesita modificar la direccion a la que apunta la cabeza. 
// Si el argumento fuera de tipo Item* listHead, la funcion recibiria una copia del 
// puntero listHead, y no podria cambiar la direccion a la que apunta la cabeza real.
{
	Item* newItem = createItem();
	// si la funcion setItem devuelve 0, el ID ya existe y no se agrega el item a la lista
	if (setItem(*listHead, newItem, newID, newName, newStock, newPrice) == 0)
	{
		free(newItem);
		return NULL;
	}
	else
	{
		// cambio de head
		insert_atHead(listHead, newItem);
		return newItem;
	}
}
void delete_item(Item** listHead, unsigned int itemID)
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
void delete_list(Item** listHead)
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
	setName(find_item(listHead, itemID), newName);
}
void changeID(Item* listHead, unsigned int oldID, unsigned int newID)
{
	setID(find_item(listHead, oldID), newID);
}
void changeStock(Item* listHead, unsigned int itemID, unsigned int newStock)
{
	setStock(find_item(listHead, itemID), newStock);
}
void changePrice(Item* listHead, unsigned int itemID, float newPrice)
{
	setPrice(find_item(listHead, itemID), newPrice);
}

Item* getItemAndRegisterMovement(Item* listHead, unsigned int itemID, Operacion op, unsigned int cantidad)
{
	Item* temp = find_item(listHead, itemID);
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
int register_movement(Item* item, int movimiento)
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

void write_txt(Item* listHead)
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

	printf("File written succesfully: "LISTDIR_PREFIX TXT_NAME"\n");
	fclose(fptr);
}
void write_bin(Item* listHead)
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

	printf("File written succesfully: "LISTDIR_PREFIX BIN_NAME"\n");
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