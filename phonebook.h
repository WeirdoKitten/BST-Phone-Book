#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

typedef struct numberList {
    char phoneNumber[13];
    struct numberList *next;
} numberList;

typedef struct node {
    char name[50];
    numberList *phoneNumberS;
    struct node *left;
    struct node *right;
} node;

extern node* root;

/* 
    Tujuan Prosedur : membuat node baru pada binary search tree yang berisi nama dan nomor telepon yang diinputkan.
*/
node* createNode(char inputName[50], char inputNumber[13]);

/* 
    Tujuan Prosedur : memasukkan data nama dan nomor telepon ke dalam binary search tree. Jika nama sudah ada, nomor telepon baru akan ditambahkan pada daftar nomor telepon yang dimiliki oleh node tersebut.
*/
void insertData(char inputName[50], char inputNumber[13]);

/* 
    Tujuan Prosedur : menambahkan nomor telepon baru pada daftar nomor telepon yang dimiliki oleh node tertentu.
*/
void addPhoneNumber(node *personNode, char inputNumber[13]);

/* 
    Tujuan Prosedur :  meminta input dari pengguna berupa nama dan nomor telepon, kemudian memanggil fungsi insertData untuk memasukkan data tersebut ke dalam binary search tree.
*/
void inputData(); 

/* 
    Tujuan Prosedur : mencetak semua data nama dan nomor telepon yang tersimpan dalam binary search tree secara inorder traversal.
*/
void printAllNode(node *currNode);

/* 
    Tujuan Prosedur : mencari node berdasarkan nama yang diinputkan, kemudian mencetak nama dan daftar nomor telepon yang dimilikinya.
*/
void search(node *root, char inputName[50], bool* found);

/* 
    Tujuan Prosedur : menyimpan semua data nama dan nomor telepon yang tersimpan dalam binary search tree ke dalam file eksternal.
*/
void saveToFile(node *root, const char *filename);

void writeToFile(node *root, FILE *file);

/* 
    Tujuan Prosedur : memuat data nama dan nomor telepon dari file eksternal ke dalam binary search tree.
*/
void loadFromFile(const char *filename);

/* 
    Tujuan Prosedur :  mengubah format penulisan nama menjadi kapital pada setiap huruf pertama kata.
*/
void toCapitalizeCase(char str[]);

/* 
    Tujuan Prosedur : mencari node dengan nilai paling kecil dalam subtree kanan dari node tertentu, yang digunakan dalam proses penghapusan node.
*/
node* findMin(node* root);

/* 
    Tujuan Prosedur : menghapus node berdasarkan nama yang diinputkan dari binary search tree.
*/
node* deleteContact(node *root, char inputName[50]);

/*
    Tujuan Prosedur : menghapus kontak saat node didelete
*/
void freeNumberList(numberList *numList);

/* 
    Tujuan Prosedur : memperbarui data nama dan/atau nomor telepon pada node tertentu dalam binary search tree. 
*/
void updateContact(node *root, const char *inputName, const char *newName, char newNumber[13], int isRecursive);

#endif