#include "WordTree.hpp"
#include "rlutil.h"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>

std::shared_ptr<WordTree> readDictionary(std::string filename)
{
    auto wordTree = std::make_shared<WordTree>();
    std::ifstream inFile = std::ifstream(filename, std::ios::in);

    while (!inFile.eof())
    {
        std::string word;
        std::getline(inFile, word);
        // Need to consume the carriage return character for some systems, if it exists
        if (!word.empty() && word[word.size() - 1] == '\r')
        {
            word.erase(word.end() - 1);
        }
        // Keep only if everything is an alphabetic character -- Have to send isalpha an unsigned char or
        // it will throw exception on negative values; e.g., characters with accent marks.
        if (std::all_of(word.begin(), word.end(), [](unsigned char c)
                        { return std::isalpha(c); }))
        {
            std::transform(word.begin(), word.end(), word.begin(), [](char c)
                           { return static_cast<char>(std::tolower(c)); });
            wordTree->add(word);
        }
    }

    return wordTree;
}

int main()
{
    std::shared_ptr<WordTree> tree = readDictionary("dictionary.txt");

    bool stop = false;
    std::string input;
    while (!stop)
    {
        int key = rlutil::getkey();
        rlutil::cls();
        switch (key)
        {
            case rlutil::KEY_ESCAPE:
                stop = true;
                break;
            case rlutil::KEY_BACKSPACE:
                if (input.size() > 0)
                {
                    input.erase(input.end() - 1);
                }
                break;
            default:
                input.append(std::string(1, char(key)));
        }

        std::vector<std::string> predictor{};
        std::istringstream iss(input);
        std::copy(std::istream_iterator<std::string>(iss),
                  std::istream_iterator<std::string>(),
                  std::back_inserter(predictor));

        std::vector<std::string> prediction = tree->predict((predictor.size() > 0) ? predictor[predictor.size() - 1] : "", static_cast<std::uint8_t>(rlutil::trows() - 5));
        std::cout << "\n\n--- Prediction ---\n";

        for (std::string word : prediction)
        {
            std::cout << word << "\n";
        }
        rlutil::locate(0, 0);
        std::cout << input;
    }
    return 0;
}
