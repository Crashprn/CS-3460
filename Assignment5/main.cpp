#include "WordTree.hpp"
#include "rlutil.h"

#include <algorithm>
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
        if (std::all_of(word.begin(), word.end(), [](unsigned char c) { return std::isalpha(c); }))
        {
            std::transform(word.begin(), word.end(), word.begin(), [](char c){ return static_cast<char>(std::tolower(c)); });
            wordTree->add(word);
        }
    }

    return wordTree;
}

void setScreen()
{
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "--- prediction --- " << std::endl;
}

void clearWords(std::vector<std::string> words, int start)
{
    auto row = start;

    for (std::string word : words)
    {
        for (decltype(word.length()) column = 1; column <= word.length(); column++)
        {
            rlutil::locate(static_cast<int>(column), row);
            rlutil::setChar(' ');
        }
        row += 1;
    }
}
void writeWords(std::vector<std::string> words, int start)
{
    auto row = start;

    for (std::string word : words)
    {
        for (decltype(word.length()) column = 1; column <= word.length(); column++)
        {
            rlutil::locate(static_cast<int>(column), row);
            rlutil::setChar(word[column - 1]);
        }
        row += 1;
    }
}

std::string getLastWord(std::string word)
{
    std::vector<std::string> tokens;
    std::istringstream iss(word);
    std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), back_inserter(tokens));

    std::string lastWord;
    if (tokens.size() > 0)
    {
        return tokens[tokens.size() - 1];
    }
    else
    {
        return "";
    }
}

int main()
{
    auto wordTree = readDictionary("dictionary.txt");
    rlutil::cls();
    auto predictNumber = static_cast<std::uint8_t>(rlutil::trows() - 6);
    setScreen();
    rlutil::locate(1, 1);

    std::string userInput = "";
    std::vector<std::string> words;
    while (true)
    {
        char letter = static_cast<char>(rlutil::getkey());

        if (letter == rlutil::KEY_BACKSPACE)
        {
            if (userInput.length() > 0)
            {
                rlutil::locate(static_cast<int>(userInput.length()), 1);
                rlutil::setChar(' ');
                userInput.pop_back();
            }
        }
        else if (!std::isalpha(letter) && letter != rlutil::KEY_SPACE)
        {
            if (letter == rlutil::KEY_ESCAPE)
            {
                break;
            }
            else
            {
                continue;
            }
        }
        else
        {
            userInput += static_cast<char>(std::tolower(letter));
            rlutil::locate(static_cast<int>(userInput.length()), 1);
            rlutil::setChar(letter);
        }

        auto lastWord = getLastWord(userInput);
        clearWords(words, 4);
        words = wordTree->predict(lastWord, predictNumber);
        writeWords(words, 4);

        rlutil::locate(static_cast<int>(userInput.length()) + 1, 1);
    }
    return 1;
}