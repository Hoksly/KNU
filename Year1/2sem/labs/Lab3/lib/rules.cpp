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
               
             
                Lexeme* NewNode = new Lexeme((double) 0);
                NewNode->parent = Node->parent;
                if(Node->parent->right_child == Node)
                    Node->parent->right_child = NewNode;
                if(Node->parent->left_child == Node)
                    Node->parent->left_child = NewNode;
                Node->clear();
                *Node = *NewNode;
                delete NewNode;
                
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
                
                Node->left_child->deep_clear(); // it also deltes node, no need in usage of 'delete Node;'
                Node->oper = Mult;
                Node->left_child = (new Lexeme((double) 2));
                Node->left_child->parent = Node;
               
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
    if(Node->oper == Plus)
    {   
        if(NotNULL(Node->right_child, Node->left_child))
        { 
            if(Node->right_child->oper == Mult)
            {
                
                
                if(*Node->right_child->right_child == *Node->left_child) // If right child is equal to val, then left is value that mult on our value
                {
                    Node->oper = Mult; // Is it right?
                    Node->right_child->oper = Plus;
                    Node->right_child->right_child->deep_clear();
                    Node->right_child->right_child = new Lexeme((double) 1);
                    Node->right_child->right_child->parent = Node->right_child;
                    return true;
                }                

                if(*Node->right_child->left_child == *Node->left_child)
                {
                    Node->oper = Mult;
                    Node->right_child->oper = Plus;
                    Node->right_child->left_child->deep_clear();
                    Node->right_child->left_child = new Lexeme((double) 1);
                    Node->right_child->left_child->parent = Node->right_child;
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
    if(Node->oper == Plus)
    {
        if(NotNULL(Node->right_child, Node->left_child))
        {
            if(Node->left_child->oper == Mult)
            {
                
                if(*Node->left_child->right_child == *Node->right_child) // If right child is equal to val, then left is value that mult on our value
                {
                    Node->oper = Mult; //?
                    Node->left_child->oper = Plus;
                    Node->left_child->right_child->clear();
                    Node->left_child->right_child = new Lexeme((double) 1);
                    Node->left_child->right_child->parent = Node->right_child;
                    return true;
                }                

                if(*Node->left_child->left_child == *Node->left_child)
                {
                    Node->oper = Mult; //?
                    Node->left_child->oper = Plus;
                    Node->left_child->left_child->clear();
                    Node->left_child->left_child = new Lexeme((double) 1);
                    Node->left_child->left_child->parent = Node->left_child;
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
{   //print("HEEEEEEEEEEEE");
    if(Node->oper == Plus)
    {
        //print("?");
        //print(Node->right_child->str_value());
        //print(Node->left_child->str_value());
        
        if(NotNULL(Node->right_child, Node->left_child) && is_const(Node->right_child) && is_const(Node->left_child))
        {
            
            double n_val = *Node->left_child->value + *Node->right_child->value;
            
            Lexeme* NewNode = new Lexeme((double) n_val);
            
            NewNode->parent = Node->parent;

            Node->clear();
         
            *Node = *NewNode;
            delete NewNode;
            //print(Node->str_value());
            return true;
        }
        else
        {
            if(Node->right_child->oper == Plus)
                return add_constants(Node->right_child);
             if(Node->left_child->oper == Plus)
                return add_constants(Node->left_child);
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
            Lexeme* NewNode = new Lexeme(n_val);
            
            NewNode->parent = Node->parent;
          
            Node->clear();
            *Node = *NewNode;
            delete NewNode;
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
            Lexeme* NewNode = new Lexeme(n_val);
            
            NewNode->parent = Node->parent;
          
            Node->clear();
            *Node = *NewNode;
            delete NewNode;
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
            Lexeme* NewNode = new Lexeme(n_val);
            
            NewNode->parent = Node->parent;
            
            Node->clear();
            *Node = *NewNode;
            delete NewNode;
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
            Lexeme* NewNode = new Lexeme(n_val);
            
            NewNode->parent = Node->parent;
           
            Node->clear();
            *Node = *NewNode;
            delete NewNode;
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

bool remove_zeroes(Lexeme * Node)
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
                tmp->parent = Node->parent;
                
                Node->del();
                *Node = *tmp; 
                return true;  
            }
            else if(Node->left_child->_type == Constant && *Node->left_child->value == 0)
            {
         
                tmp = Node->right_child;
                Node->left_child->del();
                tmp->parent = Node->parent;
            
                Node->del();
                *Node = *tmp; 
                return true;  
            }
            
            return false;
        
        
        case Minus:
            if(Node->right_child->_type == Constant && *Node->right_child->value == 0)
            {
                tmp = Node->left_child;
                Node->right_child->del();
                tmp->parent = Node->parent;
                
                Node->del();
                *Node = *tmp; 
                delete tmp;
                return true;  
            }
            else if(Node->left_child->_type == Constant && *Node->left_child->value == 0)
            {

                tmp = Node->right_child;
                Node->left_child->del();
                tmp->parent = Node->parent;
                
                Node->del();
                *Node = *tmp; 
                delete tmp;
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
                tmp->parent = Node->parent;
                Node->del();
                *Node = *tmp; 
                delete tmp;
                return true;  
            }
            return false;

        case Mult:
        if(Node->right_child->_type == Constant && *Node->right_child->value == 0)
            {
                tmp = Node->right_child;
                Node->left_child->clear();
                tmp->parent = Node->parent;
                if(Node->parent->right_child == Node)
                    Node->parent->right_child = tmp;
                if(Node->parent->left_child == Node)
                    Node->parent->left_child = tmp;
                Node->del();
                *Node = *tmp; 
                delete tmp;
                return true;  
            }
            else if(Node->left_child->_type == Constant && *Node->left_child->value == 0)
            {
                tmp = Node->left_child;
                Node->right_child->clear();
                tmp->parent = Node->parent;
                if(Node->parent->right_child == Node)
                    Node->parent->right_child = tmp;
                if(Node->parent->left_child == Node)
                    Node->parent->left_child = tmp;
                Node->del();
                *Node = *tmp; 
                delete tmp;
                return true;  
            }
            return false;
        
        default:
            return false;
        }
        
    }
    return false;
}


Lexeme* is_multiplied(Lexeme *Head, Lexeme *target, bool clear = false)
{
    if(Head->_type == Operator && Head->oper == Mult)
    {
        if(Head->left_child == target)
        {
            ////print("left");
            if(clear)
            {
                Head->left_child->clear();
                ////print("no");
                Lexeme *tmp = Head->right_child;
                Head->to_zeroes(); // it doesn't delete connection with it's parent
                double *val = new double(0);
                Head->to_const(val); // converting to 0
                return tmp;
            }

            return Head->right_child;
        }
        if(Head->right_child == target)
        {
            ////print("right");
            if(clear)
            {
                Head->right_child->clear();
                
                Lexeme *tmp = Head->left_child;
                Head->to_zeroes(); // it doesn't delete connection with it's parent
                double *val = new double(0);
                Head->to_const(val); // converting to 0
             

                return tmp;
            }

            return Head->right_child;
        }
    }
    return nullptr;
}

// going only with connection + A - A and C*A
void gather(Lexeme *Head, Lexeme *target, bool pos, std::vector<std::pair<Lexeme *, bool>> &values)
{
    ////print("gathering");
    ////print(Head->str_value());
    if(IsPorM(Head->oper)) // if it is plus or Minus
    {
        ////print("starting");
        if(Head->oper == Minus)
            pos = !pos;
        
        
        if(Head->right_child == target)
        {
            ////print("Right");
            if(Head->left_child)
                values.push_back(std::make_pair(new Lexeme((double) 1), pos));
            Head->right_child->clear();
            Head->right_child = new Lexeme((double) 0);
            Head->right_child->parent = Head;
        }
        else if(Head->left_child == target)
        {
            ////print("Left");
            if(Head->right_child)
                values.push_back(std::make_pair(new Lexeme((double) 1), pos));
            ////print("h");
            Head->left_child->clear();
            ////print("end");
            Head->left_child = new Lexeme((double) 0); // it doesn't delete connection with it's parent
            Head->left_child->parent = Head;
            
        }
        else 
        {
            gather(Head->right_child, target, pos, values);
            gather(Head->left_child, target, pos, values);
        }
    }

    if(Head->oper == Mult)
    {
        ////print("heree");
        Lexeme *tmp = is_multiplied(Head, target, true);
        ////print((long) tmp);
        if(tmp)
            values.push_back(std::make_pair(tmp, pos));
        ////print("alright");
        ////print((int) values.size());
        return;
    }

    return;
    

    
}

void create(std::vector<std::pair<Lexeme*, bool>> &vals, Lexeme * Head)
{
    //Head is not operator
    if(vals.size() == 0)
        return;
    if(vals.size() > 1)
    {
        Lexeme * new_oper = new Lexeme((vals[0].second)?Plus: Minus);
        // it must have parent!
        if(!Head->parent)
            throw std::runtime_error("No parent in recursive creation, aborting");
        
        new_oper->parent = Head->parent;
        if(Head->parent->right_child == Head)
            Head->parent->right_child = new_oper;
        
        if(Head->parent->left_child == Head)
            Head->parent->left_child = new_oper;

        
        Head->parent = new_oper;
        new_oper->right_child = Head;
        
        new_oper->left_child = vals[0].first;
        vals[0].first->parent = new_oper;

        vals.erase(vals.begin());
        create(vals, Head);
    }
}
// It creates not balanced tree, can be rewrited to balanced by dividing vector by 2 every time
void create_from_vec(std::vector<std::pair<Lexeme*, bool>> &vals, Lexeme * Head = nullptr)
{
    double all_vals = 0;
    ////print("SIZE");
    ////print((int) vals.size());
    for(int i = 0; i < vals.size(); ++i)
    {
        
         
        if(vals[i].first->_type == Constant)
        {   ////print("duck");
            all_vals += (vals[i].second)?*vals[i].first->value: *vals[i].first->value * -1 ; //depending on second val adds this const or it's negative value
            vals[i].first->clear();
            ////print("sss");
            vals.erase(vals.begin() + i);
        }
    }
   
    if(!Head)
        Head = new Lexeme(all_vals);
    else
    {   
        Lexeme *n_val = new Lexeme(all_vals);
        //print("New value: " +n_val->str_value());
        vals.push_back(std::make_pair(n_val, true));
    }

    create(vals, Head);

    
    
}
bool gather_and_replace(Lexeme *Head, Lexeme *target)
{

    //print("F");
    std::vector<std::pair<Lexeme*, bool>> values;
    gather(Head, target, true, values);
    //print("finished");
    
    if(!values.empty() && Head->_type == Operator) // Adding of new child with small recreation
    {
        bool last = values.size() > 1;
        Lexeme *right_tmp, *left_tmp, *n_head;
        right_tmp = Head->right_child; 
        left_tmp = Head->left_child;
        // Creating copy of head with new connections
        n_head = new Lexeme();
        *n_head = *Head;
        
        
        n_head->parent = Head;
        //print(Head->str_value());
        n_head->right_child->parent = n_head;
        //print("mid");
        n_head->left_child->parent = n_head;
        //print("mid2");
        Head->to_zeroes(); // it saves connection with parent
        Head->to_oper(Plus);
        Head->left_child = n_head;
        Head->right_child = new Lexeme(Mult);
        Head->right_child->left_child = target;
        Head->right_child->right_child = new Lexeme((double) 0);
        Head->right_child->parent = Head;
        
        create_from_vec(values, Head->right_child->right_child);
        //printb(last);
        return last;
    }
    else if (!values.empty())
    {
        bool last = values.size() > 1;
        Lexeme *tmp_head = new Lexeme();
        *tmp_head = *Head;
        tmp_head->parent = Head;
        Head->to_zeroes();
        Head->to_oper(Plus);
        
        Head->left_child = tmp_head;
        Head->right_child = new Lexeme(Mult);
        Head->right_child->left_child = target;
        target->parent = Head->right_child;
        Head->right_child->right_child = new Lexeme((double) 0);
        Head->right_child->right_child->parent = Head->right_child;
        Head->right_child->parent = Head;
        Head->left_child->parent = Head;
        
        
        create_from_vec(values, Head->right_child->right_child);
        
        //printb(last);
        return last;

    }

    return false;
}



bool call_gather(Lexeme *Head, Lexeme *target = nullptr)
{
    std::string s;
    //printTreeSx(Head, s);
    //print(s);

    bool was = false;
    if(target && target->_type != Operator)
        return gather_and_replace(Head, target);
   
    if(target)
    {   
       
        was = was || (target->right_child)? call_gather(Head, target->right_child): false;
        was = was || (target->left_child)?call_gather(Head, target->left_child): false;
    }
    else
    {
        //print("H");
        was = was || (Head->right_child)? call_gather(Head, Head->right_child): false;
        was = was || (Head->left_child)?call_gather(Head, Head->left_child): false;
    }
    
    return was;
    
}

bool call(auto function, Lexeme * Head)
{   
    bool res = false;
    
    ////print(Head->left_child->str_value());
    ////print(Head->str_value());
    ////print(Head->right_child->str_value());
    res = res || function(Head);
    if(Head->right_child)
        res = res || function(Head->right_child);
    if(Head->left_child)
        res = res || function(Head->left_child);

    return res;
}




void Simplyfier::simplify(Lexeme * Head)
{
    //std::vector<auto> V; //can we use vector of fucntions here?

    //all funvtions above
    bool was_changed;
    
    while (true)
    {
        std::string s;
        //printTreeSx(Head, s);
        //print((long) Head);
        //print(s);
        //print(Head->str_value());
        was_changed = false;
        was_changed = was_changed || call(simple_left_plus, Head);
        ////print("a");
        was_changed = was_changed || call(simple_right_plus, Head);
        ////print("b");
        was_changed = was_changed || call(simple_plus, Head);
        ////print("c");
        was_changed = was_changed || call(simple_minus, Head);
        ////print("d");
        was_changed = was_changed || call(complex_plus, Head);
        ////print("e");
        was_changed = was_changed || call(add_constants, Head);
        //print("f");
        was_changed = was_changed || call(mult_constants, Head);
        //print("g");
        was_changed = was_changed || call(div_constants, Head);
        //print("h");
        was_changed = was_changed || call(subs_constants, Head);
        //print("i");
        was_changed = was_changed || call(remove_const_minus, Head);
        //print("j");
        was_changed = was_changed || call(remove_zeroes, Head);
        //print("k");
        //print(std::to_string((long) Head));
        //was_changed = was_changed || call_gather(Head);

        if(!was_changed)
            break;
    }  
}