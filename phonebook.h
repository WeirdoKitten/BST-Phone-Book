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

node* createNode(char inputName[50], char inputNumber[13]);
/*
    Penulis         : 
    Tujuan Prosedur : 
*/

void insertData(char inputName[50], char inputNumber[13]);
/*
    Penulis         : 
    Tujuan Prosedur : 
*/

void addPhoneNumber(node *personNode, char inputNumber[13]);
/*
    Penulis         : 
    Tujuan Prosedur : 
*/

void inputData();
/*
    Penulis         : 
    Tujuan Prosedur : 
*/

void printAllNode(node *currNode);
/*
    Penulis         : 
    Tujuan Prosedur : 
*/

void search(node *root, char inputName[50]);
/*
    Penulis         : 
    Tujuan Prosedur : 
*/

void saveToFile(node *root, FILE *file);
/*
    Penulis         : 
    Tujuan Prosedur : 
*/

void loadFromFile(const char *filename);
/*
    Penulis         : 
    Tujuan Prosedur : 
*/

void toCapitalizeCase(char str[]);
/*
    Penulis         : 
    Tujuan Prosedur : 
*/

#endif