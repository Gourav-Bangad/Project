#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include<string.h>
#include "hashfunc.h"
#include "randomstring.h"
#include "Redblack.h"
int arr[100000];
int main()
{
    RBT t;
    init(&t);
    printf("Enter the number of random elements : ");
    int n;
    scanf("%d",&n);
    RandomStringtoRbtree(n,&t);
    Inorder(t);
   /* printf("Enter the element to be searched : ");
    char * str = (char*)malloc(sizeof(char)*20);
    scanf("%s",str);
    Node * ptr = searchRB(t,str);
    if(ptr!=NULL)
        printf("found");
    else
        printf("Present");*/
    for(int i = 0;i<100000;i++)
    {
        arr[i] = 0;
    }
    insertinBloomfilter(t,arr,100000);
    printf("Enter the element to be searched : ");
    char * str = (char*)malloc(sizeof(char)*20);
    scanf("%s",str);
    if(searchinBloomfilter(arr,100000,str))
        printf("May be Present\n");
    else
        printf("Definitely Not Present !!\n");
  //  printf("%d",arr[39662]);
    return 0;
}
