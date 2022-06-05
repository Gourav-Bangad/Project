#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "Redblack.h"
#include "randomstring.h"
#include "hashfunc.h"
#define ARR_SIZE(arr) (sizeof((arr))/sizeof((arr[0])))
//RBT t;

void RandomStringtoRbtree(int n,RBT * t)
{
   // FILE * fp;
   // fp = fopen("temp.txt","w");

    char c[]="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
   // int len[]={6,7,8,9,10,11,12,13,14};
    for (int i=0;i<n;i++)
    {
         int a  = rand()%(10);
        // printf("%d\n",a);
         if(a<6)
         {
             a = a+6;
         }
         //int a = 10;
         char * s = (char *)malloc(sizeof(char)*(a));
         for(int j=0;j<a;j++)
         {
             s[j] = c[rand()%(ARR_SIZE(c)-1)];
         }
         s[a]='\0';
         insert(t,s);
     //    printf("%d ",i);
    //     fprintf(fp,"%s\n",s);

    }

   // remove_Node(&t,"w2RlC6aVE");
   // printf("\n");
  //  printf("Hi");
  //  Inorder(t);
}

void insertinBloomfilter(RBT t,int arr[],int n)
{
    if(t==NULL)
        return;
    int a1 = hash1(t->data);
    int a2 = hash2(t->data);
    int a3 = hash3(t->data,123);
    int a4 = hash4(t->data);
    int a5 = hash5(t->data,123);
    arr[a1] = arr[a1] + 1;
    arr[a2] = arr[a2] + 1;
    arr[a3] = arr[a3] + 1;
    arr[a4] = arr[a4] + 1;
    arr[a5] = arr[a5] + 1;
   // printf("%d %d %d %d %d\n",a1,a2,a3,a4,a5);
    insertinBloomfilter(t->left,arr,n);
    insertinBloomfilter(t->right,arr,n);
}

int searchinBloomfilter(int arr[],int n,char * data)
{
    int a1 = hash1(data);
    int a2 = hash2(data);
    int a3 = hash3(data,123);
    int a4 = hash4(data);
    int a5 = hash5(data,123);
    if(arr[a1]!=0 && arr[a2]!=0 && arr[a3]!=0 && arr[a4]!=0 && arr[a5]!=0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
