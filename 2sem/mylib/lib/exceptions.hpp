#include<exception>

struct IndexOutOfRangeException : public std::exception
{};
struct NoSuchElementException : public std::exception
{};