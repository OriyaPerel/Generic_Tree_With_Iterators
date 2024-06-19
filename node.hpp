#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>

template <typename T>
class Node
{

private:
    T value;
    std::vector<Node<T> *> children;

public:
    Node(T value) : value(value) {}
    ~Node() {}
    // ~Node(){ for (auto child : children) delete child; }
    T get_value() const { return value; }
    void add_child(Node<T> *child) { children.push_back(child); }
    std::vector<Node<T> *> get_children() const { return children; }
};

#endif
