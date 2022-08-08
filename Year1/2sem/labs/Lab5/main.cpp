#include "lib/clases.hpp"
#include <string.h>
using namespace std;


int main()
{
    RBTree tree;
    char s[20];
    double k;
    while(true)
    {
        cin >> s;
        if(!strcmp(s, "add"))
        {
            cin >> k;
            tree.insert(k);
        }
        else if(!strcmp(s, "rm"))
        {
            cin >> k;
            if(tree.remove(k))
                cout << "Removed succesfully" << endl;
            else
                cout << "No such element in tree" << endl;
        }

        else if (!strcmp(s, "cl"))
        {
            tree.clear();
            cout << "Tree cleared" << endl;
        }

        else if (!strcmp(s, "fill"))
        {
            tree.clear();
            int a, b;
            cin >> a >> b;
            for(; a < b; a++)
                tree.insert(a);
        }
        else if (!strcmp(s, "pr"))
        {
            tree.print();
        }
        else if (!strcmp(s, "prb"))
        {
            tree.print_br();
        }
        else if (!strcmp(s, "prbc"))
        {
            tree.print_brc();
        }
        else if (!strcmp(s, "ex"))
        {
            break;
        }
        else
        {
            cout << "No such comand" << endl;
        }
        

    }
}