#include "rules.hpp"

// A - A = 0
bool simple_minus(Lexeme * Node)
{
    if(Node->oper == Minus)
    {
        if(NotNULL(Node->right_child, Node->left_child))
        {
            if(*(Node->left_child) == *(Node->right_child))
            {
                Node->clear(); // it also deltes node, no need in usage of 'delete Node;'
                Node = new Lexeme((double) 0);
                return true;
            }
        }
    }

    return false;
}
bool simple_plus(Lexeme *Node)
{
    if(Node->oper == Plus)
    {
        if(NotNULL(Node->right_child, Node->left_child))
        {
            if(*(Node->left_child) == *(Node->right_child))
            {
                Node->left_child->clear(); // it also deltes node, no need in usage of 'delete Node;'
                Node->oper = Mult;
                Node->left_child = new Lexeme((double) 2);
                return true;
            }
        }
    }
    return false;
}
//A + C*A

//      +                  *
//   A     *            A     +
//       C   A    =>         C  1
//
//
//
bool simple_left_plus(Lexeme * Node)
{
    if(Node->oper = Plus)
    {
        if(NotNULL(Node->right_child, Node->left_child))
        {
            if(Node->right_child->oper == Mult)
            {
                if(*Node->right_child->right_child == *Node->left_child) // If right child is equal to val, then left is value that mult on our value
                {
                    Node->right_child->oper = Plus;
                    Node->right_child->right_child->clear();
                    Node->right_child->right_child = new Lexeme((double) 1);
                    return true;
                }                

                if(*Node->right_child->left_child == *Node->left_child)
                {
                    Node->right_child->oper = Plus;
                    Node->right_child->left_child->clear();
                    Node->right_child->left_child = new Lexeme((double) 1);
                    return true;
                }
            }

        }
    }
    return false;

}

//C*A + A
bool simple_right_plus(Lexeme * Node)
{
    if(Node->oper = Plus)
    {
        if(NotNULL(Node->right_child, Node->left_child))
        {
            if(Node->left_child->oper == Mult)
            {
                if(*Node->left_child->right_child == *Node->right_child) // If right child is equal to val, then left is value that mult on our value
                {
                    Node->left_child->oper = Plus;
                    Node->left_child->right_child->clear();
                    Node->left_child->right_child = new Lexeme((double) 1);
                    return true;
                }                

                if(*Node->left_child->left_child == *Node->left_child)
                {
                    Node->left_child->oper = Plus;
                    Node->left_child->left_child->clear();
                    Node->left_child->left_child = new Lexeme((double) 1);
                    return true;
                }
            }

        }
    }
    return false;
}


//      +                  *
//   *     *            A     +
// A   K  C   A    =>       C   K
//
//
//
bool complex_plus(Lexeme * Node)
{
    if (Node->oper == Plus)
    {   
        if(NotNULL(Node->right_child, Node->left_child) && Node->right_child->oper == Mult && Node->left_child->oper == Mult)
        {
            if(*Node->right_child->right_child == *Node->left_child->right_child)
            {
                Node->oper = Mult;
                Node->right_child->oper = Plus;

                Lexeme * tmp = Node->left_child->right_child; // A
                
                Node->right_child->right_child->clear(); // deleting right A
                Node->right_child->right_child = Node->left_child->left_child; //moving K to the right
                Node->left_child->del(); // del of left operator
                Node->left_child = tmp;

                return true;
            }
            else if(*Node->left_child->right_child == *Node->right_child->left_child)
            {
              
                Node->oper = Mult;
                Node->right_child->oper = Plus;

                Lexeme * tmp = Node->left_child->right_child; // A
                
                Node->right_child->left_child->clear(); // deleting right A
                Node->right_child->left_child = Node->left_child->left_child; //moving K to the right
                Node->left_child->del(); // del of left operator
                Node->left_child = tmp;

                return true;
            }

            else if(*Node->left_child->left_child == *Node->right_child->left_child)
            {
               
                Node->oper = Mult;
                Node->right_child->oper = Plus;

                Lexeme * tmp = Node->left_child->left_child; // A
                
                Node->right_child->left_child->clear(); // deleting right A
                Node->right_child->left_child = Node->left_child->right_child; //moving K to the right
                Node->left_child->del(); // del of left operator
                Node->left_child = tmp;

                return true;
            }

            else if(*Node->left_child->left_child == *Node->right_child->right_child)
            {
                
                Node->oper = Mult;
                Node->right_child->oper = Plus;

                Lexeme * tmp = Node->left_child->left_child; // A
                
                Node->right_child->right_child->clear(); // deleting right A
                Node->right_child->right_child = Node->left_child->right_child; //moving K to the right
                Node->left_child->del(); // del of left operator
                Node->left_child = tmp;

                return true;
            }

            
        }    
    }

    return false;
    

}

