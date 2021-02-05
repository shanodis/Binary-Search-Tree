#include <iostream>
#include <ctime>

#define MAX 50

using namespace std;

class BTree // main class of the tree
{
    struct body // body of the tree. Has left and right child
    {
        int data;
        struct body* left, * right;

    }*ptr;

public:
    BTree()
    {
        ptr = NULL;
    }
    ~BTree();
    void add_node(int data);
    void delete_tree(struct body* _ptr);
    void print(int option); // choosing print method with argument option
    int find_max_node();
    int find_min_node();

private:
    void create_tree(int data);
    
    // tree print methods 
    void print_preorder(struct body* _ptr);
    void print_inorder(struct body* _ptr);
    void print_postorder(struct body* _ptr);
};

void BTree::create_tree(int data)
{
    ptr = new struct body;
    ptr->data = data;
    ptr->left = ptr->right = NULL;
}

void BTree::add_node(int data)
{
    if(ptr == NULL)
    {
        create_tree(data);
        return;
    }

    struct body* new_node = ptr, * parent = ptr;
    while(new_node)
    {
        parent = new_node;

        if(new_node->data < data)
            new_node = new_node->right;
        else
            new_node = new_node->left;
    }
    new_node = new struct body;
    new_node->data = data;
    new_node->right = new_node->left = NULL;

    if(parent->data > new_node->data)
        parent->left = new_node;
    else
        parent->right = new_node;
}

void BTree::print_preorder(struct body* _ptr)
{
    if(_ptr)
    {
        cout << _ptr->data << " ";
        print_preorder(_ptr->left);
        print_preorder(_ptr->right);
    }
}

void BTree::print_inorder(struct body* _ptr)
{
    if(_ptr)
    {
        print_inorder(_ptr->left);
        cout << _ptr->data << " ";
        print_inorder(_ptr->right);
    }
}

void BTree::print_postorder(struct body* _ptr)
{
    if(_ptr)
    {
        print_postorder(_ptr->left);
        print_postorder(_ptr->right);
        cout << _ptr->data << " ";
    }
}

void BTree::print(int option)
{
    cout << "Tree print ";
    switch(option)
    {
    case 1:
        cout << "(preorder)\n";
        print_preorder(ptr);
        break;

    case 2:
        cout << "(inorder)\n";
        print_inorder(ptr);
        break;

    case 3:
        cout << "(postorder)\n";
        print_postorder(ptr);
        break;

    default:
        cout << "Invalid argument!\n";
        break;
    }
    cout << endl;
}

int BTree::find_max_node()
{
    struct body* tmp = ptr;
    while(tmp->right)
        tmp = tmp->right;

    return tmp->data;
}

int BTree::find_min_node()
{
    struct body* tmp = ptr;
    while(tmp->left)
        tmp = tmp->left;

    return tmp->data;
}

void BTree::delete_tree(struct body* _ptr)
{
    if(_ptr)
    {
        delete_tree(_ptr->left);
        delete_tree(_ptr->right);
        delete _ptr;
    }
}

BTree::~BTree()
{
    delete_tree(ptr);
    ptr = NULL;
}

int main() // testing tree
{
    BTree tree;

    srand(time(NULL));
    for(int i = 0; i < MAX; i++)
    {
        int value = 1 + rand() % 40;
        tree.add_node(value);
    }

    for(int i = 1; i <= 3; i++)
        tree.print(i);

    cout << "max. Node: " << tree.find_max_node() << endl;
    cout << "min. Node: " << tree.find_min_node() << endl;

    return 0;
}
