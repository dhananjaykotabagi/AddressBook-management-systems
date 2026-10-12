#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    int i,j;
    Contact temp;
    {
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=i+1;j<addressBook->contactCount;j++)
            {
                if(strcmp(addressBook->contacts[i].name,addressBook->contacts[j].name)>0)
                // if(strcmp(addressBook->contacts[i].phone,addressBook->contacts[j].phone)>0)
                {
                    temp=addressBook->contacts[i];
                    addressBook->contacts[i]=addressBook->contacts[j];
                    addressBook->contacts[j]=temp;
                }
            }
        }
    }
   // Sort contacts based on the chosen criteria
    for(int i=0; i <addressBook->contactCount;i++)
    {
    printf("%s\t\t\t\t\t%s\t\t\t\t\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //  populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)

   loadContactsFromFile(addressBook);


}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
int validate_Email(char *Email)
{
    for(int i=0;Email[i] !='\0';i++)
    {
        if(!((Email[i] >='a' && Email[i]<= 'z'|| Email[i]=='@' && Email[i]=='.')))
        {
            return 1;
        }
    }
    return 0;
}

int validate_name(char *name)
{

   for(int i = 0; name[i] != '\0'; i++)
    {
        if(!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z' ) || name[i] == ' ' || name[i] == '.'))
        {
            return 0;
        }
        
    }
    return 1;
    
}
int validate_phone(char *phone)
{

    int i;
    for( i=0;phone[i] !='\0';i++)
    {
        if(!(phone[i]>='0' || phone[i]<= '9'))
        return 0;
    }
    

    if(i!=10)
    // if(!isdigit(phone[i]))
    {
        return 0;
    }
    else
    return 1;
}
int is_Valid_Mobilenumber(char* phone,AddressBook *addressBook)
{
    int i=0;
    while (phone[i] != '\0')
    {
        if (phone[i] < '0' || phone[i] > '9')
         {   return 0;
           }
         i++;
    }
    
    if(i!=10)
    {
        return 0;
    }

    for (int j = 0; j < addressBook->contactCount; j++)
    {
        if (strcmp(addressBook->contacts[j].phone, phone) == 0)
        {
            return 0; 
        }
    }

    return 1;
}



void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char name[50];
    char phone[20];
    char email[50];
    int valid;
     while(1)
     {
        printf("Enter the name:");
        scanf(" %[^\n]",name);
        valid=validate_name(name);
        if(valid == 1)
            break;
        
    }
    while(1)
    {
        printf("Enter the phone:");
        scanf(" %[^\n]",phone);
        valid=validate_phone(phone);
        if(valid == 0)
        {
            printf("Invalid Number\n");
            continue;
        }
        break;

    }
     while(1)
     {
    printf("Enter the email:");
    scanf(" %[^\n]",email);
     valid=validate_Email(email);
     if(valid == 0)
     {
         printf("Invalid Email❌.\n");
        continue;
     }
     break;
     }
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
     strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
       strcpy(addressBook->contacts[addressBook->contactCount].email,email);
       addressBook->contactCount++;

         printf(" contact Added Succesfully✅.\n");



    
}

int search_by_Name(AddressBook *addressBook)
{
    int ind = -1;
    char new_name[50];
    printf("Enter name to search :");
    scanf(" %[^\n]",new_name);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if((strcasestr(addressBook->contacts[i].name,new_name))!=NULL)
        {
            printf("%s\t\t\t\t%s\t\t\t\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            ind = i;
        }
    }
    if(ind != -1)
        return ind;
    else
        return -1;
}
int search_by_phone(AddressBook *addressBook)
{
    int ind=-1;
    char new_phone[60];
    printf("Enter phone to search:");
    scanf(" %[^\n]",new_phone);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if((strcmp(addressBook->contacts[i].phone,new_phone))==0)
        {
        printf("%s\t\t\t\t%s\t\t\t\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        return i;
        }
     }
     
     return -1;
}
int search_by_Email(AddressBook *addressBook)
{
    int ind=-1;

     char new_Email[50];
     printf("Enter Email to search:");
     scanf(" %[^\n]",new_Email);
     for(int i=0;i<addressBook->contactCount;i++)
     {
        if((strcmp(addressBook->contacts[i].email,new_Email))==0)
        {
        printf("%s\t\t\t\t%s\t\t\t\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        return i;
        }
     }
     
     return -1;
}



int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */

    int choice;
    printf("search by\n1.Name\n2.phone\n3.email\n");
    printf("Enter choice:");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
        if(search_by_Name(addressBook) == -1)
            printf("No Contact Found!");
        break;

        break;
        case 2:
         search_by_phone(addressBook);
         break;
         case 3:
          search_by_Email(addressBook);
        break;

    }

}

//  void editContact(AddressBook *addressBook)
void editContact(AddressBook *addressBook)
    {
	/* Define the logic for Editcontact */
    int ret = searchContact(addressBook);
    int i;
    if(ret == 0)
    {
        printf("Edit Contact Failure\n");
        return;
    }
    else
    {
        printf("Enter the Index to Edit the contact: ");
        scanf("%d",&i);
        
        int choice;
        printf("Edit By\n");
        printf("1.Edit By Name\n");
        printf("2.Edit by Phone\n");
        printf("3.Edit by E-mail\n");
        printf("Enter Your Choice: ");
        scanf("%d",&choice);
        
        if(choice == 1)
        {
            getchar();
            printf("Enter the New Name: ");
            scanf("%[^\n]",addressBook->contacts[i].name);
        }
        else if(choice == 2)
        {
            getchar();
            printf("Enter the New Phone Number: ");
            scanf("%[^\n]",addressBook->contacts[i].phone);
        }
        else if(choice == 3)
        {
            getchar();
            printf("Enter the New Email-Id : ");
            scanf("%[^\n]",addressBook->contacts[i].email);
        }
        else
        {
            printf("Invalid Choice❌.\n");
        }


    }
    printf("Contact Edited Succesfully✅\n");
    
}
	
void deleteContact(AddressBook *addressBook)
{
    int ret=searchContact(addressBook);
    int i;
    if(ret== 0)
    {
        printf("Delete Contact failed.\n");
        return;
    }
    else
    {
      printf("\nEnter the index want to delete:");
      scanf("%d",&i);
    }
    for(int i = ret; i < addressBook->contactCount ; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("Contact deleted successfully!✅.\n");
}


   

