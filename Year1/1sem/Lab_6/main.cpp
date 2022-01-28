#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <iomanip>
#include <cstring>


using coordinate = long double;

long double EPS = 1e-10;

struct Point;
coordinate Det2x2(coordinate a11, coordinate a12, coordinate a21, coordinate a22);
coordinate Det3x3(Point a, Point b, Point c);
Point VectorProduct(const Point& A, const Point& B, const Point& C);
double GetLenghtVector(Point A, Point B);
double GetAngle(const Point& n1, const Point& n2);
void print_mas(bool* mas, int n);


struct Point
{
    coordinate x;
    coordinate y;
    coordinate z;
    Point(coordinate x = 0, coordinate y = 0, coordinate z = 0) : x(x), y(y), z(z) {}
    Point operator-(const Point& other) const
    {
        return Point(x - other.x, y - other.y, z - other.z);
    }
    Point operator+(const Point& other) const
    {
        return Point(x + other.x, y + other.y, z + other.z);
    }
    bool operator!= (const Point& other) const
    {
        return (x != other.x || y != other.y || z != other.z);
    }
    bool operator== (const Point& other) const
    {
        return (x == other.x && y == other.y && z == other.z);
    }
};

coordinate Det2x2(coordinate a11, coordinate a12, coordinate a21, coordinate a22)
{
    return a11 * a22 - a12 * a21;
}


Point VectorProduct(const Point& A, const Point& B, const Point& C)
{
    Point a = B - A;
    Point b = C - A;
    return Point (Det2x2(a.y, a.z, b.y, b.z),
                  Det2x2(a.x, a.z, b.x, b.z),
                  Det2x2(a.x, a.y, b.x, b.y));
}


double GetLenghtVector(Point A, Point B = Point(0, 0, 0))
{
    Point vec = B - A;
    double lenght = std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    return lenght;
}

double GetAngle(const Point& n1, const Point& n2)
{
    double len_n1 = GetLenghtVector(n1);
    double len_n2 = GetLenghtVector(n2);
    double scalar_prod = n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
    if (scalar_prod == 0)
    {
        return 0;
    }
    return std::acos((scalar_prod) / (len_n1 * len_n2));
}
coordinate Det3x3(Point a, Point b, Point c)
{
    return (a.x * Det2x2(b.y, b.z, c.y, c.z) - a.y * Det2x2(b.x, b.z, c.x, c.z) + a.z * Det2x2(b.x, b.y, c.x, c.y));
}
class ConvexHull
{
    struct Flatness
    {
        int first;
        int second;
        int third;
        Point normal; 
        Flatness(int first, int second, int third, Point normal) :
            first(first), second(second), third(third), normal(normal) {}
        int Another(int one, int two)
        {
            if ((one == first && two == second) || (one == second && two == first))
            {
                return third;
            }
            if ((one == first && two == third) || (one == third && two == first))
            {
                return second;
            }
            if ((one == third && two == second) || (one == second && two == third))
            {
                return first;
            }
            return -1; // error
        }
    };

    struct Edge
    {
        int first;
        int second;
        int flatness; 
        bool is_close = false;
        Edge(int first, int second, int flatness = -1, Point normal = Point(0, 0 , 0)):
                    first(first), second(second), flatness(flatness) {}
    };

    std::vector<Point> points_;
    std::vector<Flatness> verge_;
    std::vector<Edge> edges_;

    int count_; 

    int findMinZ() const;
    void findFirstFlatness();
    int returnIsEdgeInHull(int a, int b) const;
    void makeHull();

public:
    ConvexHull(const std::vector<Point>& points): points_(points), count_(points.size()) 
    {
        points_ = points;
        count_ = points.size();
        makeHull();
    }

    std::vector<Point> give_hull()
    {
        int sz = verge_.size();
        bool *mas = new bool[points_.size()];
        memset(mas, false, sz);
        
        for (int i = 0; i < sz; i++)
        {
            mas[verge_[i].first] = true;
            mas[verge_[i].second] = true;
            mas[verge_[i].third] = true;
            
            //std::cout << verge_[i].first << ' ' << verge_[i].second << ' ' << verge_[i].third << '\n';
            

        }
        int res = 0;
        std::vector<Point> ret;
        for(int i = 0; i < points_.size(); i++)
        {
            if(mas[i])
                ret.push_back(points_[i]);
            
        
        }
        return ret;
        
    }

};

void ConvexHull::makeHull()
{
    findFirstFlatness();
    std::stack<int> stack;
    stack.push(0);
    stack.push(1);
    stack.push(2);

    while (!stack.empty())
    {
        Point new_normal;
        Edge e = edges_[stack.top()]; 
        stack.pop();
        if (e.is_close)
        {
            continue;
        }
        int min_id = -1;
        double min_angle = 7;

        for (int i = 0; i < count_; ++i)
        {
            int another = verge_[e.flatness].Another(e.first, e.second);
            if (i != another && e.first != i && e.second != i)
            {
               
                Point current_normal = VectorProduct(points_[e.second], points_[e.first], points_[i]);
                double angle = GetAngle(current_normal, verge_[e.flatness].normal);

                if (min_angle > angle)
                {
                    min_angle = angle;
                    min_id = i;
                    new_normal = current_normal;
                }
            }
        }

        if (min_id != -1)
        {
            e.is_close = true; 
            int count_flatness = verge_.size(); 
            int first_edge_in_hull = returnIsEdgeInHull(e.first, min_id);
            int second_edge_in_hull = returnIsEdgeInHull(e.second, min_id);

            if (first_edge_in_hull == -1)
            {
                edges_.push_back(Edge(e.first, min_id, count_flatness));
                stack.push(edges_.size() - 1);
            }
            if (second_edge_in_hull == -1)
            {
                edges_.push_back(Edge(min_id, e.second, count_flatness));
                stack.push(edges_.size() - 1);
            }
            if (first_edge_in_hull != -1)
            {
                edges_[first_edge_in_hull].is_close = true;
            }
            if (second_edge_in_hull != -1)
            {
                edges_[second_edge_in_hull].is_close = true;
            }

            verge_.push_back(Flatness(e.first, e.second, min_id, new_normal));
        }

    } 
} 

