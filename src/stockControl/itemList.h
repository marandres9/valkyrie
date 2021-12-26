#ifndef ITEMLIST_H
#define ITEMLIST_H

#define MAX_NAME_LENGTH 20

typedef enum
{
	ENTRADA,
	SALIDA,
} Operacion;

typedef struct item
{
	unsigned int id;
	char name[MAX_NAME_LENGTH];
	unsigned int stock;
	float price;

	struct item* next;
} Item;

unsigned int getID(Item* item);
const char* getName(Item* item);
unsigned int getStock(Item* item);
float getPrice(Item* item);

void setID(Item* item, unsigned int newID);
void setName(Item* item, const char* newName);
void setStock(Item* item, unsigned int newStock);
void setPrice(Item* item, float newPrice);

Item* findItem(Item* listHead, unsigned int itemID);
void printByID(Item* listHead, unsigned int itemID);
void printByPtr(Item* item);
void printAll(Item* listHead);

Item* createItem();
void setItem(Item* item, unsigned int newID, const char* newname, unsigned int newstock, float newprice);
Item* insert_atHead(Item** listHead, Item* item);
void createAndSet_atHead(Item** listHead, unsigned int newID, const char* newName, unsigned int newStock, float newPrice);
Item* createAndSet_after(Item** itemToInsertAfter, unsigned int newKey, const char* newName, unsigned int newStock, float newPrice);
void deleteItem(Item** listHead, unsigned int itemID);
void deleteList(Item** listHead);

void changeName(Item* listHead, unsigned int itemID, const char* newName);
void changeID(Item* listHead, unsigned int oldID, unsigned int newID);
void changeStock(Item* listHead, unsigned int key, unsigned int newStock);
void changePrice(Item* listHead, unsigned int key, float newPrice);

Item* getItemAndRegisterMovement(Item* listHead, unsigned int itemID, Operacion op, unsigned int cantidad);
// funcion adaptada para la gui
int registerMovement(Item* item, int movimiento);

void writeTxt(Item* listHead);
void writeBin(Item* listHead);
void readAndPrintBin();
Item* readBin();

#endif