/*


*** New features ***

1. You can see how much space left before the database is resized.
2. Yow can remove an item from the database without modifying it.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Initial database size
int N = 5;

//Item structure
typedef struct {
    int itemId;
    char itemName[50];
    int quantity;
    double pricePerItem;
} Item;


//Inserting a new item in the database

void insertItem(Item ** itemInventory, Item item, int *count) {
    //Check if the item ID already exists
    for (int a = 0; a < *count; a++) {
        if ((*itemInventory)[a].itemId == item.itemId) {
            printf("\nError Inserting an Item, item ID already exists\n");
            return;
        }
    }

    //Check if the database has enough space if not double the size
    if (*count == N) {
        N *= 2;
        *itemInventory = (Item *)realloc(*itemInventory, N * sizeof(Item));
        if (!*itemInventory) {
            printf("Memory reallocation failed\n");
            exit(1);
        }
    }

    (*itemInventory)[*count] = item;
    (*count)++;
    printf("\nItem successfully inserted\n");
}

void spaceLeft(int count) {
	printf("Space left for new entries before resizing: %d\n", N-count);
}


void updateItem(Item *itemInventory,int count, int itemID, const char *itemName, int quantity, double pricePerItem) {

        for (int i = 0; i < count; i++) {
        if (itemInventory[i].itemId == itemID) {
		
strncpy(itemInventory[i].itemName,itemName,sizeof(itemInventory[i].itemName)-1);
          itemInventory[i].itemName[sizeof(itemInventory[i].itemName)-1] = '\0';
	    itemInventory[i].pricePerItem = pricePerItem;
            itemInventory[i].quantity = quantity;
            printf("\nItem updated successfully\n");
            return;
        }
    }
    printf("\nItem Not Found\n");
}

void searchItem(Item *itemInventory, int count, int itemID) {
    for (int i = 0; i < count; i++) {
        if (itemInventory[i].itemId == itemID) {
            printf("********************\n");
            printf("Item ID: %03d\n", itemInventory[i].itemId);
            printf("Item Name: %s\n", itemInventory[i].itemName);
            printf("Item Quantity: %d\n", itemInventory[i].quantity);
            printf("Price per Item: %.2lf\n", itemInventory[i].pricePerItem);
            printf("********************\n");
            return;
        }
    }
    printf("\nItem Not Found\n");
}

//Display the whole database
void printData(Item *itemInventory, int count) {
    printf("*********************************************************\n");
    printf("Item ID   Item Name       Item Quantity   Item Price\n");
    printf("*********************************************************\n");
    for (int i = 0; i < count; i++) {
        printf("%03d       %-15s %-15d %.2lf\n",
               itemInventory[i].itemId,
               itemInventory[i].itemName,
               itemInventory[i].quantity,
               itemInventory[i].pricePerItem);
    }
    printf("*********************************************************\n");
}

// New addition to the database now you can remove an item without modifying it.
void removeItem(Item *itemInventory, int *count, int itemID) {
    for (int i = 0; i < *count; i++) {
        if (itemInventory[i].itemId == itemID) {
            // Shift everything after this item one slot left
            for (int j = i; j < *count - 1; j++) {
                itemInventory[j] = itemInventory[j + 1];
            }
            (*count)--;  // Reduce the total count
            printf("\nItem with ID %d removed successfully\n", itemID);
            return;
        }
    }
    printf("\nItem Not Found\n");
}


//Quit the database program
void quit(Item *itemInventory) {
    free(itemInventory);
    printf("Exiting...\n");
}

int main() {
    Item *itemInventory = (Item *)malloc(N * sizeof(Item));
    if (!itemInventory) {
        printf("Memory allocation failed\n");
        return 1;
    }

    int count = 0; //Number of items in the database
    char choice;

    do {
        printf("\n***********************************************\n");
        printf("Enter your Choice:\n");
        printf("'i' - insert an item\n");
        printf("'u' - update the database\n");
        printf("'s' - search the database\n");
        printf("'d' - display the database\n");
        printf("'l' - display the space count left before resizing\n");
        printf("'r' - remove an item\n");

	printf("'q' - quit the program\n");
        printf("***********************************************\n");
        printf("Your choice: ");
        scanf(" %c", &choice);
        choice = tolower(choice);

        switch (choice) {
            case 'i': {
                Item newItem;
                printf("Enter Item ID: ");
                scanf("%d", &newItem.itemId);
                printf("Enter Item Name: ");
                scanf(" %[^\n]", newItem.itemName);
                printf("Enter Quantity: ");
                scanf("%d", &newItem.quantity);
                printf("Enter Price per Item: ");
                scanf("%lf", &newItem.pricePerItem);
                insertItem(&itemInventory, newItem, &count);
                break;
            }
            case 'u': {
                int itemID, quantity;
		char itemName[50];
		double pricePerItem;
                printf("Enter Item ID: ");
                scanf("%d", &itemID);
		printf("Enter the name or new name if it has changed: ");
		scanf(" %[^\n]", itemName);
                printf("Enter new Quantity: ");
                scanf("%d", &quantity);
		printf("Enter the price or the new price if changed: ");
		scanf("%lf", &pricePerItem);
                updateItem(itemInventory,count,itemID,itemName,quantity,pricePerItem);
                break;
            }
		
            case 's': {
                int itemID;
                printf("Enter Item ID: ");
                scanf("%d", &itemID);
                searchItem(itemInventory, count, itemID);
                break;
            }
            case 'd':
                printData(itemInventory, count);
                break;
	    case 'l':
		spaceLeft(count);
		break;

        case 'r': {
        int itemID;
        printf("Enter Item ID to remove: ");
        scanf("%d", &itemID);
        removeItem(itemInventory, &count, itemID);
        break;
        }

	    case 'q':
                quit(itemInventory);
                break;
            default:
                printf("%c is not a valid choice\n", choice);
        }
    } while (choice != 'q');

    return 0;
}
