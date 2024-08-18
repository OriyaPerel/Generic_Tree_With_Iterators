#  Template class of Tree and Iterators
## Project Description
In this project i implemented a template container that represents a K-ary tree that can hold Nodes of any type.

## All the different classes and their hierarchy
  - tree.hpp - implement the Tree class and the print the tree using gui I used SFML library.
 - node.hpp - a Template Node class to hold any type.
complex.hpp - represents complex numbers, can be used by node.hpp to store complex numbers as data.
We have 6 different iterator classes inside the file iterators.hpp:
- in_order_iterator - Traverses Binary tree in in-order way, for any (K!=2)-Tree will travers the tree using dfs.
- pre_order_iterator - Traverses Binary tree in pre-order way, for any (K!=2)-Tree will travers the tree using dfs.
- post_order_iterator - Traverses Binary tree in post-order way, for any (K!=2)-Tree will travers the tree using dfs.
- min_heap_iterator - Turns a Binary tree to a minimum heap and travers it ,for any (K!=2)-Tree will travers the tree using dfs.
- dfs_iterator - Works on any K-tree.
- bfs_iterator - Works on any K-tree.

