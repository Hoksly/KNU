#include <iostream>
#include <vector>


using namespace std;


struct Point
{
    double x;
    double y;

};


double is_right(Point A, Point B, Point C)
{
    return (B.x - A.x) * (C.y - B.y) - (B.y - A.y) * (C.x - B.x);

}

Point take_point()
{
    Point ret;
    cin >> ret.x >> ret.y;
    return ret;

}

void swp(vector<int> &mas, int n1, int n2)
{
    int t;
    t = mas[n1];
    mas[n1] = mas[n2];
    mas[n2] = t;
    //delete &t;

}
void pr_vector(vector<int> A)
{
    for(int i = 0; i < A.size(); i++)
        cout << A[i] << ' ';
    cout << endl;
}

vector<Point> ballon(Point *A, int len_a)
{

    vector<int> P(len_a);
    //bool deleted[len_a];

    for(int i = 0; i < len_a; i++)
        P[i] = i;
    

    for (int i = 1; i < len_a; i++)
    {
        if(A[P[i]].x < A[P[0]].x)
            swp(P, 0, i);
    }

    vector<int> H;
   
    H.push_back(P[0]);
    int right;
    int c = 0;
    do
    {   
        //cout << "HERER1" << endl;
        right = 0;
        for (int i = 1; i < P.size(); i++)
        {
            if(is_right(A[H[H.size()-1]], A[P[right]], A[P[i]]) <= 0)
                {right = i; c++;}
            
        }
        
        cout << right << endl;
       
        
        if(P[right] == H[0])
        {
            //cout << "HERE" << H[0] << endl;
            break;
        }
            
        else
        {

            H.push_back(P[right]);
            P.erase(P.begin() + right);
        }
        //pr_vector(H);
        //pr_vector(P);
    }while (true);

    vector<Point> ret;
    for (int i = 0; i < H.size(); i++)
    {
        ret.push_back(A[H[i]]);
    }
    cout << c << endl;
    return ret;
}

void pr_vect(vector<Point> A)
{
    cout << endl << A.size() << endl;
    for(int i = 0; i < A.size(); i++)
    {
        cout << '(' << A[i].x << ", " << A[i].y << ')' << endl;
    }
}


int main()
{
    int n;
    cin >> n;
    Point mas[n];
    for(int i = 0; i < n; i++)
        cin >> mas[i].x >> mas[i].y;

    pr_vect(ballon(mas, n));

    
}