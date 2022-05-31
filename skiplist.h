/*typedef struct Node
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

void init(List * l);
Node * newNode(int key,char * data);
void initSkipList(SkipList * l);
void display(SkipList * L);
int search (SkipList * L,int data);
void SkipListinsert(SkipList * L,int key,char * data);*/