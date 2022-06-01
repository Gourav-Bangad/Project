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
        else
        {
            return;
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

void Inorder(Node * n)
{
    if (n==NULL){
        return;
    }
    Inorder(n->left);
    if(n->colour==0)
    {
        printf("%s-> black\n",n->data);
    }
    else if(n->colour == 1)
    {
        printf("%s->red\n",n->data);
    }
    Inorder(n->right);
}

Node * searchRB(RBT t,char * data)
{
    if(t==NULL)
    {
        return NULL;
    }
    if(strcmp(t->data,data)==0)
        return t;
    else if(strcmp(t->data,data)>0)
        return searchRB(t->left,data);
    else
        return searchRB(t->right,data);
}

Node * sibling(RBT t,Node * a)
{
    if(a->parent!=NULL)
    {
        if(a->parent->left==a)
            return a->parent->right;
        else
            return a->parent->left;
    }
}

Node * inorderPredecessor(Node * root)
{
    Node * ptr = root;
    ptr = ptr->left;
    while(ptr->right!=NULL)
    {
        ptr = ptr->right;
    }
    return ptr;
}

Node * inorderSuccesor(Node * root)
{
    Node * ptr = root;
    ptr = ptr->right;
    while(ptr->left!=NULL)
    {
        ptr = ptr->left;
    }
    return ptr;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void remove_Node(RBT *t , char * data)
{
    Node * ptr = searchRB(*t,data);
    delete_(t,ptr);
    return;
}

void delete_(RBT * t,Node * dn) // dn - node to be deleted
{
    if((dn->right==NULL)&&(dn->left==NULL)&&dn->colour==1)  //leaf node is red direct delete
    {
        if(dn->parent->left==dn)
            dn->parent->left=NULL;
        else
            dn->parent->right = NULL;
        free(dn);
    }
    else if((dn->right==NULL&&dn->left==NULL) && dn->colour==0 && dn == *t)  // if node to be deleted is black and is only node
    {                                                                        // present in tree direct delete it and make root null
        free(dn);
        *t = NULL;
    }
    else if((dn->right==NULL&&dn->left==NULL) && dn->colour==0)
    {
        dn->colour = -1;
        remove_Db(t,dn);
    }
    else
    {
        if(dn->right!=NULL)
        {
            Node * ios = inorderSuccesor(dn);
            strcpy(dn->data,ios->data);
            delete_(t,ios);
        }
        else if(dn->left!=NULL)
        {
            Node * iop = inorderPredecessor(dn);
            strcpy(dn->data,iop->data);
            delete_(t,iop);
        }
    }
    return;
}

int sib_red_away(RBT t,Node * dbn)  // will check if away node of sibling is red
{
    Node * sib = sibling(t,dbn);
    if(sib->parent->left==sib)
    {
        if(sib->left!=NULL)
        {
            if(sib->left->colour==1)
                return 1;
        }
    }
    else
    {
        if(sib->right!=NULL)
        {
            if(sib->right->colour == 1)
                return 1;
        }
    }
    return 0;
}
void remove_Db(RBT * t,Node * dbn)  // dbn - double black node
{
    if(dbn == *t)  // if dbn is root directly make it black and return
    {
        dbn->colour = 0;
        return;
    }
    else
    {
        Node * sib = sibling(*t,dbn) ; // finding sibling of dbn
        //If sibling of DB is black and both its children are black
        if((sib==NULL || sib->colour==0) && ((sib->left->colour==0 || sib->left== NULL)&&(sib->right->colour==0 || sib->right==NULL)))
        {
            if(dbn->left==NULL&&dbn->right==NULL)
            {
                if(dbn->parent->colour==0)
                    dbn->parent->colour=-1;//if parent is black make it double black
                else
                    dbn->parent->colour=0;//if parent is red make it black
                sib->colour = 1; // make sibling red
                if(dbn->parent->left==dbn)
                    dbn->parent->left = NULL;
                else
                    dbn->parent->right = NULL;
                free(dbn);
                if(sib->parent->colour == -1)
                    remove_Db(t,sib->parent);
                return;
            }
            else
            {
                if(dbn->parent->colour==0)
                    dbn->parent->colour=-1;//if parent is black make it double black
                else
                    dbn->parent->colour=0;//if parent is red make it black
                sib->colour = 1; // make sibling red
                if(dbn->parent->colour==-1)
                    remove_Db(t,dbn->parent);
                dbn->colour = 0;
                return;
            }
        }
        // if sibling color is red
        else if(sib->colour==1)
        {
            swap(&(sib->colour),&(sib->parent->colour));
            if(dbn->parent->left==dbn)  // rotate in direction of dbn
                leftrotate(t,dbn->parent);
            else
                rightrotate(t,dbn->parent);
            remove_Db(t,dbn);
        }
        //  If sibling of DB is black and its child far from DB is red
        else if(sib->colour==0 && (sib_red_away(*t,dbn)))
        {
            swap(&(dbn->parent->colour),&(sib->colour));
            if(dbn->parent->left==dbn)
            {
                dbn->parent->left = NULL;
                free(dbn);
                leftrotate(t,sib->parent);
                sib->right->colour = 0;
            }
            else if(dbn->parent->right==dbn)
            {
                dbn->parent->right = NULL;
                free(dbn);
                rightrotate(t,sib->parent);
                sib->left->colour = 0;
            }
            return;
        }
        //  If sibling of DB is black and its child near to DB is red
        else if(sib->colour==0 && !(sib_red_away(*t,dbn)))
        {
            if(dbn->parent->left==dbn)
            {
                swap(&(sib->colour),&(sib->left->colour));
                rightrotate(t,sib);
                remove_Db(t,dbn);
            }
            else if(dbn->parent->right==dbn)
            {
                swap(&(sib->colour),&(sib->right->colour));
                leftrotate(t,sib);
                remove_Db(t,dbn);
            }
            return;
        }
    }
}

