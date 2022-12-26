#pragma once
#include "algo.hpp"
#include "string"
#include <vector>
#include <chrono>

#include <iostream>
#include <fstream>
#include <sstream>

#define ll long long

#ifndef TEST_ALGORITHMS_HPP
#define TEST_ALGORITHMS_HPP

void testRandom(std::string functionName, ll (*search)(const std::string &, const std::string &),
                ll textBeg = 1000000, ll textEnd = 1001000001, ll textStep = 1000000000,
                ll partBeg = 10, ll partEnd = 100011, ll partStep = 100000);

void testReal(std::string filename, std::string functionName,
              ll (*search)(const std::string &, const std::string &),
              ll partBeg = 10, ll partEnd = 1000011, ll partStep = 1000000);

const std::string CHARS_FOR_TEST = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

#endif