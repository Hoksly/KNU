#include <vector>
#include <iostream>

enum RBColor {Black, Red};

struct Node
{
    double value;
    
    
    RBColor color = Red;

    Node * right = nullptr;
    Node * left = nullptr;
    Node * parent = nullptr;

    Node(double);
    Node();


};

class RBTree
{
private:
    Node * nil, * Head;
    void FixInsestion(Node *);
    void FixDeletion(Node *, Node *);
    
    void lRotate(Node*);
    void rRotate(Node*);
    
    void remove(Node *);
    
    Node * Next(Node *); // the leftest node in right subtree
    
    void print(Node *);
    void print_br(Node *);
    void print_brc(Node *);
    Node* search(double key);
    Node* search(Node *,const  double&);
    void clear(Node *);

public:
    RBTree(std::vector<double>);
    void insert(double);
    bool remove(double);
    void clear();
    void print();
    void print_br();
    void print_brc();


    RBTree();
};