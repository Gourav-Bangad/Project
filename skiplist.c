/*#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "skiplist.h"

void init(List * l)
{
    *l = NULL;
    return;
}

Node * newNode(int key,char * data)
{
    Node * ptr = (Node *)malloc(sizeof(Node));
    ptr->key = key;
    ptr->data = data;
    ptr->next = NULL;
    ptr->prev = NULL;
    ptr->up = NULL;
    ptr->down = NULL;
    return ptr;
}

void initSkipList(SkipList * l)
{
    Node * p = newNode(INT_MIN,'\0');
    Node * q = newNode(INT_MAX,'\0');
    p->next = q;
    q->prev = p;
    List L;
    init(&L);
    L = p;
    l->sknext = L;
    l->hieght = 0;
    return ;
}

void display(SkipList * L)
{
    Node * low = L->sknext;
    Node * next = L->sknext;
    while(low!=NULL)
    {
        while(next!=NULL)
        {
            printf("%d ",next->key);
            printf("%s ",next->data);
            next = next->next;
        }
        low = low ->down;
        next = low;
        printf("\n");
    }
}

int search (SkipList * L,int data)
{
    Node * find = L->sknext;
    Node * ptr = L->sknext;
    while(find!=NULL)
    {
        while((find->next != NULL)&&(find->key <= data))
        {
            find = find->next;
        }
        if(find->down == NULL)
        {
            ptr = find;
        }
        find = find->down;
    }
    if(ptr->key == data)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void SkipListinsert(SkipList * L,int key,char * data)
{
    int max_level = 8;
    Node * q = L->sknext;
    Node * head = L->sknext;
    int lvl = 1;
    //first Node
    if(q->next==NULL)
    {
        q->next = (Node *)malloc(sizeof(Node));
        Node * ptr = q;
        q = q->next;
        q = newNode(key,data);
        Node * tmp = NULL;
        while(((rand()%2) == 1) && lvl<max_level)
        {
            lvl++;
            tmp = newNode(INT_MIN,"0");
            tmp = ptr->up;
            tmp->down = ptr;
            ptr = ptr->up;
            ptr->up = NULL;

            tmp = newNode(INT_MIN,"0");
            tmp = q->up;
            tmp->down = q;
            q= q->up;
            q->next = NULL;
            ptr->next = q;
            L->sknext = ptr;

        }
        return;
    }
    Node * f = L->sknext;//to find element
    while(f!=NULL)
    {
        while((f->next!=NULL) && (f->next->key < key))
        {
            f = f->next;
        }
        if(f->down == NULL)
        {
            q = f;
        }
        f = f->down;
    }
    Node * p = NULL;
    if(q->next == NULL)
    {
        q->next = newNode(key,data);
        q = q->next;
    }
    else
    {
        p = q->next;
        q->next = newNode(key,data);
        q = q->next;
        q->next = p;
    }
    p = NULL;
    while(rand()%2==1 && lvl<max_level)
    {
        lvl++;
        Node * tmp = newNode(key,data);
        q->up = tmp;
        tmp->down = q;
        q = q->up;
        if(head->up == NULL)
        {
            head->up = (Node *)malloc(sizeof(Node));
            tmp = head->up;
            tmp->down = head;
            head = head->up;
            head->next = q;
            head->up = NULL;
            head->key = INT_MIN;
            head->data ="0";
            q->next= NULL;
            L->sknext = head;
        }
        else
        {
            head = head->up;
            p = head;
            // int count = 1;
            while (p->next != NULL && p->next->key < key)
            {
                // printf("count = %d\n", count);
                p = p->next;
                // count++;
            }
            Node *t = p->next;
            p->next = q;
            q->next = t;
            p = head;
        }
    }
}*/