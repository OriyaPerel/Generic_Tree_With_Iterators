// id:322522806
// email:oriyaperel18@gmail.com


#include "doctest.h"
#include "tree.hpp"
#include "node.hpp"
#include "Complex.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <typeinfo>

using namespace std;


TEST_CASE ("creat node is correct")
{
    Node<int> node(1);
    CHECK(node.get_value() == 1);

    Node<string> node2("hello");
    CHECK(node2.get_value() == "hello");

    Node<Complex> node3(Complex(1, 1));
    CHECK(node3.get_value() == Complex(1, 1));
}

TEST_CASE("Add sub node functionality")
{
    Tree<int> tree;
    Tree<int> tree2;
    Node<int> *nullNode = nullptr;
    Node<int> validNode(1);
    tree.add_root(validNode);

    CHECK_THROWS_WITH(tree2.add_root(*nullNode), "The root node is null");
    CHECK_THROWS_WITH(tree.add_sub_node(*nullNode, validNode), "The root node is null or the parent or child node is null");
    CHECK_THROWS_WITH(tree.add_sub_node(validNode, *nullNode), "The root node is null or the parent or child node is null");
}

TEST_CASE("dont add more than 3 children to a 3-k tree")
{
    Tree<int, 3> tree;
    Node<int> root(1);
    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);
    Node<int> n4(5);
    tree.add_root(root);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(root, n3);
    CHECK_THROWS_WITH(tree.add_sub_node(root, n4), "The parent node has the maximum number of children");
}

TEST_CASE("MinHeapIterator functionality")
{
    SUBCASE("Iterate through a tree in min-heap order")
    {
        Node<int> root(5);
        Tree<int> tree3;
        tree3.add_root(root);
        Node<int> child1(3);
        Node<int> child2(8);
        tree3.add_sub_node(root, child1);
        tree3.add_sub_node(root, child2);

        // Expected order of values
        std::vector<int> expectedOrder = {3, 5, 8};
        std::vector<int> actualOrder;

        for (auto it = tree3.begin_min_heap(); it != tree3.end_min_heap(); ++it)
        {
            actualOrder.push_back((*it)->get_value());
        }
       
        REQUIRE(actualOrder == expectedOrder);
    }

    SUBCASE("Iterator out of range throws exception")
    {
        Tree<int> emptyTree;
        // Assuming emptyTree is correctly initialized to be empty
        auto it = emptyTree.begin_min_heap();
        CHECK_THROWS_WITH(*it, "Iterator is out of range");
    }
    SUBCASE("Equality and inequality operators")
    {
        Node<int> root(10);
        Node<int> chid(5);

        Tree<int> tree4;
        tree4.add_root(root);
        tree4.add_sub_node(root, chid);
        auto it1 = tree4.begin_min_heap();
        auto it2 = tree4.begin_min_heap();

        CHECK((*it1)->get_value() == (*it2)->get_value()); // Both at beginning

        ++it1;
        CHECK((*it1)->get_value() != (*it2)->get_value());

        ++it2;
        CHECK((*it1)->get_value() == (*it2)->get_value());
    }
}

TEST_CASE("pre order functionality")
{
    SUBCASE("iterate pre order is correct")
    {
        // Setup a simple tree
        Node<int> root(1);
        Tree<int> tree;
        tree.add_root(root);
        Node<int> child1(2);
        Node<int> child2(3);
        Node<int> child3(4);
        tree.add_sub_node(root, child1);
        tree.add_sub_node(root, child2);
        tree.add_sub_node(child2, child3);
       

        // Expected order of values
        std::vector<int> expectedOrder = {1, 2, 3, 4};
        std::vector<int> actualOrder;

        for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it)
        {
            if (it != tree.end_pre_order())
            { // Redundant in a well-behaved loop but added for clarity
                actualOrder.push_back((*it)->get_value());
            }
        }

        REQUIRE(actualOrder == expectedOrder);
    }

    SUBCASE("Iterator out of range throws exception")
    {
        Tree<int> emptyTree;
        // Assuming emptyTree is correctly initialized to be empty
        auto it = emptyTree.begin_pre_order();
        CHECK_THROWS_WITH(*it, "Iterator out of range");
    }

    SUBCASE("Equality and inequality operators")
    {
        Node<int> root(10);
        Node<int> chid(5);

        Tree<int> tree4;
        tree4.add_root(root);
        tree4.add_sub_node(root, chid);
        auto it1 = tree4.begin_pre_order();
        auto it2 = tree4.begin_pre_order();

        CHECK(it1 == it2);

        ++it1;

        CHECK(it1 != it2);
    }
}

