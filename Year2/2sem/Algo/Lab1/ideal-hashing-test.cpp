#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "ideal-hashing.h"
#include "utils.h"
#include <set>

using namespace std;

TEST_CASE("Insertion tests")
{
    getRandomSizeT gen;
    std::set<std::string> stringSet;
    size_t totalString = gen.getNumberInRange(10, 1000);
    getRandomString stingGen;

    for (size_t i = 0; i < totalString; ++i)
    {
        stringSet.insert(stingGen.getStringInRange(10, 1000));
    }

    idealHashSet<std::string, std::set<std::string>, LazyPrimesGenerator<size_t>>
        st(stringSet, LazyPrimesGenerator<size_t>());

    for (string s : stringSet)
    {
        st.insert(s);
    }
    for (string s : stringSet)
    {
        CHECK(st.contains(s));
    }
}

TEST_CASE("Erasing")
{
    getRandomSizeT gen;
    std::set<std::string> stringSet;
    size_t totalString = gen.getNumberInRange(10, 1000);
    getRandomString stingGen;

    for (size_t i = 0; i < totalString; ++i)
    {
        stringSet.insert(stingGen.getStringInRange(10, 1000));
    }

    idealHashSet<std::string, std::set<std::string>, LazyPrimesGenerator<size_t>>
        st(stringSet, LazyPrimesGenerator<size_t>());

    for (string s : stringSet)
    {
        st.insert(s);
    }

    for (string s : stringSet)
    {
        st.erase(s);
    }

    for (string s : stringSet)
    {
        CHECK(!st.contains(s));
    }
}

TEST_CASE("Pushing wrong element")
{
    std::set<std::string> a = {"123123", "221", "123", "1231", "__x", "ddaq"};
    idealHashSet<std::string, std::set<std::string>, LazyPrimesGenerator<size_t>> st(a, LazyPrimesGenerator<size_t>());

    CHECK_THROWS_AS(st.insert("444"), std::invalid_argument);
}
