<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include<string.h>
//#include "hashfunc.h"
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
=======
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
//#include "skiplist.h"
#include "hashfunc.h"
#include "RBtree.h"
int arr[25000];
#define ARR_SIZE(arr) (sizeof((arr))/sizeof((arr[0])))

void RandomStringtoRbtree(int n)
{
  //  FILE * fp;
   // fp = fopen("temp.txt","w");
    RBT  t;
    init(&t);
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
         s[a] = '\0';
         insert(&t,s);
     //    printf("%d ",i);
        // fprintf(fp,"%s\n",s);

    }
    Inorder(t);
   // remove_Node(&t,"");
   // printf("\n");
  //  printf("Hi");
  //  Inorder(t);
}

int main()
{
   /* SkipList * l = (SkipList *)malloc(sizeof(SkipList));
    initSkipList(l);
    l->hieght = 0;
    display(l);
    //l->sknext = newNode(INT_MIN,"0");
  //  display(l);
    SkipListinsert(l,25,"Gourav");
    //printf("%d ",l->sknext->key);
    SkipListinsert(l,19,"Rohan");
    SkipListinsert(l,27,"Vineet");
    SkipListinsert(l,55,"Kedar");
    SkipListinsert(l,5,"Yash");
    SkipListinsert(l,43,"Shyam");
    SkipListinsert(l,2,"Shiv");
    display(l);*/
  /*  char sr[200] = "br-icloud.com.br";
    long int a1 = hash1(sr);
    long int b1 = hash2(sr);
    long int c1 = hash3(sr);
    arr[a1] = 1;
    arr[b1] = 1;
    arr[c1] = 1;
  

    printf("%ld %ld %ld\n", a1, b1, c1);*/

   /* printf("%d %d %d %d\n", arr[a1], arr[b1], arr[c1], arr[d1]);
    char sr1[200] = "br-icloud.com.br ";
    long int a2 = hash(sr1);
    long int b2 = hash5(sr1);
    long int c2 = strlen(sr1);
    long int d2 = MurmurHash3(sr1, seed);

    printf("%ld %ld %ld %ld\n", a2, b2, c2, d2);
    if (arr[a2] == 1 && arr[b2] == 1 && arr[c2] == 1 && arr[d2] == 1)
    {
        printf("Yes , it is there");
    }
    else
    {
        printf("No , it is definitely not present");
    }
    // fclose(ptr);
    return 0;*/
    RandomStringtoRbtree(15000);
    return 0;
}
>>>>>>> 31d2fcc4a029cc908b64c591e3cc852f1ae167ed
