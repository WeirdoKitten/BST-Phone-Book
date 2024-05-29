#include "phonebook.h"

node *root = NULL;

node *createNode(char inputName[50], char inputNumber[13]) {
    node *newNode = (node *)malloc(sizeof(node));
    numberList *newNumber = (numberList *)malloc(sizeof(numberList));
    if (newNode == NULL || newNumber == NULL) {
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

void addPhoneNumber(node *personNode, char inputNumber[13]) {
    numberList *newNumber = (numberList *)malloc(sizeof(numberList));
    if (newNumber == NULL) {
        return;
    }
    strcpy(newNumber->phoneNumber, inputNumber);
    newNumber->next = NULL;

    numberList *current = personNode->phoneNumberS;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNumber;
}

void insertData(char inputName[50], char inputNumber[13]) {
    node *currNode = root;
    node *prevNode = NULL;

    if (root == NULL) {
        root = createNode(inputName, inputNumber);
        return;
    }

    while (currNode != NULL) {
        prevNode = currNode;
        if (strcmp(currNode->name, inputName) == 0) {
            addPhoneNumber(currNode, inputNumber);
            return;
        } else if (strcmp(currNode->name, inputName) > 0) {
            currNode = currNode->left;
        } else {
            currNode = currNode->right;
        }
    }

    node *newNode = createNode(inputName, inputNumber);
    if (strcmp(prevNode->name, inputName) > 0) {
        prevNode->left = newNode;
    } else {
        prevNode->right = newNode;
    }
}

void printAllNode(node *currNode) {
    if (currNode != NULL) {
        printAllNode(currNode->left);
        printf("===================================================\n");
        printf("Nama          : %s\n", currNode->name);
        numberList *numList = currNode->phoneNumberS;
        while (numList != NULL) {
            printf("Nomor Telepon : %s\n", numList->phoneNumber);
            numList = numList->next;
        }
        printf("===================================================\n\n");
        printAllNode(currNode->right);
    }
}

void inputData() {
    char inputNama[50];
    char inputNumber[13];

    while ((getchar()) != '\n');
    printf("Inputkan Nama : ");
    scanf("%[^\n]%*c", inputNama);
    printf("Inputkan Nomor Telepon: ");
    scanf("%[^\n]%*c", inputNumber);

    insertData(inputNama, inputNumber);
}

void search(node *root, char inputName[50]) {
    if (root != NULL) {
        if (strstr(root->name, inputName)) {
            printf("===================================================\n");
            printf("Nama          : %s\n", root->name);
            numberList *numList = root->phoneNumberS;
            while (numList != NULL) {
                printf("Nomor Telepon : %s\n", numList->phoneNumber);
                numList = numList->next;
            }
            printf("===================================================\n\n");
        }
        if (strcmp(inputName, root->name) < 0) {
            search(root->left, inputName); 
        } else {
            search(root->right, inputName); 
        }
    }
}
