#ifndef ITEMLIST_H
#define ITEMLIST_H

typedef struct item
{
	unsigned int id;
	char name[20];
	unsigned int stock;
	float price;

	struct item* next;
} Item;

typedef enum op
{
	ENTRADA,
	SALIDA,
} Operacion;

unsigned int getID(Item* item);
const char* getName(Item* item);
unsigned int getStock(Item* item);
float getPrice(Item* item);

void setID(Item* item, unsigned int newID);
void setName(Item* item, const char* newName);
void setStock(Item* item, unsigned int newStock);
void setPrice(Item* item, float newPrice);

Item* getItem(Item* listHead, unsigned int itemID);
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

void registerMovement(Item* listHead, unsigned int itemID, Operacion op, unsigned int cantidad);

void writeTxt(Item* listHead);
void writeBin(Item* listHead);
void readAndPrintBin();
Item* readBin();

#endif