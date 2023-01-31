#include "WordTree.hpp"

// TreeNode Method Implementations

TreeNode::TreeNode()
{
    m_endOfWord = false;
}

bool TreeNode::isChildNull(std::uint8_t index)
{
    return m_children[index] == nullptr;
}

void TreeNode::addChildAtIndex(std::uint8_t index)
{
    m_children[index] = std::make_shared<TreeNode>(TreeNode());
}

std::shared_ptr<TreeNode> TreeNode::getChildAtIndex(std::uint8_t index)
{
    return m_children[index];
}

// WordTree Method Implementations

WordTree::WordTree()
{
    m_root = std::make_shared<TreeNode>(TreeNode());
    m_size = 0;
}

bool WordTree::find(std::string word)
{
    std::shared_ptr<TreeNode> node = m_root;

    for (char letter : word)
    {
        if (not node->isChildNull(letter - 'a'))
        {
            node = node->getChildAtIndex(letter - 'a');
        }
        else
        {
            return false;
        }
    }
    return node->isEndofWord();
}

void WordTree::add(std::string word)
{
    if (find(word) || word.length() == 0)
    {
        return;
    }
    else
    {
        std::shared_ptr<TreeNode> node = m_root;
        for (char letter : word)
        {
            if (not node->isChildNull(letter - 'a'))
            {
                node = node->getChildAtIndex(letter - 'a');
            }
            else
            {
                node->addChildAtIndex(letter - 'a');
                node = node->getChildAtIndex(letter - 'a');
            }
        }
        node->m_endOfWord = true;
        m_size += 1;
    }
}

std::vector<std::string> WordTree::predict(std::string partial, std::uint8_t howMany)
{
    std::vector<std::string> Words;
    if (partial.length() == 0)
    {
        return Words;
    }
    std::shared_ptr<TreeNode> node = m_root;
    for (char letter : partial)
    {
        if (not node->isChildNull(letter - 'a'))
        {
            node = node->getChildAtIndex(letter - 'a');
        }
        else
        {
            return Words;
        }
    }

    std::vector<std::shared_ptr<TreeNode>> nodeQueue;
    std::vector<std::string> wordQueue;

    nodeQueue.push_back(node);
    wordQueue.push_back(partial);

    while (Words.size() < howMany && not nodeQueue.empty())
    {
        std::shared_ptr<TreeNode> searchNode = nodeQueue[0];
        std::string searchWord = wordQueue[0];
        nodeQueue.erase(nodeQueue.begin());
        wordQueue.erase(wordQueue.begin());

        for (decltype(searchNode->getChildSize()) i = 0; i < searchNode->getChildSize(); i++)
        {
            if (not searchNode->isChildNull(static_cast<std::uint8_t>(i)))
            {
                char letter = static_cast<char>('a' + i);
                std::shared_ptr<TreeNode> newNode = searchNode->getChildAtIndex(static_cast<std::uint8_t>(i));
                nodeQueue.push_back(newNode);
                wordQueue.push_back(searchWord + letter);

                if (newNode->isEndofWord())
                {
                    Words.push_back(searchWord + letter);
                }
            }
        }
    }

    return Words;
}