TEST_CASE("post order functionality")
{
    SUBCASE("iterate post order is correct")
    {
        // Setup a simple tree
        Node<double> root_node(1.1);
        Tree<double> tree; // Binary tree that contains doubles.
        tree.add_root(root_node);
        Node<double> n1(1.2);
        Node<double> n2(1.3);
        Node<double> n3(1.4);
        tree.add_sub_node(root_node, n1);
        tree.add_sub_node(root_node, n2);
        tree.add_sub_node(n1, n3);

        // Expected order of values
        std::vector<double> expectedOrder = {1.4, 1.2, 1.3, 1.1};
        std::vector<double> actualOrder;

        for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it)
        {
            if (it != tree.end_post_order())
            { // Redundant in a well-behaved loop but added for clarity
                actualOrder.push_back((*it)->get_value());
            }
        }

        REQUIRE(actualOrder == expectedOrder);
    }

    SUBCASE("Iterator out of range throws exception")
    {
        Tree<int> emptyTree;
        // Assuming emptyTree is correctly initialized to be empty
        auto it = emptyTree.begin_post_order();
        CHECK_THROWS_WITH(*it, "Iterator out of range");
    }

    SUBCASE("Equality and inequality operators")
    {
        Node<int> root(10);
        Node<int> chid(5);

        Tree<int> tree4;
        tree4.add_root(root);
        tree4.add_sub_node(root, chid);
        auto it1 = tree4.begin_post_order();
        auto it2 = tree4.begin_post_order();

        CHECK(it1 == it2);

        ++it1;

        CHECK(it1 != it2);
    }
}
TEST_CASE("in order functionality")
{
    SUBCASE("iterate in order is correct")
    {
        Node<string> root_node("wow");
        Tree<string> tree; // Binary tree that contains strings
        tree.add_root(root_node);
        Node<string> n1("hey");
        Node<string> n2("i am");
        Node<string> n3("a tree ");

        tree.add_sub_node(root_node, n1);
        tree.add_sub_node(root_node, n2);
        tree.add_sub_node(n1, n3);
        // Expected order of values
        std::vector<string> expectedOrder = {"a tree ", "hey", "wow", "i am"};
        std::vector<string> actualOrder;

        for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it)
        {
            if (it != tree.end_in_order())
            { // Redundant in a well-behaved loop but added for clarity
                actualOrder.push_back((*it)->get_value());
            }
        }
        REQUIRE(actualOrder == expectedOrder);
    }

    SUBCASE("Iterator out of range throws exception")
    {
        Tree<string> emptyTree;
        // Assuming emptyTree is correctly initialized to be empty
        auto it = emptyTree.begin_in_order();
        CHECK_THROWS_WITH(*it, "Iterator out of range");
    }

    SUBCASE("Equality and inequality operators")
    {
        Node<string> root("it");
        Node<string> chid("work!");

        Tree<string> tree4;
        tree4.add_root(root);
        tree4.add_sub_node(root, chid);
        auto it1 = tree4.begin_in_order();
        auto it2 = tree4.begin_in_order();

        CHECK(it1 == it2);

        ++it1;

        CHECK(it1 != it2);
    }
}
TEST_CASE("DFS with complex numbers")
{
    SUBCASE("iterate DFS is correct")
    {
        Node<Complex> root(Complex(1, 1));
        Tree<Complex> tree;
        tree.add_root(root);
        Node<Complex> n1(Complex(2, 2));
        Node<Complex> n2(Complex(3, 3));
        Node<Complex> n3(Complex(4, 4));
        tree.add_sub_node(root, n1);
        tree.add_sub_node(root, n2);
        tree.add_sub_node(n1, n3);

        // Expected order of values
        std::vector<Complex> expectedOrder = {Complex(1, 1), Complex(2, 2), Complex(4, 4), Complex(3, 3)};
        std::vector<Complex> actualOrder;

        for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it)
        {
            if (it != tree.end_dfs_scan())
            { // Redundant in a well-behaved loop but added for clarity
                actualOrder.push_back((*it)->get_value());
            }
        }

        REQUIRE(actualOrder == expectedOrder);
    }

    SUBCASE("iterating through an empty tree")
    {
        Tree<Complex> emptyTree;
        auto it = emptyTree.begin_dfs_scan();
        CHECK_THROWS_WITH(*it, "Iterator out of range");
    }

    SUBCASE("Equality and inequality operators")
    {
        Node<Complex> root(Complex(1, 1));
        Tree<Complex> tree4;
        tree4.add_root(root);
        Node<Complex> n1(Complex(2, 2));
        tree4.add_sub_node(root, n1);

        auto it1 = tree4.begin_dfs_scan();
        auto it2 = tree4.begin_dfs_scan();

        CHECK(it1 == it2);

        ++it1;

        CHECK(it1 != it2);
    }
}

