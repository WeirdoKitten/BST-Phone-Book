#include "phonebook.h"
node *root = NULL;

node *createNode(char inputName[50], char inputNumber[15])
{
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL)
    {
        return NULL;
    }
    strcpy(newNode->name, inputName);
    strcpy(newNode->phoneNumber[0], inputNumber);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insertData(char inputName[50], char inputNumber[15])
{
    node *currNode = root;
    node *prevNode;
    if (root == NULL)
    {
        node *newNode = createNode(inputName, inputNumber);
        root = newNode;
        return;
    }
    while (currNode != NULL)
    {
        prevNode = currNode;
        if (strcmp(currNode->name, inputName) == 0)
        {
            printf("nama sudah tersedia");
            return;
        }
        else if (strcmp(currNode->name, inputName) > 0)
        {
            currNode = currNode->left;
        }
        else
        {
            currNode = currNode->right;
        }
    }

    node *newNode = createNode(inputName, inputNumber);

    if (strcmp(prevNode->name, inputName) > 0)
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
        printf("Nomor Telepon : %s\n", currNode->phoneNumber);
        printf("===================================================\n\n");
        printAllNode(currNode->right);
    }
}

void inputData()
{
    char inputNama[50];
    char inputNumber[15];

    while ((getchar()) != '\n')
        ;
    printf("Inputkan Nama : ");
    scanf("%[^\n]%*c", inputNama);

    printf("Inputkan Nomor Telepon: ");
    scanf("%[^\n]%*c", inputNumber);
    insertData(inputNama, inputNumber);
}

void search(node *root, char inputName[50])
{
    if (root != NULL)
    {

        if (strstr(root->name, inputName))
        {
            printf("===================================================\n");
            printf("Nama          : %s\n", root->name);
            printf("Nomor Telepon : %s\n", root->phoneNumber);
            printf("===================================================\n\n");
        }
        if (strcmp(inputName, root->name) < 0)
        {
            search(root->left, inputName); // Cari di subtree kiri jika substring lebih kecil
        }
        else
        {
            search(root->right, inputName); // Cari di subtree kanan jika substring lebih besar atau sama
        
        }
    }
}

