#pragma once
#include <string>
#define ll long long
#include <vector>
#include <unordered_map>

#ifndef SEARCH_ALGORITHMS_HPP
#define SEARCH_ALGORITHMS_HPP
long long naiveSearch(const std::string &text, const std::string &part);

long long horspoolSearch(const std::string &text, const std::string &part);

long long rabinCarpSearch(const std::string &text, const std::string &part,
                          int charsInAplhabet = 256, ll base = 71,
                          ll primeOne = 87178291199, bool checkCollisions = false);
#endif