#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


typedef struct Car
{
    vector<int> path;

} *CarPtr;


typedef struct Street
{
    string name;
    int beg;
    int end;
    int len;

} *Sptr;



void TakeInput(int &D, int &I, int &S, int &V, int &F, vector<Sptr> &Streets, map<string, int> &SInex, vector<CarPtr> Cars, vector<vector<int>> &Graph)
{
    
    cin >> D >> I >> S >> V >> F;
    for(int i = 0; i < I; i++)
    {
        vector<int> s;
        Graph.push_back(s);
    }

    for(int i = 0; i < S; i++)
    {
        Sptr s = new Street;
        cin >> s->beg >> s->end >> s->name >>s->len;
        Streets.push_back(s);
        SInex.insert(make_pair(s->name, i));
        Graph[s->beg].push_back(s->end);


    }
    int p;
    string s;
    for (int i = 0; i < V; i++)
    {
        CarPtr car = new Car;
        for(int j = 0; j < p; j++)
        {   
                cin >> s;
                auto s_index = SInex.find(s);

                car->path.push_back(s_index->second);
                
        }
        Cars.push_back(car);
    }




}

int main()
{
    int D, I, S, V, F;
    vector<Sptr> Streets;
    map<string, int> SInex;
    vector<CarPtr> Cars;
    vector<vector<int>> Graph;

    ifstream ifile;

    


}