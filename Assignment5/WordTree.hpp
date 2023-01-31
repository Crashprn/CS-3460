#pragma once

#include <string>
#include <vector>
#include <memory>
#include <array>

class TreeNode
{
  public:
    TreeNode();
    bool m_endOfWord;
    bool isEndofWord() { return m_endOfWord; };
    bool isChildNull(std::uint8_t index);
    void addChildAtIndex(std::uint8_t index);
    auto getChildSize() { return m_children.size(); };
    std::shared_ptr<TreeNode> getChildAtIndex(std::uint8_t index);

  private:
    std::array<std::shared_ptr<TreeNode>, 26> m_children;
};

class WordTree
{

  public:
    WordTree();
    void add(std::string word);
    bool find(std::string word);
    std::vector<std::string> predict(std::string partial, std::uint8_t howMany);
    std::size_t size() { return m_size; };

  private:
    std::shared_ptr<TreeNode> m_root;
    std::size_t m_size;
};

