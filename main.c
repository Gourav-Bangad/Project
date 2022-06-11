#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "hashfunc.h"
#include "randomstring.h"
#include "Redblack.h"
int arr[100000];
int main()
{
    RBT t;
    init(&t);
    printf("Press 1 to insert random elements in Red black tree.\nPress 2 to insert a element in Red black tree.\n");
    printf("Press 3 to delete a element in Red black tree.\nPress 4 to search a element in BLOOM FILTER.\n");
    printf("Press 5 to search element in REDBLACK TREE\nPress 6 for inorder traversal of tree\nPress any other key to exit\n");
    while (1)
    {
        printf("Enter a digit : ");
        int i;
        scanf("%d", &i);
        if (i == 1)
        {
            printf("Enter the number of random elements : ");
            int n;
            scanf("%d", &n);
            RandomStringtoRbtree(n, &t);
        }
        else if (i == 2)
        {
            printf("Enter the element to be inserted : ");
            char *data = (char *)malloc(sizeof(char) * 15);
            scanf("%s", data);
            insert(&t, data);
        }
        else if (i == 3)
        {
            printf("Enter the element to be deleted : ");
            char *data = (char *)malloc(sizeof(char) * 15);
            scanf("%s", data);
            remove_Node(&t, data);
        }
        else if (i == 4)
        {
            for (int i = 0; i < 100000; i++)
            {
                arr[i] = 0;
            }
            insertinBloomfilter(t, arr, 100000);
            printf("Enter the element to be searched in Bloom filter : ");
            char *str = (char *)malloc(sizeof(char) * 20);
            scanf("%s", str);
            if (searchinBloomfilter(arr, 100000, str))
                printf("May be Present\n");
            else
                printf("Definitely Not Present !!\n");
        }
        else if (i==5)
        {
            printf("Enter the element to be searched in Redblack tree : ");
            char *str = (char *)malloc(sizeof(char) * 20);
            scanf("%s", str);
            Node * ptr = searchRB(t,str);
            if(ptr==NULL)
                printf("Not present in Red Black tree\n");
            else
                printf("Present in Redblack tree\n");
        }
        else if (i==6)
        {
            Inorder(t);
        }
        else
        {
            break;
        }
    }

    /* for(int i = 0;i<n;i++)
      {
          char * data = (char*)malloc(sizeof(char)*10);
          scanf("%s",data);
          insert(&t,data);
          Inorder(t);
      }*/
   // Inorder(t);
    /* printf("Enter the element to be searched : ");
     char * str = (char*)malloc(sizeof(char)*20);
     scanf("%s",str);
     Node * ptr = searchRB(t,str);
     if(ptr!=NULL)
         printf("found");
     else
         printf("Present");*/
  /*  for (int i = 0; i < 100000; i++)
    {
        arr[i] = 0;
    }
    insertinBloomfilter(t, arr, 100000);
    printf("Enter the element to be searched : ");
    char *str = (char *)malloc(sizeof(char) * 20);
    scanf("%s", str);
    if (searchinBloomfilter(arr, 100000, str))
        printf("May be Present\n");
    else
        printf("Definitely Not Present !!\n");
    //  printf("%d",arr[39662]);*/
    return 0;
}
