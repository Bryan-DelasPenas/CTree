// File:    CTree.h
// Author:  Bryan Delas Penas 
// Section: 05
// Date:    03/25/19
// Email:   bdelasp1@umbc.edu

#ifndef _CTREE_H
#define _CTREE_H

#include <iostream>

// struct Node: Contains the nodes for the Ctree; contains value, left and right pointer. 
struct Node {

  int m_key;       // Data stored inside of node.
  int m_height;    // Height of the Node
  int m_size;      // Amount of nodes in tree
  
  Node *m_right;   // Pointer for the right of branch 
  Node *m_left;    // Pointer for the left of the branch.
  
};

class CTree {
 public:

  // CTree: Default Constructor for the CTree. Creates a CTree.
  CTree(); 

  // CTree(source): Copy Constructor for CTree 
  CTree(const CTree& source);

  // helperCopy: helper for copy constructor, uses recursion 
  Node* helperCopy(Node* node);

  // ~CTree: Deconstructor for CTree. Deletes all new memory 
  ~CTree();

  // helperDestory: Used in the deconstructor, usees recursion.
  void helperDestroy(Node* node);

  // operator=: Overloaded assigment Operator
  const CTree& operator= (const CTree& rhs);

  // equals: helper function for overloaded assignment operator
  Node* equals(Node* node);

  // max: Gets the greater between two number
  int max(int a, int b); 

  // height: Gets the height of the subtree
  int height(Node *h); 
  
  // insert: Inserts node into Tree. If it key is already stored, do nothing except rebalance the tree 
  void insert(int key);

  // newNode: Creates new node
  Node* newNode(int key);

  // helperInsert: helper function for insert, uses recursion 
  Node* helperInsert(int key, Node *node);

  // size: Gets size of a subtree
  void size(Node *node);
  
  // count: Helper function for size
  int count(Node *node);
  
  // remove: Returns true if the node is there and removes it, else it returns false.
  bool remove(int key);

  // helperRemove: helper function for remove
  Node* helperRemove(int key, Node *node);
  
  // helperMax: Finds the smallest value of a subtree
  Node* helperMax(Node *node);

  // find: Finds the node will the parameter of the key value
  bool find(int key);

  // search: Helper function for find function
  bool search(int key, Node *node);

  // rebalance: rebalance the whole tree
  void rebalance();

  void print(); 
  // array: Puts all nodes into an array
  void array(Node *node, int value[], int& index);

  // createTree: creates tree from array values
  Node* createTree(int value[], int start, int end);  
  
  // Puts Tree in inorder fashion
  void inorder();

  // printInorder: prints in orders uses recursion
  void printInorder(Node* node);

  // locate: Returns if the node is there and the key value it holds.
  bool locate(const char *position, int &key);

  // helperLocate: helper function for locate
  bool helperLocate(const char *str,int &key, Node *node, int index);

  // Avl tree rotations
  Node* singleRightRotation(Node* &node);

  Node* singleLeftRotation(Node* &node);

  Node* doubleRightRotate(Node* &node);
  
  Node* doubleLeftRotate(Node* &node);
private:

  Node *m_root;            // Root is set to null ptr
  int m_left_size;         // Size of the left size of the root
  int m_right_size;        // Size of the right size of the root


};

#endif
