#ifndef RANDOMSTRING_H
#define RANDOMSTRING_H 1
#include "Redblack.h"
void RandomStringtoRbtree(int n,RBT* t);
void insertinBloomfilter(RBT t,int arr[],int n);
int searchinBloomfilter(int arr[],int n,char * data);
#endif
