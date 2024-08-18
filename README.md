#  Template class of Tree and Iterators
## Project Description
In this project i implemented a template container that represents a K-ary tree that can hold Nodes of any type.

## All the different classes and their hierarchy
  - tree.hpp - a Template K-ary tree container, has a Node<T>* root. uses the iterators.hpp to travers the tree in different ways (depends what K is the tree). the tree class uses the type_traits library to use compile-time type manipulation based on certain conditions (see Explenation about the tree container usage with iterators below for additional explenation). In order to print the tree using gui we used QT library.
 - node.hpp - a Template Node class to hold any type.
complex.hpp - represents complex numbers, can be used by node.hpp to store complex numbers as data.
We have 6 different iterator classes inside the file iterators.hpp:
- in_order_iterator - Traverses Binary tree in in-order way, for any (K!=2)-Tree will travers the tree using dfs.
- pre_order_iterator - Traverses Binary tree in pre-order way, for any (K!=2)-Tree will travers the tree using dfs.
- post_order_iterator - Traverses Binary tree in post-order way, for any (K!=2)-Tree will travers the tree using dfs.
- min_heap_iterator - Turns a Binary tree to a minimum heap and travers it ,for any (K!=2)-Tree will travers the tree using dfs.
- dfs_iterator - Works on any K-tree.
- bfs_iterator - Works on any K-tree.



# הערות 
1. בבנאי כאשר מוסיפים ילדים לקודקוד הבנים נוספים משמאל לימין
2. ניתן להוסיף ילדים רק באמצעות המתודה add_sub_node
3. בפרויקט שמתי את כל המימושים בקובץ hpp מכיון שמדובר במחלקות template , עבור כל איטרטור בניתי מחלקה שמששמת את כל האופרטורים הדרושים לאיטרטור ועוד פונקציות נוספות למימוש הלוגיקה של המעבר על העץ.


