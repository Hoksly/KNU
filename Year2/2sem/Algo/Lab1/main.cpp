#include "ideal-hashing.h"
#include <set>
int main()
{
    std::set<int> a = {1, 2, 4};
    idealHashSet<int, std::set<int>, LazyPrimesGenerator<size_t>> st(a, LazyPrimesGenerator<size_t>());
}