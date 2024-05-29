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

void toCapitalizeCase(char str[]) {
    int len = strlen(str);
    int capitalizeNext = 1;

    for (int i = 0; i < len; i++) {
        str[i] = tolower(str[i]);
        if (capitalizeNext && isalpha(str[i])) {
            str[i] = toupper(str[i]);
            capitalizeNext = 0;
        } else if (str[i] == ' ') {
            capitalizeNext = 1;
        }
    }
}

void insertData(char inputName[50], char inputNumber[13]) {
    char formattedName[50];
    strcpy(formattedName, inputName);
    toCapitalizeCase(formattedName);

    node *currNode = root;
    node *prevNode = NULL;

    if (root == NULL) {
        root = createNode(formattedName, inputNumber);
        return;
    }

    while (currNode != NULL) {
        prevNode = currNode;
        if (strcmp(currNode->name, formattedName) == 0) {
            addPhoneNumber(currNode, inputNumber);
            return;
        } else if (strcmp(currNode->name, formattedName) > 0) {
            currNode = currNode->left;
        } else {
            currNode = currNode->right;
        }
    }

    node *newNode = createNode(formattedName, inputNumber);
    if (strcmp(prevNode->name, formattedName) > 0) {
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

    FILE *file = fopen("data.txt", "w");
    if (file != NULL) {
        saveToFile(root, file);
        fclose(file);
    } else {
        printf("Gagal membuka file\n");
    }
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
        if (strcmp(formattedName, root->name) < 0) {
            search(root->left, formattedName); 
        } else {
            search(root->right, formattedName); 
        }
    }
}

void saveToFile(node *root, FILE *file) {
    if (root != NULL) {
        saveToFile(root->left, file);
        fprintf(file, "Nama: %s\n", root->name);
        numberList *numList = root->phoneNumberS;
        while (numList != NULL) {
            fprintf(file, "Nomor Telepon: %s\n", numList->phoneNumber);
            numList = numList->next;
        }
        fprintf(file, "===================================================\n\n");
        saveToFile(root->right, file);
    }
}

void loadFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return;
    }

    char line[256];
    char name[50];
    char phoneNumber[13];

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "Nama: %[^\n]", name) == 1) {
            while (fgets(line, sizeof(line), file) && sscanf(line, "Nomor Telepon: %[^\n]", phoneNumber) == 1) {
                insertData(name, phoneNumber);
            }
        }
    }

    fclose(file);
}
