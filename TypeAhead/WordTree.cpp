#include "WordTree.hpp"

#include <array>
#include <cctype>
#include <cstdint>
#include <format>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

const std::uint8_t ALPHA_OFFSET = 97;

WordTree::WordTree()
{
    m_root = std::make_shared<TreeNode>(false);
    m_count = 0;
};

void WordTree::add(std::string word)
{
    std::shared_ptr<TreeNode> node = m_root;
    for (unsigned long i = 0; i < word.size(); i++)
    {
        if (std::isalpha(word[i]) && !std::isspace(word[i]))
        {
            int let = int(std::tolower(word[i]));
            let -= ALPHA_OFFSET;
            // if the letter is not in already in place create it and increment the size
            if (node->children[let] == 0)
            {
                node->children[let] = std::make_shared<TreeNode>((i == word.size() - 1) ? true : false);
                node = node->children[let];
                if (i == word.size() - 1)
                {
                    m_count++;
                }
            }
            else
            {
                node = node->children[let];
            }
        }
        else
        {
            break;
        }
    }
}

bool WordTree::find(std::string word)
{
    std::shared_ptr<TreeNode> node = m_root;
    for (unsigned long i = 0; i < word.size(); i++)
    {
        int let = int(std::tolower(word[i]));
        let -= ALPHA_OFFSET;
        // if letter is found move down the tree
        if (std::isalpha(word[i]) && !std::isspace(word[i]) && node->children[let] != 0)
        {
            // if letter is end of the word and we are also at the end of the searched word return true
            if (node->children[let]->endOfWord && i == word.size() - 1)
            {
                return true;
            };
            node = node->children[let];
        }
        else
        {
            break;
        }
    }
    return false;
};

std::vector<std::string> WordTree::predict(std::string partial, std::uint8_t howMany)
{
    std::queue<std::tuple<std::shared_ptr<TreeNode>, std::string>> queue;
    std::shared_ptr<TreeNode> start = m_root;
    std::vector<std::string> prediction{};

    // finds the starting node from partial string
    for (unsigned long i = 0; i < partial.size(); i++)
    {
        int let = int(std::tolower(partial[i]));
        let -= ALPHA_OFFSET;
        if (!partial.empty() && std::isalpha(partial[i]) && !std::isspace(partial[i]) && start->children[let] != 0)
        {
            start = start->children[let];
        }
        else
        {
            start = std::shared_ptr<TreeNode>{};
        }
    }
    
    // perform a breadth first search to find the shortest words from the starting position of the partial word
    queue.push({ start, partial });
    while (!queue.empty() && prediction.size() < howMany)
    {
        std::tuple<std::shared_ptr<TreeNode>, std::string> curr = queue.front();
        queue.pop();
        for (unsigned long i = 0; i < std::get<0>(curr)->children.size(); i++)
        {
            if (std::get<0>(curr)->children[i])
            {
                std::string temp = std::get<1>(curr);
                temp.push_back(char(i + ALPHA_OFFSET));
                queue.push({ std::get<0>(curr)->children[i], temp });

                if (std::get<0>(curr)->children[i]->endOfWord)
                {
                    prediction.push_back(temp);
                }
            }
        }
    }
    return prediction;
};
