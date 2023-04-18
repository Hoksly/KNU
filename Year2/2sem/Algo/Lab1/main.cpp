#include "ideal-hashing.h"
#include <set>
int main()
{
    std::set<std::string> a = {"123123", "221", "123"};
    idealHashSet<std::string, std::set<std::string>, LazyPrimesGenerator<size_t>> st(a, LazyPrimesGenerator<size_t>());
}