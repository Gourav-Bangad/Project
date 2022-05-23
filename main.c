#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct Node
{
    int key;
    char * data;
    struct Node * next;
    struct Node * prev;
    struct Node * up;
    struct Node * down;
}Node;

typedef Node * List;
typedef struct SkipList
{
    int hieght;
    struct Node * sknext;
}SkipList;

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
}

int main()
{
    SkipList * l = (SkipList *)malloc(sizeof(SkipList));
    initSkipList(l);
    l->hieght = 0;
    display(l);
    //l->sknext = newNode(INT_MIN,"0");
  //  display(l);
    SkipListinsert(l,25,"Gourav");
    //printf("%d ",l->sknext->key);
    SkipListinsert(l,2,"Gouv");
    SkipListinsert(l,2532,"Goav");
    SkipListinsert(l,253,"Grav");
    SkipListinsert(l,215,"Gurav");
    display(l);
    return 0;
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Skiplist
{
    int data;
    struct Skiplist *up;
    struct Skiplist *down;
    struct Skiplist *right;
} Skiplist;

void display(Skiplist *top)
{
    Skiplist *bottom = top;
    Skiplist *next = top;

    while (bottom != NULL)
    {
        while (next != NULL)
        {
            printf("%d ", next->data);
            next = next->right;
        }
        bottom = bottom->down;
        next = bottom;
        printf("\n");
    }
}

int search(Skiplist *top, int num)
{
    Skiplist *find = top;
    Skiplist *q = top;
    // finding the place to insert the number
    while (find != NULL)
    {
        printf("Searching %d\n", num);
        while ((find->right != NULL) && (find->right->data <= num))
        {
            find = find->right;
        }
        if (find->down == NULL)
        {
            q = find;
        }
        find = find->down;
    }
    if (q->data == num)
    {
        return 1;
    }

    return 0;
}

void skiplistAdd(Skiplist *obj, Skiplist **top, int num)
{
    int max_level = 5;
    Skiplist *q = obj;
    Skiplist *head = obj;
    int level = 1;

    // if the element inserted is first element
    if (q->right == NULL)
    {
        q->right = (Skiplist *)malloc(sizeof(Skiplist));
        Skiplist *t = q;
        q = q->right;
        q->data = num;
        // printf("Inserting %d\n", num);
        q->down = NULL;
        q->right = NULL;
        // vertically increasing skiplist
        Skiplist *tmp = NULL;
        while (((rand() % 2) == 1) && level < max_level)
        {
            level++;
            t->up = (Skiplist *)malloc(sizeof(Skiplist));
            tmp = t->up;
            tmp->down = t;
            t = t->up;
            t->data = INT_MIN;
            t->up = NULL;

            q->up = (Skiplist *)malloc(sizeof(Skiplist));
            tmp = q->up;
            tmp->down = q;
            q = q->up;
            q->data = num;
            printf("Inserting %d inside while of first element\n", num);

            q->right = NULL;
            t->right = q;
            // maintaing a top pointer which points at the topmost infi
            *top = t;
        }
        return;
    }

    Skiplist *find = *top;
    // finding the place to insert the number
    while (find != NULL)
    {
        printf("Searching %d\n", num);
        while ((find->right != NULL) && (find->right->data < num))
        {
            find = find->right;
        }
        if (find->down == NULL)
        {
            q = find;
        }
        find = find->down;
    }

    //inserting the number
    Skiplist *p = NULL;
    if (q->right == NULL)
    {
        q->right = (Skiplist *)malloc(sizeof(Skiplist));
        q = q->right;
        q->data = num;
        printf("Inserting other element %d when right is NULL\n", num);
        q->right = NULL;
        q->up = NULL;
        q->down = NULL;
    }
    else
    {
        p = q->right;
        q->right = (Skiplist *)malloc(sizeof(Skiplist));
        q = q->right;
        q->right = p;
        q->data = num;
        printf("Inserting other element %d when right is not NULL\n", num);
        q->down = NULL;
        q->up = NULL;
    }
    p = NULL;

    // vertically increasing other number
    while (((rand() % 2) == 1) && ((level < max_level)))
    {
        level++;
        q->up = (Skiplist *)malloc(sizeof(Skiplist));
        Skiplist *tmp = q->up;
        tmp->down = q;
        q = q->up;
        q->data = num;
        printf("Inserting %d inside while of other element\n", num);

        q->right = NULL;

        if (head->up == NULL)
        {
            head->up = (Skiplist *)malloc(sizeof(Skiplist));
            tmp = head->up;
            tmp->down = head;
            head = head->up;
            head->right = q;
            head->up = NULL;
            head->data = INT_MIN;
            q->right = NULL;
            printf("Connecting %d inside if head->up == NULL of while of other element\n", num);
            *top = head;
        }
        else
        {
            head = head->up;
            p = head;
            // int count = 1;
            while (p->right != NULL && p->right->data < num)
            {
                // printf("count = %d\n", count);
                p = p->right;
                // count++;
            }
            Skiplist *t = p->right;
            p->right = q;
            q->right = t;
            p = head;
        }
    }
}

int main()
{
    Skiplist *obj = (Skiplist *)malloc(sizeof(Skiplist));
    Skiplist *top = (Skiplist *)malloc(sizeof(Skiplist));
    obj->up = NULL;
    obj->down = NULL;
    obj->right = NULL;
    obj->data = INT_MIN;
    top = obj;
    skiplistAdd(obj, &top, 21);
    skiplistAdd(obj, &top, 24);
    skiplistAdd(obj, &top, 84);
    skiplistAdd(obj, &top, 42);
    skiplistAdd(obj, &top, 0);
    skiplistAdd(obj, &top, 63);

    if (search(top, 0))
    {
        printf("Found\n");
    }

    if (search(top, 1))
    {
        printf("Found\n");
    }
    else
    {
        printf("Not Found\n");
    }

    skiplistAdd(obj, &top, 14);
    skiplistAdd(obj, &top, 71);
    skiplistAdd(obj, &top, 100);
    skiplistAdd(obj, &top, 30);
    skiplistAdd(obj, &top, 47);
    skiplistAdd(obj, &top, 83);
    skiplistAdd(obj, &top, 64);
    printf("\n");
    display(top);
    return 0;
}*/
