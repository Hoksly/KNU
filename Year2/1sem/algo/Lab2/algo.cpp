#include <string>

long long naiveSearch(std::string text, std::string part)
{
    // searching part in text

    long long textSize, partSize, shift;

    textSize = text.size();
    partSize = part.size();
    shift = 0;

    for (long long i = 0; i < textSize; ++i)
    {
        shift = 0;
        while (i + shift < textSize && shift < partSize && text[i + shift] == part[shift])
        {
            shift++;
        }
        if (shift == textSize)
            return i;
    }
    return -1;
}

long long horspoolSearch(std::string text, std::string part)
{
}

long long rabinCarpSearch(std::string text, std::string part)
{
}