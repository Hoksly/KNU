#include "test.hpp"

std::string generateRandomText(ll textLen)
{
    srand(time(NULL));
    int mx = CHARS_FOR_TEST.size();
    std::string randoms = "";
    randoms.reserve(textLen);
    for (ll i = 0; i < textLen; ++i)
    {
        randoms += CHARS_FOR_TEST[rand() % mx];
    }

    return randoms;
}

void testRandom(std::string functionName, ll *search(const std::string, const std::string), ll textBeg, ll textEnd, ll textStep,
                ll partBeg, ll partEnd, ll partStep)
{
    std::string text, part;

    for (ll textLen = textBeg; textLen < textEnd; textLen += textStep)
    {
        text = generateRandomText(textLen);
        for (ll partLen = partBeg; partLen < partEnd; partLen += partStep)
        {
            part = generateRandomText(partLen);
            auto begin = std::chrono::high_resolution_clock::now();
            search(text, part);
            auto end = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
            double execTime = duration.count();
            execTime /= 10e6;

            std::cout << functionName << "\n  text size: " << textLen << "\n  sample len: " << partLen << "\n  search time: " << execTime << '\n';
            std::cout << std::endl;
        }
    }
}

void testReal(std::string filename, std::string functionName, ll *search(const std::string, const std::string), ll partBeg, ll partEnd, ll partStep)
{
    std::ifstream file;
    std::stringstream buffer;
    file.open(filename);
    buffer << file.rdbuf();
    std::string text = buffer.str(), part;

    for (ll partLen = partBeg; partLen < partEnd; partLen += partStep)
    {
        part = generateRandomText(partLen);
        part = generateRandomText(partLen);
        auto begin = std::chrono::high_resolution_clock::now();
        search(text, part);
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        double execTime = duration.count();
        execTime /= 10e6;

        std::cout << functionName << "\n  text file name: " << filename << "\n text size: " << text.size()
                  << "\n  sample len: " << partLen << "\n  search time: " << execTime << '\n';
        std::cout << std::endl;
    }
}