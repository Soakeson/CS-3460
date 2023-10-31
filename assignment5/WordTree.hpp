#pragma once
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <valarray>
#include <vector>

/*
 * WordTree is a class that constructs an m-ary tree that contains TreeNodes that corespond to letters of the
 * alphabet.
 * @m_root: TreeNode | the starting node, does not correspond to any letter of the alphabet.
 * @m_count: size_t | keeps track of the amount of words in the WordTree.
 */
class WordTree
{
  public:
    WordTree();
    /*
     * @word: std::string | the word that will be added to the WordTree *only alpha character.
     * @return: void
     */
    void add(std::string word);

    /*
     * @word: std::string | the word that will be searched for *only alpha characters.
     * @return: bool | true if found, false if not.
     */
    bool find(std::string word);

    /*
     * @partial: std::string | a partial word that will be the base for the predicted words.
     * @howMany: std::uint8_t | the amount of predicted words that will be returned.
     * @return: std::vector<std::string> | returns a vector with the amount of specified predicted words.
     */
    std::vector<std::string> predict(std::string partial, std::uint8_t howMany);

    /*
     * @return: size_t | returns the amount of words saved in the WordTree.
     */
    std::size_t size() { return m_count; };

  private:
    /*
     * TreeNode is a private class on WordTree that stores a list of children pointers to other TreeNodes
     * it also stores whether it itself is the end of the word.
     * @endOfWord: bool | true if that node is the end of the word, false if not.
     * @children: std::array<std::shared_ptr<TreeNode>, 26> | each of the 26 slots correspond to a letter of
     * the alphabet to translate add 97 to get in the range of lowercase letters.
     */
    class TreeNode
    {
      public:
        TreeNode(bool endOfWord) :
            endOfWord(endOfWord),
            children(std::array<std::shared_ptr<TreeNode>, 26>{})
        {
        }

        bool endOfWord;
        std::array<std::shared_ptr<TreeNode>, 26> children;
    };

    std::shared_ptr<TreeNode> m_root;
    std::size_t m_count;
};
