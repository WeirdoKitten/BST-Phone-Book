#include "phonebook.h"

node *root = NULL;

int height(node *N) {
    if (N == NULL)
        return 0;
    int leftHeight = height(N->left);
    int rightHeight = height(N->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int balanceFactor(node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

node *rightRotate(node *y) {
    node *x = y->left;
    node *T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

node *leftRotate(node *x) {
    node *y = x->right;
    node *T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

node *createNode(char inputName[50], char inputNumber[13])
{
    node *newNode = (node *)malloc(sizeof(node));
    numberList *newNumber = (numberList *)malloc(sizeof(numberList));
    if (newNode == NULL || newNumber == NULL) {
        printf("Gagal mengalokasikan memori\n");
        if (newNode != NULL) free(newNode);
        if (newNumber != NULL) free(newNumber);
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

node *minValueNode(node *node1) {
    node *current = node1;
    while (current->left != NULL)
        current = current->left;
    return current;
}

node *insertNode(node *root, char inputName[50], char inputNumber[13]) {
    if (root == NULL)
        return createNode(inputName, inputNumber);

    if (strcmp(inputName, root->name) < 0)
        root->left = insertNode(root->left, inputName, inputNumber);
    else if (strcmp(inputName, root->name) > 0)
        root->right = insertNode(root->right, inputName, inputNumber);
    else
        addPhoneNumber(root, inputNumber);

    int bf = balanceFactor(root);

    if (bf > 1 && strcmp(inputName, root->left->name) < 0)
        root = rightRotate(root);
    else if (bf < -1 && strcmp(inputName, root->right->name) > 0)
        root = leftRotate(root);
    else if (bf > 1 && strcmp(inputName, root->left->name) > 0) {
        root->left = leftRotate(root->left);
        root = rightRotate(root);
    } else if (bf < -1 && strcmp(inputName, root->right->name) < 0) {
        root->right = rightRotate(root->right);
        root = leftRotate(root);
    }

    return root;
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

    root = insertNode(root, formattedName, inputNumber);
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
    else {
        if (root->left == NULL || root->right == NULL) {
            node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                freeNumberList(root->phoneNumberS);
                free(root);
                root = NULL;
            } else {
                *root = *temp;
                freeNumberList(temp->phoneNumberS);
                free(temp);
            }
        } else {
            node *temp = minValueNode(root->right);
            strcpy(root->name, temp->name);
            root->phoneNumberS = temp->phoneNumberS;
            root->right = deleteContact(root->right, temp->name);
        }
    }

    if (root == NULL)
        return root;

    int bf = balanceFactor(root);

    if (bf > 1 && balanceFactor(root->left) >= 0)
        root = rightRotate(root);
    else if (bf > 1 && balanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        root = rightRotate(root);
    } else if (bf < -1 && balanceFactor(root->right) <= 0)
        root = leftRotate(root);
    else if (bf < -1 && balanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        root = leftRotate(root);
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

void updateContact(node *root, const char *inputName, const char *newName, char newNumber[13], int isRecursive)
{
    if (root == NULL)
    {
        printf("Kontak tidak ditemukan\n");
        return;
    }

    if (strcmp(inputName, root->name) < 0)
        updateContact(root->left, inputName, newName, newNumber, 1);
    else if (strcmp(inputName, root->name) > 0)
        updateContact(root->right, inputName, newName, newNumber, 1);
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
        if(!isRecursive){
        saveToFile(root, "data.txt");
        printf("Kontak berhasil diperbarui\n");
        }
    }
}
