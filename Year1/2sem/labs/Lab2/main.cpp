#include "lib/classes.h"
//#include "lib/utils.h"
#include "lib/input.h"
#include "lib/const.h"
#include "lib/random.h"
#include "lib/sort.h"
#include <iostream>

#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;




vector<pair<long, long>> test()
{
    long START, diff, STOP, time ;
    START = 5000;
    diff = START;
    STOP = 1000000000;
    

    pair<vector<vector<String *>>, vector<vector<char>>> p;
    vector<pair<long, long>> ret;
    for(; START < STOP; START += diff )
    {
        
        p = give_set(START);
        
        auto start = high_resolution_clock::now();
        LecSort(p.second, p.first);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds> (stop - start);
        
        cout << START << ' ' << duration.count() << endl;
        
        ret.push_back(make_pair(START, duration.count()));
        
        //clearing memory
        for(auto v = p.first.begin(); v != p.first.end(); v++)
        {
            for(auto s = v->begin(); s != v->end(); s++)
            {
                delete (*s);
            }
            v->clear();
        }
        p.first.clear();

        for(auto v = p.second.begin(); v != p.second.end(); v++)
        {
            v->clear();
        }
        p.second.clear();
    


    }

    return ret;
}

void PrintVector(vector<String *> &V)
{
    for(auto v = V.begin(); v != V.end(); v++)
    {
        printf("%s\n", (*v)->mas);
    }

}

void chose()
{
    char filename[128], fileout[128], mode;
    cout << "File to sort: ";
    cin >> filename;
    //cout << endl;
    
    cout << "File out (Only for in-memory sort): ";
    cin >> fileout;
    //cout << endl;

    cout << "Mode: Out(O), In(I)";
    cin >> mode;
    cout<<"Processing..." << endl;

    if(mode == 'O' || mode == 'o')
        OutSort(filename);

    else
    {

        pair<vector<vector<String *>>, vector<vector<char>>> p;
        p = read_file(filename);
         vector<String *> res = LecSort(p.second, p.first);
        write_out(fileout, res);

    }
}
int main()
{

    
    
    
    //NotEmpty = p.second;

    //auto start = high_resolution_clock::now();
    chose();
    //auto stop = high_resolution_clock::now();
    //PrintVector(res);
    //test();
    

    
}