inline bool is_const(Lexeme * Node) // Is it right to use inline here?
{
    return Node->_type == Constant;
}

bool add_constants(Lexeme * Node)
{
    if(Node->oper == Plus)
    {
        if(NotNULL(Node->right_child, Node->left_child) && is_const(Node->right_child) && is_const(Node->left_child))
        {
            double n_val = *Node->left_child->value + *Node->right_child->value;
            Node->clear();
            Node = new Lexeme(n_val);
            return true;
        }
    }

    return false;
}

bool mult_constants(Lexeme * Node)
{
    if(Node->oper == Mult)
    {
        if(NotNULL(Node->right_child, Node->left_child) && is_const(Node->right_child) && is_const(Node->left_child))
        {
            double n_val = (*Node->left_child->value) * (*Node->right_child->value);
            Node->clear();
            Node = new Lexeme(n_val);
            return true;
        }
    }

    return false;
}

bool div_constants(Lexeme * Node)
{
    if(Node->oper == Div)
    {
        if(NotNULL(Node->right_child, Node->left_child) && is_const(Node->right_child) && is_const(Node->left_child))
        {
            double n_val = (*Node->left_child->value) / (*Node->right_child->value);
            Node->clear();
            Node = new Lexeme(n_val);
            return true;
        }
    }

    return false;
}

bool subs_constants(Lexeme * Node)
{
    if(Node->oper == Minus)
    {
        if(NotNULL(Node->right_child, Node->left_child) && is_const(Node->right_child) && is_const(Node->left_child))
        {
            double n_val = (*Node->left_child->value) - (*Node->right_child->value);
            Node->clear();
            Node = new Lexeme(n_val);
            return true;
        }
    }

    return false;
}
// adding unar minus into a constant
bool remove_const_minus(Lexeme *Node)
{
    if(Node->oper == Minus)
    {
        if(IsNull(Node->right_child) && is_const(Node->left_child))
        {
            double n_val = (*Node->left_child->value) * -1;
            Node->clear();
            Node = new Lexeme(n_val); 
            return true;
        }
    }
    return false;
}



bool collect_and_delete(Lexeme * Head, Lexeme * target)
{
    std::queue<Lexeme *> Q;
    return false;
}

bool remove_zero(Lexeme * Node)
{   
    //Binary operations
    if(Node->_type == Operator && NotNULL(Node->right_child, Node->left_child)) 
    {
        Lexeme * tmp;
        switch (Node->oper)
        {
        case Plus:
            if(Node->right_child->_type == Constant && *Node->right_child->value == 0)
            {
                tmp = Node->left_child;
                Node->right_child->del();
                Node->del();
                Node = tmp;
                return true;  
            }
            else if(Node->left_child->_type == Constant && *Node->left_child->value == 0)
            {

                tmp = Node->right_child;
                Node->left_child->del();
                Node->del();
                Node = tmp;
                return true;  
            }
            
            return false;
        
        
        case Minus:
            if(Node->right_child->_type == Constant && *Node->right_child->value == 0)
            {
                tmp = Node->left_child;
                Node->right_child->del();
                Node->del();
                Node = tmp;
                return true;  
            }
            else if(Node->left_child->_type == Constant && *Node->left_child->value == 0)
            {

                tmp = Node->right_child;
                Node->left_child->del();
                Node->del();
                Node = tmp;
                return true;  
            }
            return false;
        
        case Div:
            if(Node->right_child->_type == Constant && *Node->right_child->value == 0)
            {
                throw std::runtime_error("Division by zero detected. Aborting");
            }
            else if(Node->left_child->_type == Constant && *Node->left_child->value == 0)
            {
                tmp = Node->left_child;
                Node->right_child->clear();
                Node->del();
                Node = tmp;
                return true;  
            }
            return false;

        case Mult:
        if(Node->right_child->_type == Constant && *Node->right_child->value == 0)
            {
                tmp = Node->right_child;
                Node->left_child->clear();
                Node->del();
                Node = tmp;
                return true;  
            }
            else if(Node->left_child->_type == Constant && *Node->left_child->value == 0)
            {
                tmp = Node->left_child;
                Node->right_child->clear();
                Node->del();
                Node = tmp;
                return true;  
            }
            return false;
        
        default:
            return false;
        }
        
    }
    return false;
}