int ConvexHull::findMinZ() const
{
    int min_id = 0;
    for (int i = 1; i < count_; ++i)
    {
        if (points_[i].z < points_[min_id].z ||
            (points_[i].z == points_[min_id].z && points_[i].y < points_[min_id].y) ||
            (points_[i].z == points_[min_id].z && points_[i].y == points_[min_id].y &&
                points_[i].x < points_[min_id].x))
        {
            min_id = i;
        }
    }
    return min_id;
}

void ConvexHull::findFirstFlatness()
{
    int first_point, second_point, third_point;
    first_point = findMinZ();
    double min_angle = 7;
    int min_id = -1;
    for (int i = 0; i < count_; ++i)
    {
        if (first_point == i)
        {
            continue;
        }
        Point start = points_[first_point];
        Point next = points_[i];
        double angle = GetAngle(start - next, next - Point(next.x, next.y, start.z));
        if (min_angle > angle)
        {
            min_angle = angle;
            min_id = i;
        }
    }
    second_point = min_id;

    min_angle = 7;
    min_id = -1;
    for (int i = 0; i < count_; ++i)
    {
        if (first_point == i || second_point == i)
        {
            continue;
        }
        Point normal = VectorProduct(points_[first_point], points_[second_point], points_[i]);
        double angle = GetAngle(Point(0, 0, 1), normal);
        if (min_angle > angle)
        {
            min_angle = angle;
            min_id = i;
        }
    }
    third_point = min_id;

   
    if (VectorProduct(points_[first_point], points_[second_point], points_[third_point]).z > 0)
    {
        std::swap (second_point, third_point);
    }
    Point new_normal = VectorProduct(points_[first_point], points_[second_point], points_[third_point]);
    verge_.push_back(Flatness(first_point, second_point, third_point, new_normal)); 
    edges_.push_back(Edge(first_point, second_point, 0));
    edges_.push_back(Edge(second_point, third_point, 0));
    edges_.push_back(Edge(third_point, first_point, 0));
}

int ConvexHull::returnIsEdgeInHull(int a, int b) const
{
    for (int i = 0; i < edges_.size(); ++i)
    {
        if ((edges_[i].first == a && edges_[i].second == b) ||
            (edges_[i].first == b && edges_[i].second == a))
        {
            return i;
        }
    }

    return -1;
}

void take_input(std::vector<Point> &A)
{
    using namespace std;
    int n; 
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        Point a;
        cin >> a.x >> a.y >> a.z;
        
        A.push_back(a);
        ConvexHull Hull(A);




    }

}

void clear_point(std::vector<Point> &A, double EPS)
{
    bool *mas = new bool[A.size()];
    int i1, j1, k1;
    
    for(auto i = A.begin(); i != A.end(); i++)
    {   
        if(!mas[i1])
            continue;

        for(auto j = A.begin(); j != A.end(); j++)
        {
            if (j == i || !mas[j1])
                continue;

            for(auto k = A.begin(); k != A.end(); k++)
            {
                if(k == i || k == j || !mas[k1])
                    continue;

                if (fabs(Det3x3(*i, *j, *k)) < EPS)
                    {
                        //A.erase(k)
                        mas[k1] = false;
                    }
                    
                    
                 k1++;     
            }

            j1++;
        }
        i1++;

        
    }

    i1 = 0;
    for(auto i = A.begin(); i != A.begin(); i++)
    {
        if(!mas[i1])
            A.erase(i);
        i1++;
    }
}

void print_vector(std::vector<Point> &A)
{
    int a = A.size();
    for(int i = 0; i < a; ++i)
        {
            std::cout << A[i].x << ' ' <<A[i].y << ' '<<A[i].z << '\n'; 
        }
}



int main()
{
    using namespace std;

    vector<Point> A;
    take_input(A);
    clear_point(A, EPS);
    //print_vector(A);
    
   
    ConvexHull Hull(A);
    vector<Point> res = Hull.give_hull();

    print_vector(res);
    
    
}
/*

7
0 0 0
1 2 0
-7 4 0
15 24 1
18 23 8
123 124 7
172 24 123


    def requestValidArl():
        while True:
            arl = 'ccc560b13f778d7f620ef1a0a4494a397cf8150450c41d961cf7ae0dd1a8935370a82838925e9e3a5b1458b39b9c92d655a9e8a5d732cd3e3c90f007aec2224f97df507e218317b50b48ed0d3a990a0d8ed9d56ec5eee55623c67efaf75d83df'
            if dz.login_via_arl(arl.strip()): break
            print('Error with arl')
        return arl


*/
