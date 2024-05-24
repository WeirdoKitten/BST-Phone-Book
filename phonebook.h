#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct node{
    char name[50];
    char phoneNumber[5][15];
    node *left;
    node *right;
} node;

extern node* root;

node* createNode(char inputName[50], char inputNumber[15]);
/*
    Penulis         : 
    Tujuan Prosedur : 
*/

void insertData(char inputName[50], char inputNumber[15]);
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

#endif