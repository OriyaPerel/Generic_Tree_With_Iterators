#include "node.hpp"
#include <stack>
#include <queue>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <string>
#include <iomanip>
#include <cmath>

template <typename T, int K = 2>
class Tree
{
private:
    Node<T> *root;
    // Helper function to calculate the width of the subtree rooted at a given node
    int calculate_subtree_width(Node<T> *node, int node_width = 120)
    {
        if (node == nullptr || node->get_children().empty())
        {
            return node_width;
        }

        int total_width = 0;
        for (auto &child : node->get_children())
        {
            total_width += calculate_subtree_width(child, node_width);
        }
        return std::max(total_width, node_width);
    }

    // Helper function to recursively draw the tree
    void draw_The_Tree(sf::RenderWindow &window, Node<T> *node, int x, int y, int px, int py, int level = 0)
    {
        if (node == nullptr)
        {
            return;
        }

        sf::CircleShape circle(30);
        circle.setFillColor(sf::Color::White);
        circle.setPosition(x, y); // Adjust position to center the circle

        window.draw(circle);

        sf::Font font;
        if (!font.loadFromFile("Roboto-Italic.ttf"))
        {
            throw std::runtime_error("Could not load font");
        }
        sf::Text text;
        text.setFont(font);

        // Convert node value to string with two decimal places
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << node->get_value();
        text.setString(ss.str());

        text.setCharacterSize(15);
        text.setFillColor(sf::Color::Red);

        // Calculate the position to center the text on the node
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(x + circle.getRadius(), y + circle.getRadius());

        window.draw(text);

        if (px != -1 && py != -1) // Draw line if parent coordinates are valid
        {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x + circle.getRadius(), y + circle.getRadius())),
                sf::Vertex(sf::Vector2f(px + circle.getRadius(), py + circle.getRadius()))};
            window.draw(line, 2, sf::Lines);
        }

        const std::vector<Node<T> *> children = node->get_children();
        int childCount = children.size();
        if (childCount > 0)
        {
            int subtree_width = calculate_subtree_width(node);
            int child_x = x - subtree_width / 2;

            for (auto &child : children)
            {
                int child_subtree_width = calculate_subtree_width(child);
                int new_x = child_x + child_subtree_width / 2;
                int new_y = y + 150;
                draw_The_Tree(window, child, new_x, new_y, x, y, level + 1);
                child_x += child_subtree_width + 20; // Add a margin between subtrees
            }
        }
    }

