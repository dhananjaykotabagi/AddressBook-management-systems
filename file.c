#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *ptr = fopen("contact.csv","w");
    // open file in write mode
    FILE *fp = fopen("contacts.csv", "w");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    // write contact count in first line
    fprintf(fp, "%d\n", addressBook->contactCount);

    // write each contact
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    // close file
    fclose(fp);

    printf("Contacts saved successfully!✅.\n");
}
    
void loadContactsFromFile(AddressBook *addressBook) {
    {
    // open file in read mode
    FILE *fp = fopen("contacts.csv", "r");

    if (fp == NULL)
    {
        printf("No file found. Starting with empty address book.\n");
        addressBook->contactCount = 0;
        return;
    }

    // read contact count
    fscanf(fp, "%d\n", &addressBook->contactCount);

    // read each contact
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fp, "%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    // close file
    fclose(fp);

    printf("Contacts loaded successfully !✅.\n");
}
    
}
