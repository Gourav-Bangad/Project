typedef struct Node{
    char * data;
    int colour;  // 0 - black, 1 - red, -1 - double black
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;

typedef Node * RBT;

void init(RBT * t);
Node * newNode(char * data);
Node* uncle(Node * a);
void leftrotate(RBT * t,Node * n);
void rightrotate(RBT * t, Node * n);
void left_right(RBT * t, Node * n);
void right_left(RBT * t,Node * n);
void insert(RBT * t,char * data);
void inorder(Node * n);



