#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"server.h"
int main () // main function that controls all other functions
{  
   int checkid,no,ch; char peras[50]; char changestto[50]; char search[50];
    do
    {
 printf("Menu\n");
    printf("1. Add a bug (maximum 100)\n");
    printf("2. Display all bugs and total number of bugs\n");
    printf("3. Assign bug to a person (manager required) \n");
    printf("4. Get list of bugs filed by same person\n");
    printf("5. Get list of bugs having same priority \n");
    printf("6. Get list of all bugs having same status\n");
    printf("7. Get list of all bugs having same type\n");
    printf("8. Change status of bug (only assigned person can do so)\n");
    printf("9. Exit\n");
    printf("Enter choice\n");
    scanf("%d",&ch);
    switch(ch) // to call the functions depending on need of the user
    {
        case 1:
        add();
        break;
        case 2:
        printf("Enter 0 to display all bugs, otherwise enter specific bug ID for its details\n");
        scanf("%d",&checkid);
        no=disp(checkid);
        printf("Total number of bugs= %d\n",no);
        break;
        case 3:
        // taking in details, using %[^\n] to change delimiter of scanf for strings from space to newline
        printf("Enter ID of bug\n");
        scanf("%d",&checkid);
        printf("Enter name of person to who bug is assigned (max 50 letters)\n");
        scanf(" %[^\n]",peras); 
        assign(peras,checkid);
        break;
        case 4:
        // taking in details, using %[^\n] to change delimiter of scanf for strings from space to newline
        printf("Enter name of person to be searched\n");
        scanf(" %[^\n]",search);
        no=person(search);
        printf("Total number of bugs filed by %s= %d\n",search,no); //displaying number of bugs filed by specific person
        break;
        case 5:
        // taking in details, using %[^\n] to change delimiter of scanf for strings from space to newline
        printf("Enter priority of bug to be searched (low, medium, high)\n");
        scanf(" %[^\n]",search);
        no=pri(search);
        printf("Total number of bugs filed with %s priority= %d\n",search,no); //displaying number of bugs filed with specific priority
        break;
        case 6:
       // taking in details, using %[^\n] to change delimiter of scanf for strings from space to newline
        printf("Enter status of bug to be searched (not assigned, assigned, being fixed, fixed, delivered)\n");
        scanf(" %[^\n]",search);
        no=status(search);
        printf("Total number of bugs filed with %s status= %d\n",search,no); //displaying number of bugs filed with specific status
        break;
        case 7:
         // taking in details, using %[^\n] to change delimiter of scanf for strings from space to newline
        printf("Enter type of bug to be searched (major, minor, cosmetic) \n");
        scanf(" %[^\n]",search);
        no=type(search);
        printf("Total number of bugs filed with %s type= %d\n",search,no); //displaying number of bugs filed with specific type
        break;
        case 8:
         // taking in details, using %[^\n] to change delimiter of scanf for strings from space to newline
        printf("Enter ID of bug\n");
        scanf("%d",&checkid);
        printf("Enter your name (person assigned to bug)\n");
        scanf(" %[^\n]",peras);
        printf("Enter the changed status\n");
        scanf(" %[^\n]",changestto);
        changestat(checkid,peras,changestto);
        break;
        case 9:
        exit(0); //EXIT_SUCCESS;
        // allows the user to exit the program at any time he chooses
        default: // for wrong input
        printf("Invalid entry\n");
    } // keeps calling the menu until user is done with his tasks
   }while(1);
} 