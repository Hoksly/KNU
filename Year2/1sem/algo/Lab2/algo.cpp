#include "algo.hpp"
#include <iostream>

long long naiveSearch(const std::string &text, const std::string &part)
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
        if (shift == partSize)
            return i;
    }
    return -1;
}

std::unordered_map<char, int> findShiftTable(const std::string &prototype)
{
    std::unordered_map<char, int>
        shiftTable; // A HashMap for shift table that has characters for keys and integers for values

    for (int i = 0; i < prototype.size();
         i++)
    { // Checking all characters of prototype string
        if (shiftTable.find(prototype[i]) ==
            shiftTable.end())
        { // If character does not exist in HashMap
            if (i != prototype.size() - 1)
            {
                shiftTable.insert(std::make_pair(
                    prototype[i], prototype.size() - i -
                                      1)); // Insert the character as key and the size of prototype string - index of character - 1 as value
            }
            else
            {
                shiftTable.insert(std::make_pair(
                    prototype[i],
                    prototype.size())); // Insert the character as key and the size of prototype string as value
            }
        }
        else
        {
            if (i != prototype.size() - 1)
            {
                shiftTable[prototype[i]] = prototype.size() - i - 1;
            }
        }
    }
    return shiftTable;
}

long long horspoolSearch(const std::string &text, const std::string &part)
{
    std::unordered_map<char, int> shiftTable = findShiftTable(part); // Initialise shift table calling findShiftTable function

    ll i = part.size() - 1; // Index that we shift in text to find the substring

    while (i < text.size())
    {
        ll j = i, k = 0;
        bool flag = true;

        for (ll z = part.size() - 1; z >= 0 && flag; z--)
        { // Checking if all characters of substring are equal with all characters of string
            if (text[j] == part[z])
            {
                k++;
                j--;
            }
            else
            {
                flag = false; // If two characters are not equal set flag to false and break from loop
            }
        }

        if (k == part.size())
        { // If all characters match then return true
            return i - part.size() + 1;
        }

        else
        {
            if (shiftTable.find(text[i]) != shiftTable.end())
            {
                i += shiftTable[text[i]]; // If shift table contains the character then shift index as many steps as value
            }
            else
            {
                i += part.size(); // If character does not exist in shift table then shift index as many steps as size of prototype string
            }
        }
    }
    return -1;
}

long long rabinCarpSearch(const std::string &text, const std::string &part, int charsInAplhabet, ll base, ll primeOne, bool checkCollisions)
{

    ll leadingPow = 1;
    ll M = part.size();
    ll N = text.size();
    ll patternHash = 0; // hash value for pattern
    ll textHash = 0;    // hash value for txt

    for (int i = 0; i < M - 1; ++i)
    {
        leadingPow *= base;
        leadingPow %= primeOne;
    }

    // Calculate the hash value of pattern and first
    // window of text
    for (ll i = 0; i < M; i++)
    {
        patternHash = (base * patternHash + part[i]) % primeOne;
        textHash = (base * textHash + text[i]) % primeOne;
    }

    // Slide the pattern over text one by one
    for (ll i = M; i < N; i++)
    {

        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters one by one
        if (patternHash == textHash)
        {
            bool found = true;
            /* Check for characters one by one */
            if (checkCollisions)
            {
                for (ll j = 0; j < M; j++)
                {
                    if (text[i + j] != part[j])
                    {
                        found = false;
                        break;
                    }
                }
                if (found)
                    return i - M;
            }

            if (!checkCollisions)
                return i - M;
        }

        // Calculate hash value for next window of text:
        // Remove leading digit, add trailing digit
        if (i < N - M)
        {

            textHash = (base * (textHash - text[i - M] * leadingPow) % primeOne + text[i]) % primeOne;

            // We might get negative value of t, converting
            // it to positive
            if (textHash < 0)
                textHash = (textHash + primeOne);
        }
    }

    return -1;
}