TEST_CASE("BFS with 3-k tree")
{
    SUBCASE("iterate BFS is correct")
    {
        Node<double> root_node2(1.1);
        Tree<double, 3> tree2; // Binary tree that contains doubles.
        tree2.add_root(root_node2);
        Node<double> n22(1.2);
        Node<double> n23(1.3);
        Node<double> n24(1.4);
        Node<double> n25(1.5);
        Node<double> n26(1.6);
        tree2.add_sub_node(root_node2, n22);
        tree2.add_sub_node(root_node2, n23);
        tree2.add_sub_node(root_node2, n24);
        tree2.add_sub_node(n23, n26);
        tree2.add_sub_node(n22, n25);
        std::vector<double> expectedOrder = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
        std::vector<double> actualOrder;
        for (auto it = tree2.begin_bfs_scan(); it != tree2.end_bfs_scan(); ++it)
        {
            if (it != tree2.end_bfs_scan())
            { // Redundant in a well-behaved loop but added for clarity
                actualOrder.push_back((*it)->get_value());
            }
        }

        REQUIRE(actualOrder == expectedOrder);
    }

    SUBCASE("iterating through an empty tree")
    {
        Tree<double, 3> emptyTree;
        auto it = emptyTree.begin_bfs_scan();
        CHECK_THROWS_WITH(*it, "Iterator out of range");
    }

    SUBCASE("Equality and inequality operators")
    {
        Node<double> root(10);
        Node<double> chid(5);

        Tree<double, 3> tree4;
        tree4.add_root(root);
        tree4.add_sub_node(root, chid);
        auto it1 = tree4.begin_bfs_scan();
        auto it2 = tree4.begin_bfs_scan();

        CHECK(it1 == it2);

        ++it1;

        CHECK(it1 != it2);
    }
}

TEST_CASE("min heap with complex numbers and 4-k tree")
{
    Tree<Complex, 4> treeC;
    Complex root_value3(2, 2);
    Node<Complex> root_node3(root_value3);
    treeC.add_root(root_node3);

    Node<Complex> n111(Complex(1, 1));
    Node<Complex> n222(Complex(3, 3));
    Node<Complex> n333(Complex(4, 4));
    Node<Complex> n444(Complex(5, 5));

    treeC.add_sub_node(root_node3, n111);
    treeC.add_sub_node(root_node3, n222);
    treeC.add_sub_node(root_node3, n333);
    treeC.add_sub_node(root_node3, n444);

    std::vector<Complex> expectedOrder = {Complex(1, 1), Complex(2, 2), Complex(3, 3), Complex(4, 4), Complex(5, 5)};
    std::vector<Complex> actualOrder;

    for (auto it = treeC.begin_min_heap(); it != treeC.end_min_heap(); ++it)
    {

        actualOrder.push_back((*it)->get_value());
    }
    
    REQUIRE(actualOrder == expectedOrder);
}
