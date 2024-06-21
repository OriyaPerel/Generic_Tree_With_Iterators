/**
 * Demo app for Ex4
 */
#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include "Complex.hpp"

using namespace std;

int main()
{
    std::cout << "Hello, World!" << std::endl;
    Node<double> root_node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);
    // Node<double> n6(1.7);
    // Node<string> root_node("wow");
    // Tree<string> tree; // Binary tree that contains doubles.
    // tree.add_root(root_node);
    // Node<string> n1("hey");
    // Node<string> n2("i am");
    // Node<string> n3("a tree ");
    // Node<string> n4("with");
    // Node<string> n5("strings");

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    // tree.add_sub_node(n2,n6);
    tree.displayTree();

    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    std::cout << "the pre order is: " << std::endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << (*node)->get_value() << " ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    std::cout << '\n';
    std::cout << "the post order is: " << std::endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << (*node)->get_value() << " ";
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
    std::cout << '\n';
    std::cout << "the in order is: " << std::endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << (*node)->get_value() << " ";
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    std::cout << '\n';
    std::cout << "the BFS is: " << std::endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << (*node)->get_value() << " ";
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    std::cout << '\n';
    std::cout << "the for eche: " << std::endl;
    for (auto node : tree)
    {
        cout << node->get_value() << " ";
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    std::cout << '\n';
    std::cout << "the DFS is: " << std::endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        cout << (*node)->get_value() << " ";
    } // prints: 1.1 1.2 1.4 1.5 1.3 1.6

    std::cout << '\n';
    std::cout << "the Min heap is: " << std::endl;
    for (auto node = tree.begin_min_heap(); node != tree.end_min_heap(); ++node)
    {
        cout << (*node)->get_value() << " ";
    } // prints: 1.1 1.2 1.3 1.4 1.5 1.6

    std::cout << "\n*******************otehr tree*******************" << std::endl;
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
    // tree2.displayTree();

    cout << "pre order: \n";
    for (auto node = tree2.begin_pre_order(); node != tree2.end_pre_order(); ++node)
    {

        cout << (*node)->get_value() << " ";
    } // 1.1 1.2 1.5 1.3 1.6 1.4

    cout << endl;
    cout << "post order: \n";
    for (auto node = tree2.begin_post_order(); node != tree2.end_post_order(); ++node)
    {

        cout << (*node)->get_value() << " ";
    } // 1.1 1.2 1.5 1.3 1.6 1.4
    cout << endl;
    cout << "in order: \n";
    for (auto node = tree2.begin_in_order(); node != tree2.end_in_order(); ++node)
    {

        cout << (*node)->get_value() << " ";
    } // 1.1 1.2 1.5 1.3 1.6 1.4
    cout << endl;
    cout << "bfs: \n";
    for (auto node = tree2.begin_bfs_scan(); node != tree2.end_bfs_scan(); ++node)
    {

        cout << (*node)->get_value() << " ";
    } // 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;
    cout << "dfs: \n";
    for (auto node = tree2.begin_dfs_scan(); node != tree2.end_dfs_scan(); ++node)
    {

        cout << (*node)->get_value() << " ";
    } // 1.1 1.2 1.5 1.3 1.6 1.4
    cout << endl;
    cout << "for each: \n";
    for (auto node : tree2)
    {
        cout << node->get_value() << " ";
    } // 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;

    std::cout << "*******************Complex tree*******************" << std::endl;
    Tree<Complex> treeC;
    Complex root_value3(1.1, 0.0);
    Node<Complex> root_node3(root_value3);
    treeC.add_root(root_node3);

    Node<Complex> n111(Complex(0.5, 1.2));
    Node<Complex> n222(Complex(0.8, -1.1));
    Node<Complex> n333(Complex(-0.2, 0.9));
    Node<Complex> n444(Complex(1.5, -0.5));
    Node<Complex> n555(Complex(-1.3, 0.4));

    treeC.add_sub_node(root_node3, n111);
    treeC.add_sub_node(root_node3, n222);
    treeC.add_sub_node(n111, n333);
    treeC.add_sub_node(n111, n444);
    treeC.add_sub_node(n222, n555);

    std::cout << "The pre-order for complex is: " << std::endl;
    for (auto it = treeC.begin_pre_order(); it != treeC.end_pre_order(); ++it)
    {
        std::cout << (*it)->get_value() << " ";
    } //(1.1+0!) (0.5+1.2!) (-0.2+0.9!) (1.5+-0.5!) (0.8+-1.1!) (-1.3+0.4!)

    std::cout << std::endl;
    std::cout << "The for each for complex is: " << std::endl;
    for (auto node : treeC)
    {
        cout << node->get_value() << " ";
    } // 1.1+0! 0.5+1.2! -0.2+0.9! 1.5+-0.5! 0.8+-1.1! -1.3+0.4!

    std::cout << std::endl;
    std::cout << "The post-order for complex is: " << std::endl;
    for (auto it = treeC.begin_post_order(); it != treeC.end_post_order(); ++it)
    {
        std::cout << (*it)->get_value() << " ";
    } // (1.1+0!) (0.5+1.2!) (-0.2+0.9!) (1.5+-0.5!) (0.8+-1.1!) (-1.3+0.4!)

    std::cout << std::endl;
    std::cout << "the min heap for complex is: " << std::endl;
    for (auto it = treeC.begin_min_heap(); it != treeC.end_min_heap(); ++it)
    {
        std::cout << (*it)->get_value() << " ";
    } // (1.1+0!) (0.5+1.2!) (0.8+-1.1!) (-0.2+0.9!) (1.5+-0.5!) (-1.3+0.4!)

    std::cout << std::endl;
    treeC.displayTree();

    // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */
    return 0;
}
