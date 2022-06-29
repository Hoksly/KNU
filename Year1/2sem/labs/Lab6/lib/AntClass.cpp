#include "AntClass.hpp"
using std::pair;

Ant::Ant(uchar n)
{
    allowed = new bool[n];
    Path = new uchar[n + 1];
}
Ant::~Ant()
{

    // std::cout << "ANT DESTRUCTOR" << '\n';
    delete allowed;
    delete Path;
}

inline void Ant::go_to(uchar node, uchar iter)
{

    // std::cout << path.capacity() << '\n';
    // std::cout << "SUCK?" << '\n';
    // path.push_back(current_node);
    Path[iter] = node;
    // std::cout << "SUCK" << '\n';
    // std::cout << "SIZE: " << path.size() << '\n';
    current_node = node;
}

uchar Ant::choose_next(bool *allowed, AntMap &Map, uchar from, uchar n_of_allowed)
{
    // std::cout << "ALLOWED: ";
    // print_mas(allowed, Map.n);
    // std::cout << n_of_allowed << '\n';
    uchar n = Map.n, cur = 0;
    // by using array instead of vector we will have O(n) asymptotic insted of O(n^2)
    // because vector.push_back on it's own has O(n) asympotic
    double total_len = 0;

    std::vector<pair<uchar, double>> chances(n_of_allowed);

    double val;
    for (uchar i = 0; i < n; ++i)
    {

        if (allowed[i])
        {
            val = pow(give_distance(Map.DistanceMap, i, from), ALPHA) + pow(give_feromon(Map.FeromonMap, i, from), BETA);
            // std::cout << "VAL: " << val << '\n';
            total_len += val;
            chances[cur] = std::make_pair(i, val);

            ++cur;
        }
    }
    // normalization
    for (uchar i = 0; i < n_of_allowed; ++i)
    {
        // std::cout << "NORM1: " << chances[i].second << ' ' << total_len << '\n';
        chances[i].second /= total_len;
        // std::cout << "NORM2: " << chances[i].second << ' ' << total_len << '\n';
    }

    double total = 0, chance;
    chance = ((double)rand()) / RAND_MAX;

    // shuffle chances?
    std::random_shuffle(chances.begin(), chances.end());

    for (uchar i = 0; i < n_of_allowed; ++i)
    {
        total += chances[i].second;
        // std::cout << "CHANCES: " << total << ' ' << chance << '\n';
        if (chance < total)
            return chances[i].first;
    }

    // no return needed here, but compiler throws warnings...

    // delete chances;
    //  std::cout << "HOLLY SHIT" << '\n';
    return 0;
}

void Ant::move(uchar begin, AntMap &Map)
{
    uchar n = Map.n, next;

    // std::cout << (int)Map.n << std::endl;
    current_node = begin;

    memset(allowed, true, n);
    // std::cout << "ALLOWED1: ";
    //  print_mas(allowed, Map.n);
    allowed[begin] = false;
    Path[0] = begin;

    // n-1 iterations if we have n nodes to visit and return to the begining
    // std::cout << "N: " << (int)n << '\n';
    // std::cout << "N: " << n << '\n';
    for (uchar i = 1; i < n; ++i)
    {
        // std::cout << "Moving " << (int)i << " from " << current_node << std::endl;
        allowed[current_node] = false;

        next = choose_next(allowed, Map, current_node, n - i);
        // std::cout << "NEXT: " << (int)next << '\n';

        go_to(next, i);
    }

    go_to(begin, n);

    // std::cout << "PATH: ";
    // for (int i = 0; i < n + 1; i++)
    // std::cout << Path[i] << ' ';
    // std::cout << '\n';
}

inline uchar Ant::give_nearest(uchar beg, AntMap &Map)
{
    uchar ret = -1;
    double fer = 1e308; // Yeah, hardcoding but why not?

    for (uchar i = 0; i < Map.n; ++i)
    {
        if (i == beg || !allowed[i])
            continue;

        if (give_feromon(Map.FeromonMap, beg, i) < fer)
        {
            ret = i;
            fer = give_feromon(Map.FeromonMap, beg, i);
        }
    }
    // std::cout << "RET: " << (int)ret << '\n';
    //  print_mas(allowed, Map.n);
    allowed[ret] = false;
    return ret;
}

uchar *Ant::give_shortest(uchar begin, AntMap &Map)
{
    uchar n = Map.n;
    uchar *ret = new uchar[n + 1];
    ret[0] = begin;

    memset(allowed, true, n);
    allowed[begin] = false;

    for (uchar i = 1; i < n; ++i)
    {
        ret[i] = give_nearest(ret[i - 1], Map);
    }
    ret[n] = begin;
    return ret;
}
void Ant::update(uchar n)
{
    delete allowed;
    delete Path;
    allowed = new bool[n];
    Path = new uchar[n + 1];
}