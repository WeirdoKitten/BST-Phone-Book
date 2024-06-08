#include "phonebook.h"

node *root = NULL;

node *createNode(char inputName[50], char inputNumber[13])
{
    node *newNode = (node *)malloc(sizeof(node));
    numberList *newNumber = (numberList *)malloc(sizeof(numberList));
    if (newNode == NULL || newNumber == NULL)
    {
        return NULL;
    }
    strcpy(newNode->name, inputName);
    strcpy(newNumber->phoneNumber, inputNumber);
    newNumber->next = NULL;
    newNode->phoneNumberS = newNumber;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void addPhoneNumber(node *personNode, char inputNumber[13])
{
    numberList *newNumber = (numberList *)malloc(sizeof(numberList));
    if (newNumber == NULL)
    {
        return;
    }
    strcpy(newNumber->phoneNumber, inputNumber);
    newNumber->next = NULL;

    numberList *current = personNode->phoneNumberS;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNumber;
}

void toCapitalizeCase(char str[])
{
    int len = strlen(str);
    int capitalizeNext = 1;

    for (int i = 0; i < len; i++)
    {
        str[i] = tolower(str[i]);
        if (capitalizeNext && isalpha(str[i]))
        {
            str[i] = toupper(str[i]);
            capitalizeNext = 0;
        }
        else if (str[i] == ' ')
        {
            capitalizeNext = 1;
        }
    }
}

void insertData(char inputName[50], char inputNumber[13])
{
    char formattedName[50];
    strcpy(formattedName, inputName);
    toCapitalizeCase(formattedName);

    node *currNode = root;
    node *prevNode = NULL;

    if (root == NULL)
    {
        root = createNode(formattedName, inputNumber);
        return;
    }

    while (currNode != NULL)
    {
        prevNode = currNode;
        if (strcmp(currNode->name, formattedName) == 0)
        {
            addPhoneNumber(currNode, inputNumber);
            return;
        }
        else if (strcmp(currNode->name, formattedName) > 0)
        {
            currNode = currNode->left;
        }
        else
        {
            currNode = currNode->right;
        }
    }

    node *newNode = createNode(formattedName, inputNumber);
    if (strcmp(prevNode->name, formattedName) > 0)
    {
        prevNode->left = newNode;
    }
    else
    {
        prevNode->right = newNode;
    }
}

void printAllNode(node *currNode)
{
    if (currNode != NULL)
    {
        printAllNode(currNode->left);
        printf("===================================================\n");
        printf("Nama          : %s\n", currNode->name);
        numberList *numList = currNode->phoneNumberS;
        while (numList != NULL)
        {
            printf("Nomor Telepon : %s\n", numList->phoneNumber);
            numList = numList->next;
        }
        printf("===================================================\n\n");
        printAllNode(currNode->right);
    }
}

void inputData()
{
    char inputNama[50];
    char inputNumber[13];

    while ((getchar()) != '\n')
        ;
    printf("Inputkan Nama : ");
    scanf("%[^\n]%*c", inputNama);
    printf("Inputkan Nomor Telepon: ");
    scanf("%[^\n]%*c", inputNumber);

    insertData(inputNama, inputNumber);

    saveToFile(root, "data.txt");
}

void search(node *root, char inputName[50]) {
    char formattedName[50];
    strcpy(formattedName, inputName);
    toCapitalizeCase(formattedName);

    if (root != NULL) {
        if (strstr(root->name, formattedName)) {
            printf("===================================================\n");
            printf("Nama          : %s\n", root->name);
            numberList *numList = root->phoneNumberS;
            while (numList != NULL) {
                printf("Nomor Telepon : %s\n", numList->phoneNumber);
                numList = numList->next;
            }
            printf("===================================================\n\n");
        }
        search(root->left, formattedName);
        search(root->right, formattedName);
    }
}

void saveToFile(node *root, const char *filename) {
    char tempFilename[256];
    sprintf(tempFilename, "%s.tmp", filename);

    FILE *tempFile = fopen(tempFilename, "w");
    if (tempFile != NULL) {
        writeToFile(root, tempFile);
        fclose(tempFile);

        remove(filename);
        rename(tempFilename, filename);
    } else {
        printf("Gagal membuat file sementara\n");
    }
}

void writeToFile(node *root, FILE *file) {
    if (root != NULL) {
        writeToFile(root->left, file);
        fprintf(file, "Nama: %s\n", root->name);
        numberList *numList = root->phoneNumberS;
        while (numList != NULL) {
            fprintf(file, "Nomor Telepon: %s\n", numList->phoneNumber);
            numList = numList->next;
        }
        fprintf(file, "===================================================\n\n");
        writeToFile(root->right, file);
    }
}

void loadFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return;
    }

    char line[256];
    char name[50];
    char phoneNumber[13];

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "Nama: %[^\n]", name) == 1)
        {
            while (fgets(line, sizeof(line), file) && sscanf(line, "Nomor Telepon: %[^\n]", phoneNumber) == 1)
            {
                insertData(name, phoneNumber);
            }
        }
    }

    fclose(file);
}

node *findMin(node *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

node *deleteContact(node *root, char inputName[50])
{
    if (root == NULL)
        return root;

    if (strcmp(inputName, root->name) < 0)
        root->left = deleteContact(root->left, inputName);
    else if (strcmp(inputName, root->name) > 0)
        root->right = deleteContact(root->right, inputName);
    else
    {
        if(root->left == NULL && root->right == NULL){
            freeNumberList(root->phoneNumberS);
            free(root);
            return NULL;
        }
        else if (root->left == NULL)
        {
            node *temp = root->right;
            freeNumberList(root->phoneNumberS);
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            node *temp = root->left;
            freeNumberList(root->phoneNumberS);
            free(root);
            return temp;
        }

        node *temp = findMin(root->right);
        strcpy(root->name, temp->name);
        root->phoneNumberS = temp->phoneNumberS;
        root->right = deleteContact(root->right, temp->name);
    }

    saveToFile(root, "data.txt");

    return root;
}

void freeNumberList(numberList *numList) {
    numberList *current = numList;
    while (current != NULL) {
        numberList *next = current->next;
        free(current);
        current = next;
    }
}

void updateContact(node *root, const char *inputName, const char *newName, char newNumber[13])
{
    if (root == NULL)
    {
        printf("Kontak tidak ditemukan\n");
        return;
    }

    if (strcmp(inputName, root->name) < 0)
        updateContact(root->left, inputName, newName, newNumber);
    else if (strcmp(inputName, root->name) > 0)
        updateContact(root->right, inputName, newName, newNumber);
    else
    {
        if (newName != NULL && strlen(newName) > 0)
        {
            strcpy(root->name, newName);
        }
        if (newNumber != NULL && strlen(newNumber) > 0)
        {
            numberList *numList = root->phoneNumberS;
            if (numList != NULL)
            {
                strcpy(numList->phoneNumber, newNumber);
            }
            else
            {
                addPhoneNumber(root, newNumber);
            }
        }
        printf("Kontak berhasil diperbarui\n");
        saveToFile(root, "data.txt");
        return;
    }
}
