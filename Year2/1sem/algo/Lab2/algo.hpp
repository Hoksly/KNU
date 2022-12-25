#pragma once
#include <string>
#define ll long long
#include <vector>
#include <unordered_map>

#ifndef SEARCH_ALGORITHMS_HPP
#define SEARCH_ALGORITHMS_HPP
long long naiveSearch(std::string text, std::string part);

long long horspoolSearch(std::string text, std::string part);

long long rabinCarpSearch(std::string text, std::string part,
                          int charsInAplhabet = 256, ll base = 717,
                          ll primeOne = 87178291199, bool checkCollisions = false);
#endif