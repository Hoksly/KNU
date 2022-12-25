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

void testRandom(ll textBeg, ll textEnd, ll textStep,
                ll partBeg, ll partEnd, ll partStep);
void testReal(std::string filename, std::string functionName,
              ll *search(const std::string, const std::string),
              ll partBeg = 10, ll partEnd = 1011, ll partStep = 1000);

const std::string CHARS_FOR_TEST = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

#endif