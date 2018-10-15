//Floyd Pinto 0645556 Oct 15, 2018 Assignment 2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//create the structure of car
typedef struct car
{
    char carname[10];
    int returndate;
    char plateNo[10];
    int milage;
    int totalcharge;
    struct car* next;
}car;
typedef void (*callback)(car* data);

car *availableRent  = NULL;
car *rented = NULL;
car *inrepairlist  = NULL;

//function used to create the node into linkedlist
car* create(char* noPlate,int mil,int totalcharge,int rdate,car* next)
{
    car* new_node = (car*)malloc(sizeof(car));
    if(new_node == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
    strcpy(new_node->plateNo,noPlate);
    new_node->milage = mil;
    new_node->returndate = rdate;
    new_node->next = next;
    new_node->totalcharge = totalcharge;
    return new_node;
}

//function used to add the data into the linked list
car* addCarToAvailableList(char* noPlate, int mil,int totalcharge,car* availableRent)
{
    // If linkedlist is null i.e head is null then create the head node else go to the last node and add the car
    if(availableRent != NULL)
    {
        /* go to the last node */
        car *cursor = availableRent;
        while(cursor->next != NULL)
            cursor = cursor->next;
        /* create a new node */
        car* new_node =  create(noPlate,mil,totalcharge,0,NULL);
        cursor->next = new_node;
        return availableRent;
    }
    else
    {
        car* new_node =  create(noPlate,mil,totalcharge,0,NULL);
        return new_node;
    }
}

// To compute the charge if mileage is greater than 100
int computeCharge(int mileage)
{
    //a flat rate of $40.00 for up to 100 km
    if(mileage < 100)
    {
        return 100;
    }else{
        //15 cents per km for the additional (i.e. beyond 100) kilometers.
        return (100 + (0.15)*(mileage - 100));
    }
}

//function used to display the list of particular list
void display(car* n)
{
    if(n != NULL)
    {
        printf("plateno: %s ", n->plateNo);
        printf("mileage: %d ", n->milage);
        printf("date: %d", n->returndate);
        printf("totalcharge: %d \n", n->totalcharge);
    }
}

//    traverse the linked list
void traverse(car* head,callback f)
{
    car* cursor = head;
    while(cursor != NULL)
    {
        f(cursor);
        cursor = cursor->next;
    }
}

// To give the car on the rent this function is used
void rentCar()
{
    if(availableRent == NULL)
        return;
    car *front = availableRent;
    availableRent = availableRent->next;
    front->next = NULL;
    /* is this the last node in the list */
    if(front == availableRent)
        availableRent = NULL;

    if(rented==NULL)
    {
      rented=front;
    }
    else{
        car *cursor = rented;
    while(cursor->next != NULL)
        cursor = cursor->next;
    cursor->next=front;
    }
}

// this function is used to search that platnumber exist into repairlist or not
int search(char* key)
{
    int index;
    struct car *curNode;
    index = 0;
    curNode = inrepairlist;
    while (curNode != NULL && curNode->plateNo != key)
    {
        index++;
        curNode = curNode->next;
    }
	if (curNode != NULL)
	{
		return index;
	}
	else
	{
		return -1;
	}
}

// Calculate the total income for each rented car
int calculatetotalincome(car* head)
{
    int totalincome = 0;
    car* cursor = head;
    while(cursor != NULL)
    {
        totalincome = totalincome + cursor->totalcharge;
        cursor = cursor->next;
    }
    return totalincome;
}

// main function
int main ()
{
    int ch = 0;
    int mil;
    int totalcharge;
    int index;
    char noPlate[10];
    do
    {
        printf ("\n");
        printf ("1. Add a new car \n");
        printf ("2. Add a returned car to available list\n");
        printf ("3. Add a returned car to repaired list \n");
        printf ("4. Tranfer caer from repaired list to available list \n");
        printf ("5. Rent a car \n");
        printf ("6. Print all lists \n");
        printf ("7. Quit \n");
        printf ("Enter your choice:");
        scanf ("%d", &ch);
        switch (ch)
        {
            case 1:
                printf("Enter plate no:");
                scanf("%s",noPlate);
                printf("Enter Milage:");
                scanf("%d",&mil);
                totalcharge = computeCharge(mil);
                printf("Total charge applied is %d: ", totalcharge);
                //add car
                availableRent = addCarToAvailableList (noPlate,mil,totalcharge,availableRent);
                break;
            case 2:

                printf("Enter plate no:");
                scanf("%s",noPlate);
                printf("Enter Milage:");
                scanf("%d",&mil);
                totalcharge = computeCharge(mil);
                printf("Total charge applied is %d: ", totalcharge);
                // add to avilable car list
                availableRent = addCarToAvailableList (noPlate,mil,totalcharge,availableRent);
                break;
            case 3:

                printf("Enter plate no:");
                scanf("%s",noPlate);
                printf("Enter Milage:");
                scanf("%d",&mil);
                totalcharge = computeCharge(mil);
                printf("Total charge applied is %d: ", &totalcharge);
                rented = addCarToAvailableList (noPlate,mil,totalcharge,availableRent);
                break;
            case 4:
                printf("Enter plate no:");
                scanf("%s",noPlate);
                index = search(noPlate);
                // Element found in the list
                if (index >= 0)
                    printf("%s found in the list at position %d\n", noPlate, index + 1);
                else
                    printf("%s not found in the list.\n", noPlate);
                break;
            case 5:
                // Give car on the rent
                rentCar();
                break;
            case 6:
                printf("Available Car List:\n");
                traverse(availableRent,display);
                printf("Rented Car List:\n");
                traverse(rented,display);
                printf("Repaired Car List:\n");
                traverse(inrepairlist,display);
                break;
            case 7:
                // calculate the total income
                printf("Total income: %d",calculatetotalincome(rented));
                break;
        }
    }
    while (ch != 7);
    return 0;
}