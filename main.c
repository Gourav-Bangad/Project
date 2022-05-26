#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "skiplist.h"

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
