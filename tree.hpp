#ifndef TREE_HPP
#define TREE_HPP

// id:322522806
// email:oriyaperel18@gmail.com

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
            return node_width; // Return the width of the node if it has no children
        }

        int total_width = 0; // Initialize the total width of the subtree
        for (auto &child : node->get_children())
        {
            total_width += calculate_subtree_width(child, node_width); // Calculate the width of the subtree recursively
        }
        return std::max(total_width, node_width); // Return the maximum width of the subtree
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
        if (!font.loadFromFile("Roboto-Italic.ttf")) // Load font
        {
            throw std::runtime_error("Could not load font");
        }
        sf::Text text;
        text.setFont(font); // Set the font of the text

        // Convert node value to string with two decimal places
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << node->get_value(); // Set the precision of the value
        text.setString(ss.str());

        text.setCharacterSize(15);
        text.setFillColor(sf::Color::Red);

        // Calculate the position to center the text on the node
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(x + circle.getRadius(), y + circle.getRadius()); // Adjust position to center the text

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
        if (childCount > 0) // Draw the children
        {
            int subtree_width = calculate_subtree_width(node);
            int child_x = x - subtree_width / 2;

            for (auto &child : children) // Draw the children recursively
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

    ~Tree() {}

    void add_root(Node<T> &node)
    {
        if (&node == nullptr)
        {
            throw std::runtime_error("The root node is null");
        }
        else
        {
            root = &node;
        }
    }

    void add_sub_node(Node<T> &parent, Node<T> &child) // Add a child to a parent node
    {
        if (root == nullptr || &parent == nullptr || &child == nullptr)
        {
            throw std::runtime_error("The root node is null or the parent or child node is null");
        }
        if (parent.get_children().size() < K)
        {
            parent.add_child(&child);
        }
        else
        {
            std::__throw_invalid_argument("The parent node has the maximum number of children");
        }
    }

    void displayTree() // Display the tree
    {
        sf::RenderWindow window(sf::VideoMode(1200, 800), "Tree Display");

        // run the program as long as the window is open
        while (window.isOpen())
        {

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

    class MinHeapIterator
    {
    private:
        using NodePtr = Node<T> *;

        struct NodeComparer // Comparator for the min-heap
        {
            bool operator()(const NodePtr &a, const NodePtr &b) const // fanctor to compare the nodes
            {
                return a->get_value() > b->get_value(); // min-heap order
            }
        };

        std::priority_queue<NodePtr, std::vector<NodePtr>, NodeComparer> minHeap;

        void populateMinHeap(NodePtr node) // insert the nodes in the min-heap in the correct order by the fanctor and the recursion
        {
            if (node) // check if the node is not null
            {
                minHeap.push(node); // insert the node in the min-heap by the fanctor
                for (NodePtr child : node->get_children())
                {
                    populateMinHeap(child); // the recursion
                }
            }
        }

    public:
        MinHeapIterator(Node<T> *root)
        {
            populateMinHeap(root); // insert thr root node in the min-heap
        }

        const Node<T> *operator*() const
        {
            if (minHeap.empty())
            {
                throw std::out_of_range("Iterator is out of range");
            }
            return minHeap.top();
        }

        const T *operator->() const
        {
            return &(minHeap.top()->get_value()); // return the value of the top element
        }

        const MinHeapIterator &operator++()
        {
            minHeap.pop(); // remove the top element
            return *this;
        }

        bool operator!=(const MinHeapIterator &other) const
        {
            return !(*this == other);
        }
        bool operator==(const MinHeapIterator &other) const
        {

            if (minHeap.empty() && other.minHeap.empty()) // check if the heap is empty or not
            {
                return true;
            }
            if (minHeap.empty() || other.minHeap.empty()) // if one of the heaps is empty the iterator is not equal
            {
                return false;
            }
            return minHeap.top() == other.minHeap.top();
        }
    };

    MinHeapIterator begin_min_heap() const
    {
        return MinHeapIterator(root);
    }

    MinHeapIterator end_min_heap() const
    {
        return MinHeapIterator(nullptr);
    }

    class PreOrderIterator
    {
    private:
        std::stack<Node<T> *> stkTree; // stack to store the nodes

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
            if (stkTree.empty() && other.stkTree.empty()) // check if the stack is empty or not
            {
                return true;
            }
            if (stkTree.empty() || other.stkTree.empty()) // if one of the stacks is empty the iterator is not equal
            {
                return false;
            }
            return stkTree.top() == other.stkTree.top();
        }

        const PreOrderIterator &operator++()
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

        const T *operator->() const
        {
            return &(stkTree.top()->get_value());
        }
    };

    auto begin_pre_order() const
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

    auto end_pre_order() const
    {
        if constexpr (K != 2) // check the condition in compile time
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
                indexStack.push(0); // this is for the index of the children
                if (!node->get_children().empty())
                {
                    node = node->get_children()[0]; // Assuming the first child is the leftmost
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

        bool operator==(const PostOrderIterator &other) const
        {
            if (nodeStack.empty() && other.nodeStack.empty()) // check if the stack is empty or not
            {
                return true;
            }
            if (nodeStack.empty() || other.nodeStack.empty()) // if one of the stacks is empty the iterator is not equal
            {
                return false;
            }
            return nodeStack.top() == other.nodeStack.top();
        }

        bool operator!=(const PostOrderIterator &other) const
        {
            return !(*this == other);
        }

        const Node<T> *operator*() const
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

        const T *operator->() const
        {
            return &(nodeStack.top()->get_value());
        }

        const PostOrderIterator &operator++()
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
                { // we went to know if the index is less than the size
                    // of the children of the node this is to know if we have more children to visit
                    pushLeft(nodeStack.top()->get_children()[index]); // insert the children in the stack the right children
                }
            }

            return *this;
        }
    };

    auto begin_post_order() const
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

    auto end_post_order() const
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
        std::stack<Node<T> *> traversal;

    public:
        InOrderIterator(Node<T> *root)
        {
            if (root)
            {
                initializeStack(root); // Initialize stack with in-order traversal order
            }
        }

        bool operator==(const InOrderIterator &other) const
        {
            if (traversal.empty() && other.traversal.empty()) // check if the stack is empty or not
            {
                return true;
            }
            if (traversal.empty() || other.traversal.empty()) // if one of the stacks is empty the iterator is not equal
            {
                return false;
            }
            return traversal.top() == other.traversal.top();
        }

        bool operator!=(const InOrderIterator &other) const
        {
            return !(*this == other);
        }

        const Node<T> *operator*() const
        {
            if (traversal.empty())
            {
                throw std::out_of_range("Iterator out of range");
            }
            return traversal.top();
        }

        const T *operator->() const
        {
            return &(traversal.top()->get_value());
        }

        const InOrderIterator &operator++()
        {
            if (!traversal.empty())
            {
                Node<T> *current = traversal.top();
                traversal.pop();
                if (current->get_children().size() > 1)
                {
                    initializeStack(current->get_children()[1]); // Move to the leftmost node of the right subtree
                    // and insert all the left children of the right subtree
                }
            }
            return *this;
        }

    private:
        void initializeStack(Node<T> *node)
        { // Initialize stack with in-order traversal order
            if (!node)
            {
                return;
            }
            while (node)
            {
                traversal.push(node);
                if (node->get_children().size() > 0)
                {
                    node = node->get_children()[0]; // Move to the left child
                }
                else
                {
                    node = nullptr;
                }
            }
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
        std::queue<Node<T> *> q; // Queue to store the nodes
        Node<T> *currentNode;    // Pointer to the current node

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
        const BFSIterator &operator++()
        {
            if (!q.empty())
            {
                Node<T> *node = q.front();
                q.pop();
                std::vector<Node<T> *> children = node->get_children();
                for (Node<T> *child : children) // Add the children to the queue to visit them in the correct BFS order
                {
                    if (child != nullptr)
                        q.push(child);
                }
                currentNode = (!q.empty()) ? q.front() : nullptr;
            }
            return *this;
        }

        const T *operator->() const
        {
            return &(currentNode->get_value());
        }

        bool operator!=(const BFSIterator &other) const
        {
            return this->currentNode != other.currentNode;
        }

        bool operator==(const BFSIterator &other) const
        {
            return this->currentNode == other.currentNode;
        }

        const Node<T> *operator*() const
        {
            if (q.empty())
            {
                throw std::out_of_range("Iterator out of range");
            }
            return currentNode;
        }
    };

    BFSIterator begin_bfs_scan() const
    {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan() const
    {
        return BFSIterator(nullptr);
    }

    BFSIterator begin() const
    {
        return begin_bfs_scan();
    }

    BFSIterator end() const
    {
        return end_bfs_scan();
    }

    class DFSIterator
    {
        std::stack<Node<T> *> s; // Stack to store the nodes
        Node<T> *currentNode;    // Pointer to the current node

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
        const DFSIterator &operator++()
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

        const T *operator->() const
        {
            return &(currentNode->get_value());
        }

        bool operator==(const DFSIterator &other) const
        {
            return this->currentNode == other.currentNode;
        }

        bool operator!=(const DFSIterator &other) const
        {
            return this->currentNode != other.currentNode;
        }

        const Node<T> *operator*() const
        {
            if (s.empty())
            {
                throw std::out_of_range("Iterator out of range");
            }
            return currentNode;
        }
    };

    DFSIterator begin_dfs_scan() const
    {
        return DFSIterator(root);
    }

    DFSIterator end_dfs_scan() const
    {
        return DFSIterator(nullptr);
    }

}; // end of Tree class
#endif
