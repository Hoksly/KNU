#include "clases.hpp"

void pr(std::string s)
{
    std::cout << s << '\n';
}

Node::Node(double v)
{
    value = v;
    color = Red; // red by default
}

Node::Node()
{
    color = Black;
}

RBTree::RBTree()
{
    nil = new Node();
    nil->color = Black;

    Head = nil;
}

void RBTree::lRotate(Node *x)
{
    Node *y = x->right;
    x->right = y->left;

    if (y->left != nil)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr) // if we need rotate root
        Head = y;
    else
    {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RBTree::rRotate(Node *y)
{
    Node *x = y->left;
    y->left = x->right;

    if (x->right != nil)
        x->right->parent = y;

    x->parent = y->parent;
   
    if (y->parent == nullptr) // in case we rotate a root
        Head = x;
    else
    {
        if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

void RBTree::FixInsestion(Node *node)
{
    Node *parent = node->parent;
    while (node != Head && parent->color == Red)
    {
        Node *grandparent = parent->parent;
        if (grandparent && grandparent->left == parent)
        {
            
            Node *uncle = grandparent->right;
            
            // if uncle exists and his color is red
            if (uncle != nil && uncle->color == Red)
            {
                parent->color = Black;
                grandparent->color = Red;
                uncle->color = Black;

                // going up
                node = grandparent;
                parent = node->parent;
            }

            else
            {
                if (parent->right == node)
                {
                    lRotate(parent);
                    std::swap(node, parent);
                }
                
                rRotate(grandparent);
                grandparent->color = Red;
                parent->color = Black;
                break;
            }
        }
        else if (grandparent)
        {
            
            Node *uncle = grandparent->left;
            if (uncle != nil && uncle->color == Red)
            {
                
                grandparent->color = Red;
                parent->color = Black;
                uncle->color = Black;

                node = grandparent;
                parent = node->parent;
            }

            else
            {
                
                if (parent->left == node)
                {
                    
                    rRotate(parent);
                    std::swap(parent, node);
                }
                
                lRotate(grandparent);
                parent->color = Black;
                grandparent->color = Red;
                break;
            }
        }
    }

    Head->color = Black; // just in case
}

void RBTree::insert(double key)
{
    Node *x = Head;
    Node *y = nil; // y is a parent of x
    while (x != nil)
    {
        y = x;
        x = key < x->value ? x->left : x->right;
    }

    Node *newnode = new Node(key);
    newnode->left = newnode->right = nil;

    if (y == nil)
    {
        Head = newnode;
        newnode->color = Black;
    }

    else if (key < y->value)
    {
        (*y).left = newnode;
        newnode->parent = y;
        //std::cout << Head->value << '\n';
        //std::cout << "H " << key << ' ' << newnode->parent << '\n';
    }

    else
    {
        y->right = newnode;
        newnode->parent = y;
        //std::cout << Head->value << '\n';
        //std::cout << "P " << key << ' ' << y->value << '\n';
    }
    //print();
    if (newnode != Head && key != 14);
        {FixInsestion(newnode);}
}

Node *RBTree::Next(Node *z)
{
    
    Node *sub = z->right; // can change for z later, when optimize
    while (sub->left != nil)
    {
        sub = sub->left;
    }

    return sub;
}

void RBTree::FixDeletion(Node *node, Node* parent)
{
    Node *ch;
    while (node == nil || node->color == Black && node != Head)
    {
        if(parent->left = node)
        {
            ch = parent->right;
            if(ch->color == Red)
            {
                ch->color = Black;
                parent->color = Red;
                lRotate(parent);
                ch = parent->right;
            }
            else
            {
                if(ch->right == nil || ch->right->color == Black)
                {
                    ch->left->color = Black;
                    ch->color = Red;
                    rRotate(ch);
                    ch = parent->right;
                }

                ch->color = parent->color;
                parent->color = Black;
                ch->right->color = Black;
                
                lRotate(parent);
                node = Head;
                break;
            }
        }
        else
        {
            ch = parent->left;
            if(ch->color = Red)
            {
                ch->color = Black;
                parent->color = Red;
                rRotate(parent);
                ch = parent->left;
            }
            if((ch->left == nil || ch->left->color == Black) && (ch->right == nil  || ch->right->color == Black))
            {
                ch->color = Red;
                node = parent;
                parent = node->parent;
            }
            else
            {
           
                if(ch->left == nil || ch->left->color == Black)
                {
                    ch->right->color = Black;
                    ch->color = Red;
                    lRotate(ch);
                    ch = parent->left;
                }

                ch->color = parent->color;
                parent->color = Black;
                ch->left->color = Black;
                rRotate(parent);
                node = Head;
                break;
            }
        }
    }
    
    if(node != nil)
        node->color = Black;
}

void RBTree::remove(Node *node)
{
    Node *child, *parent;
    RBColor color;

    if(node->right != nil && node->left != nil)
    {
        Node * replace = node->right;
        while(replace->left != nil)
            replace = replace->left;
        

        
        if(node->parent != nullptr)
        {
            if(node->parent->left == node)
                node->parent->left = replace;
            else
                node->parent->right = replace;
        }
        else
            Head = replace;
        
        child = replace->right;
        parent = replace->parent;
        color = replace->color;

        if(parent == node)
            parent = replace;

        else
        {
            if(child != nil)
                child->parent = parent;
            parent->left = child;
            replace->right = node->right;
            node->right->parent = replace;
        }
        
        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        //situation with double black node
        if(color = Black)
            FixDeletion(child, parent);
    
        delete node;
        return; 
    }

    if(node->left != nil)
        child = node->left;
    else
        child = node->right;
    parent = node->parent;
    color = node->color;

    if(child != nil)
        child->parent = parent;
    
    if(parent != nil)
    {
        if(node == parent->left)
            parent->left = child;
        else
            parent->right = child;
    }
    else
        Head = child;
    
    
    //situation with double black node
    if(color == Black)
        FixDeletion(child, parent);
    
    delete node;
}

Node * RBTree::search(Node * node, const double &key)
{
    if(node == nil || node->value == key)
        return node;
    if(key > node->value)
        return search(node->right, key);
    else
        return search(node->left, key);
    
}

Node * RBTree::search(double key)
{
    return search(Head, key);
}


bool RBTree::remove(double key)
{
    Node * dnode = search(key);
    if(dnode != nil)
    {
    
        remove(dnode);
        return true;
    }

    return false;
}



void RBTree::print(Node *node)
{

    if (node == nil)
        return;
    std::cout << node->value << '\n';
    //std::cout << node << '\n';
    //std::cout << (int)(bool)(node->left == nil) << '\n';
    print(node->left);
    print(node->right);
}

void RBTree::print()
{

    print(Head);
}

void RBTree::print_br(Node *node)
{

    if (node == nil)
        return;
    std::cout << node->value;
    //std::cout << node << '\n';
    //std::cout << (int)(bool)(node->left == nil) << '\n';
    if(node->right != nil || node->left != nil)
        std::cout << '(';
    print_br(node->left);
    
    if(node->right != nil)
        std::cout << ", ";

    print_br(node->right);

    if(node->right != nil || node->left != nil)
        std::cout << ')';
}

void RBTree::print_br()
{

    print_br(Head);
    std::cout << '\n';
}
void RBTree::print_brc(Node *node)
{

    if (node == nil)
        return;
    std::cout << node->value;
    char c = (node->color == Black)? 'b':'r';
    std::cout << c;
    //std::cout << node << '\n';
    //std::cout << (int)(bool)(node->left == nil) << '\n';
    if(node->right != nil || node->left != nil)
        std::cout << '(';
    print_brc(node->left);
    
    if(node->right != nil)
        std::cout << ", ";

    print_brc(node->right);

    if(node->right != nil || node->left != nil)
        std::cout << ')';
}

void RBTree::print_brc()
{

    print_brc(Head);
    std::cout << '\n';
}
void RBTree::clear()
{
    clear(Head);
}

void RBTree::clear(Node * node)
{
    if(node == nil)
        return;
    clear(node->left);
    clear(node->right);
    delete node;

}