public:
    Tree() : root(nullptr) {}

     ~Tree(){}
    // {
    //     if (root != nullptr)
    //     {
    //         delete root; // Clean up existing tree
    //     }
    // }

    void add_root(Node<T> &node)
    {
        root = &node;
    }

    void displayTree()
    {
        sf::RenderWindow window(sf::VideoMode(1200, 800), "Tree Display");

        // run the program as long as the window is open
        while (window.isOpen())
        {
            // check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            // clear the window with black color
            window.clear(sf::Color::Black);

            // draw the tree starting from the root
            if (root != nullptr)
            {
                draw_The_Tree(window, root, 600, 50, -1, -1, 0);
            }

            // end the current frame
            window.display();
        }
    }

    void add_sub_node(Node<T> &parent, Node<T> &child)
    {
        if (parent.get_children().size() < K)
        {
            parent.add_child(&child);
        }
        else
        {
            std::__throw_invalid_argument("The parent node has reached the maximum number of children.");
        }
    }

    class MinHeapIterator
    {
    private:
        struct CompareNode
        {
            bool operator()(const Node<T> *lhs, const Node<T> *rhs) const
            {
                return lhs->get_value() > rhs->get_value();
            }
        };

        std::priority_queue<Node<T> *, std::vector<Node<T> *>, CompareNode> nodes;

    public:
        MinHeapIterator(Node<T> *root)
        {
            if (root)
                nodes.push(root);
        }

        const Node<T> *operator*() const
        {
            if (!nodes.empty())
            {
                return nodes.top();
            }
            throw std::out_of_range("Iterator is out of range");
        }
        MinHeapIterator &operator++()
        {
            if (!nodes.empty())
            {
                Node<T> *current = nodes.top();
                nodes.pop();
                for (Node<T> *child : current->get_children()) // add the children to the priority queue
                {
                    nodes.push(child);
                }
            }
            return *this;
        }

        bool operator!=(const MinHeapIterator &other) const
        {
            // Since we can't directly compare priority queues, we compare their emptiness
            return !nodes.empty() || !other.nodes.empty();
        }

        bool operator==(const MinHeapIterator &other) const
        {
            return nodes.empty() && other.nodes.empty();
        }
    };

    MinHeapIterator begin_min_heap()
    {
        return MinHeapIterator(root);
    }

    MinHeapIterator end_min_heap()
    {
        return MinHeapIterator(nullptr);
    }

    class PreOrderIterator
    {
    private:
        std::stack<Node<T> *> stkTree;

    public:
        PreOrderIterator(Node<T> *node)
        {
            if (node)
            {
                stkTree.push(node);
            }
        }

        bool operator!=(const PreOrderIterator &other) const
        {
            return !(*this == other);
        }

        bool operator==(const PreOrderIterator &other) const
        {
            return stkTree == other.stkTree;
        }

        PreOrderIterator &operator++()
        {
          
            if (stkTree.empty())
            {
                return *this;
            }

            Node<T> *current = stkTree.top();
            stkTree.pop(); // remove the top element
            const std::vector<Node<T> *> children = current->get_children();
            for (auto it = children.rbegin(); it != children.rend(); ++it)
            { // add the children in reverse order to the stack to get the
                // correct order that it wiil be the left child first then the right child
                stkTree.push((*it));
            }

            return *this; // return the current iterator
        }

        const Node<T> *operator*() const
        {
          
            if (stkTree.empty())
            {
                throw std::out_of_range("Iterator out of range");
            }
            else
            {
                return stkTree.top();
            }
        }
    };

    auto begin_pre_order()
    {
        if constexpr (K != 2)
        {
            return DFSIterator(root);
        }
        else
        {
            return PreOrderIterator(root);
        }
    }

    auto end_pre_order()
    {
        if constexpr (K != 2)
        {
            return DFSIterator(nullptr);
        }
        else
        {
            return PreOrderIterator(nullptr);
        }
    }

    class PostOrderIterator
    {
    private:
        Node<T> *root;
        std::stack<Node<T> *> nodeStack;
        std::stack<size_t> indexStack;

        void pushLeft(Node<T> *node)
        {
            while (node)
            {
                nodeStack.push(node);
                indexStack.push(0);
                if (!node->get_children().empty())
                {
                    node = node->get_children()[0];
                }
                else
                {
                    node = nullptr;
                }
            }
        }

    public:
        PostOrderIterator(Node<T> *root) : root(root)
        {
            if (root)
            {
                pushLeft(root);
            }
        }

        bool operator!=(const PostOrderIterator &other) const
        {
            return !(*this == other);
        }

        bool operator==(const PostOrderIterator &other) const
        {
            if (nodeStack.empty() && other.nodeStack.empty())
            {
                return true;
            }
            if (nodeStack.empty() || other.nodeStack.empty())
            {
                return false;
            }
            return nodeStack.top() == other.nodeStack.top();
        }

        Node<T> *operator*() const
        {
            if (nodeStack.empty())
            {
                throw std::out_of_range("Iterator out of range");
            }
            else
            {
                return nodeStack.top();
            }
        }

        PostOrderIterator &operator++()
        {
            if (nodeStack.empty())
            {
                return *this;
            }

            Node<T> *node = nodeStack.top();
            nodeStack.pop();
            indexStack.pop();

            if (!nodeStack.empty())
            {
                size_t &index = indexStack.top();
                if (++index < nodeStack.top()->get_children().size())
                {
                    pushLeft(nodeStack.top()->get_children()[index]);
                }
            }

            return *this;
        }
    };

    auto begin_post_order()
    {
        if constexpr (K != 2)
        {
            return DFSIterator(root);
        }
        else
        {
            return PostOrderIterator(root);
        }
    }

    auto end_post_order()
    {
        if constexpr (K != 2)
        {
            return DFSIterator(nullptr);
        }
        else
        {
            return PostOrderIterator(nullptr);
        }
    }

    class InOrderIterator
    {
    private:
        std::stack<Node<T> *> stk;
        Node<T> *currentNode;

        void pushLeft(Node<T> *node)
        {
            // Push all left children onto the stack
            while (node != nullptr)
            {
                stk.push(node);
                if (!node->get_children().empty())
                {
                    node = node->get_children().front(); // Assuming the first child is the "leftmost"
                }
                else
                {
                    break;
                }
            }
        }

    public:
        InOrderIterator(Node<T> *root) : currentNode(root)
        {
            pushLeft(root);
        }

        bool operator!=(const InOrderIterator &other) const
        {
            return !stk.empty();
        }

        bool operator==(const InOrderIterator &other) const
        {
            return stk.empty();
        }

        Node<T> *operator*() const
        {
            return stk.top();
        }

        InOrderIterator &operator++()
        {
            if (!stk.empty())
            {
                Node<T> *top = stk.top();
                stk.pop();
                const auto &children = top->get_children();
                if (children.size() > 1)
                {
                    pushLeft(children[1]);
                }
            }
            return *this;
        }
    };

    auto begin_in_order() const
    {
        if constexpr (K != 2)
        {
            return DFSIterator(root);
        }
        else
        {
            return InOrderIterator(root);
        }
    }

    auto end_in_order() const
    {
        if constexpr (K != 2)
        {
            return DFSIterator(nullptr);
        }
        else
        {
            return InOrderIterator(nullptr);
        }
    }
    class BFSIterator
    {
        std::queue<Node<T> *> q;
        Node<T> *currentNode;

    public:
        BFSIterator(Node<T> *root) : currentNode(nullptr)
        {
            if (root != nullptr)
            {
                q.push(root);
                currentNode = q.front();
            }
        }
        // Increment operator moves to the next node in BFS order
        BFSIterator &operator++()
        {
            if (!q.empty())
            {
                Node<T> *node = q.front();
                q.pop();
                std::vector<Node<T> *> children = node->get_children();
                for (Node<T> *child : children)
                {
                    if (child != nullptr)
                        q.push(child);
                }
                currentNode = (!q.empty()) ? q.front() : nullptr;
            }
            return *this;
        }
        bool operator!=(const BFSIterator &other) const
        {
            return this->currentNode != other.currentNode;
        }

        bool operator==(const BFSIterator &other) const
        {
            return this->currentNode == other.currentNode;
        }

        Node<T> *operator*() const
        {
            return currentNode;
        }
    };

    BFSIterator begin_bfs_scan()
    {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan()
    {
        return BFSIterator(nullptr);
    }

    BFSIterator begin()
    {
        return begin_bfs_scan();
    }

    BFSIterator end()
    {
        return end_bfs_scan();
    }

    class DFSIterator
    {
        std::stack<Node<T> *> s;
        Node<T> *currentNode;

    public:
        DFSIterator(Node<T> *root) : currentNode(nullptr)
        {
            if (root != nullptr)
            {
                s.push(root);
                currentNode = s.top();
            }
        }
        // Increment operator moves to the next node in DFS order
        DFSIterator &operator++()
        {
            if (!s.empty())
            {
                Node<T> *node = s.top();
                s.pop();
                std::vector<Node<T> *> children = node->get_children();
                // Push children in reverse order to visit them in the correct DFS order
                for (auto it = children.rbegin(); it != children.rend(); ++it)
                {
                    if (*it != nullptr)
                        s.push(*it);
                }
                currentNode = (!s.empty()) ? s.top() : nullptr;
            }
            return *this;
        }

        bool operator==(const DFSIterator &other) const
        {
            return this->currentNode == other.currentNode;
        }

        bool operator!=(const DFSIterator &other) const
        {
            return this->currentNode != other.currentNode;
        }

        Node<T> *operator*() const
        {
            return currentNode;
        }
    };

    DFSIterator begin_dfs_scan()
    {
        return DFSIterator(root);
    }

    DFSIterator end_dfs_scan()
    {
        return DFSIterator(nullptr);
    }

}; // end of Tree class
