#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include<string.h>
#include "RBtree.h"

void init(RBT * t)
{
    *t = NULL;
    return;
}

Node * newNode(char * data)
{
    Node * p = (Node *)malloc(sizeof(Node));
    p->colour = 1; //new node as red
    p->data = data;
    p->left = NULL;
    p->parent = NULL;
    p->right = NULL;
    return p;
}

Node* uncle(Node * a)  // function to return node pointing at uncle of node 'a'
{
    Node* GRF = a->parent->parent;  // GRF - grandfather
    if (GRF != NULL)
    {
        if (strcmp(a->data,GRF->data)<0)
        {
            return GRF->right;
        }
        else
        {
            return GRF->left;
        }
    }
}

void leftrotate(RBT * t,Node * n)
{
    Node * A = n;
    Node * B = A->right;
    Node * Bl = B->left;
    A->right = Bl;
    if(Bl!=NULL)
    {
        Bl->parent=A;
    }
    B->left = A;
    if(A->parent==NULL)
    {
        *t = B;
    }
    else
    {
        if(A->parent->left==A)
            A->parent->left = B;
        else
            A->parent->right = B;
    }

    B->parent = A->parent;
    A->parent = B;
}

void rightrotate(RBT * t, Node * n)
{

    Node * A = n;
    Node * B = A->left;
    Node * Br = B->right;
    A->left = Br;
    if(Br!=NULL)
    {
        Br->parent = A;
    }
    B->right= A;
    if(A->parent==NULL)
    {
        *t = B;
    }
    else
    {
        if(A->parent->left==A)
            A->parent->left = B;
        else
            A->parent->right = B;
    }

    B->parent = A->parent;
    A->parent = B;
}

void left_right(RBT * t, Node * n)
{
    leftrotate(t,n->left);
    rightrotate(t,n);
}

void right_left(RBT * t,Node * n)
{
    rightrotate(t,n->right);
    leftrotate(t,n);
}

void insert(RBT * t,char * data)
{
    Node * n = newNode(data); //new Node
    if(*t == NULL)
    {
        *t = n;
        n->colour = 0; // making root as black
        return;
    }
    Node * p = *t;
    Node * q = NULL;
    while(p != NULL)  // finding appropriate positon
    {
        q = p;
        if(strcmp(p->data,data)<0)
        {
            p = p->right;
        }
        else if(strcmp(p->data,data)>0)
        {
            p = p->left;
        }
    }
    if(strcmp(q->data,data)>0) // checking leaf node and inserting
    {
        q->left = n;
    }
    else if(strcmp(q->data,data)<0)
    {
        q->right = n;
    }
    n->parent = q; // connecting newnode parent to q(leaf node)

    while(n->parent != NULL)
    {
        if(q->colour == 0)//there is no red red conflict
        {
            //printf("No Conflict\n");
            return;
        }
        else
        {
           // printf("Conflict\n");
            Node * unc = uncle(n); // finding uncle of newnode n;
            if(unc!=NULL && unc->colour == 1)  // if both uncle and parent are red(case 1)
            {
              //  printf("BOth red");
                unc->colour = 0;//recoloring both uncle and parent(q);
                q->colour = 0;
                if(q->parent != *t)
                {
                    q->parent->colour = 1; // if grandfather is not root node than recoloring grandfather
                }
                n = q->parent;//traversing up
                q = n->parent;
            }
            else if(unc==NULL || unc->colour == 0) // if uncle is black or null (case2)
            {
              //  printf("Uncle black");
                Node * GRF = n->parent->parent;
                if((strcmp(n->data,GRF->data)<0) && (strcmp(n->data,q->data)<0)) // left left imbalance
                {
                    rightrotate(t,GRF);
                    if(GRF->colour == 0)
                    {
                        GRF->colour = 1;
                    }
                    else
                    {
                        GRF->colour = 0;
                    }
                    if(n->parent->colour == 0)
                    {
                        n->parent->colour = 1;
                    }
                    else
                    {
                        n->parent->colour = 0;
                    }
                    n = n->parent;
                    q = n->parent;
                }
                else if((strcmp(n->data,GRF->data)>0) && (strcmp(n->data,q->data)>0)) // right right imbalance
                {
                    leftrotate(t,GRF);
                    if(GRF->colour == 0)
                    {
                        GRF->colour = 1;
                    }
                    else
                    {
                        GRF->colour = 0;
                    }
                    if(n->parent->colour == 0)
                    {
                        n->parent->colour = 1;
                    }
                    else
                    {
                        n->parent->colour = 0;
                    }
                    n = n->parent;
                    q = n->parent;
                }
                else if((strcmp(n->data,GRF->data)<0) && (strcmp(n->data,q->data)>0)) // left right imbalance
                {
                    left_right(t,GRF);
                    if(GRF->colour == 0)
                    {
                        GRF->colour = 1;
                    }
                    else
                    {
                        GRF->colour = 0;
                    }
                    if(n->colour == 0)
                    {
                        n->colour = 1;
                    }
                    else
                    {
                        n->colour = 0;
                    }
                    q = n->parent;
                }
                else // right left imbalance
                {
                    right_left(t,GRF);
                    if(GRF->colour == 0)
                    {
                        GRF->colour = 1;
                    }
                    else
                    {
                        GRF->colour = 0;
                    }
                    if(n->colour == 0)
                    {
                        n->colour = 1;
                    }
                    else
                    {
                        n->colour = 0;
                    }
                    q = n->parent;
                }
            }

        }
    }
}
void inorder(Node * n)
{
    if (n==NULL){
        return;
    }
    inorder(n->left);
    if (n->colour == 0)
    {
        printf("%s -> black\n",n->data);
    }
    else if (n->colour == 1)
    {
        printf("%s -> red\n",n->data);
    }
    else
    {
        printf("%s -> DB\n",n->data);
    }
    inorder(n->right);
}


