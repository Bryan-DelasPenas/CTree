// File:    CTree.cpp 
// Author:  Bryan Delas Penas 
// Section: 05
// Date:    03/29/19
//

#include "CTree.h"

// Ctree: Constructor for the CTree object 
CTree::CTree()
{
  m_root = NULL;    // Sets root to equal null
  m_left_size = 0;  // Sets left size to 0 
  m_right_size = 0; // Sets right size to 0
}

// CTree(source): Copy Constructor for CTree
CTree::CTree(const CTree& source)
{
  if(source.m_root == NULL)
    {
      std:: cout << "Orginal Tree is empty" << std::endl; 
    }
  else
    {
      m_root = helperCopy(source.m_root); 
    }
}

// helperCopy: helper for copy constructor, uses recursion
Node* CTree::helperCopy(Node *node)
{
  if(node == NULL)
    {
      return NULL;
    }
  else
    {
      Node *copy = new Node();
      copy->m_key = node->m_key;
      copy->m_size = node->m_size;
      copy->m_height = node->m_height;
      copy->m_left = helperCopy(node->m_left);
      copy->m_right = helperCopy(node->m_right);
      return copy;
    }
}

// ~CTree: Deconstructor for CTree. Deletes all new memory
CTree::~CTree()
{
  if(m_root != NULL)
    {
      helperDestroy(m_root); // Calls the recursive destory function
    }
   m_root = NULL;
}

// Travels the tree to delete it. Travels post order
void CTree::helperDestroy(Node* node)
{
  // While the node is not null, it will kept on calling the function.
  if(node != NULL)
    {
      helperDestroy(node->m_left);  // Goes to the left branch
      helperDestroy(node->m_right); // Goes to the right branch
      delete node;            // Deletes node

    }
}

// operator=: Overloaded assigment Operator
const CTree& CTree::operator= (const CTree& rhs)
{
  if(this != &rhs)
    {
      if(m_root != NULL)
	{
	  helperDestroy(m_root);     
	}
      if(rhs.m_root == NULL)
	{
	  m_root = NULL;
	}
      else
	{
	  m_root = equals(rhs.m_root);
	}      
    }
  return *this; 
}

//
Node* CTree::equals(Node *node)
{
  if(node == NULL)
    {
      return NULL;
    }
  else
    {
      Node *copy = new Node();
      copy->m_key = node->m_key;
      copy->m_size = node->m_size;
      copy->m_height = node->m_height;
      copy->m_left = helperCopy(node->m_left);
      copy->m_right = helperCopy(node->m_right);
      return copy;
    }
}

// Max: Compares two numbers and returns the greater one
int CTree::max(int a, int b)
{
  if(a > b )
    {
      return a; 
    }
  else
    {
      return b; 
    }
}

// height: Takes in a node, and returns the height
int CTree::height(Node *h)
{
  // Checks to see if Node is null 
  if(h == NULL)
    {
      return 0; // This is not a leave 
    }

  // Recusive Call
  else
    {
      return max(height(h->m_left), height(h->m_right)) + 1;
    }
 
}

// Insert: Takes in a key value, and inserts it into the CTree
void CTree::insert(int key)
{
  // If the value is the first inserted value, makes it to the root
  if(m_root == NULL)
    {
      Node *root = new Node(); // Creates a new node

      root->m_right = NULL;    // Sets root's right branch to NULL
      root->m_left = NULL;     // Sets root's left branch to NULL
      root->m_key = key;       // Sets root's key to key
      root->m_height = 0;      // Sets the height of the root to 0
      root->m_size = 1;
      m_root = root;           // Points m_root to root
    }

  // If the key value is not in the tree
  if( find(key) == false )
    {

      rebalance();            // Rebalances the Tree
      helperInsert(key, m_root); // Calls insert  helper function and inserts
      rebalance();
    }

  // If the key value is in the tree
  else
    {
      rebalance(); // Rebalances the Tree
    }
}

// NewNode: Takes in a key and creates a new node Object
Node* CTree::newNode(int key)
{
  Node* node = new Node();  // Creates a new node

  node->m_key = key;        // Puts data into node
  node->m_left = NULL;      // Sets left ptr to null
  node->m_right = NULL;     // Sets right ptr to null
  node->m_size = 1;         // Sets height to one
  return node;              // Returns node
}


// helperInsert: Used for the insertion function, recursive funtion 
Node* CTree::helperInsert(int key, Node *node)
{
  // Base case: if the node points to null, this is where the insert should happen  
  if(node == NULL)
    {
      node = new Node();  // Creates a new Node object

      node->m_right = NULL;     // Sets child's right to NULL
      node->m_left = NULL;      // Sets child's left to NULL
      node->m_key = key;        // Sets key to key
      node->m_size = 1;
    }
  
    
      // Less then goes left 
  else  if(node->m_key > key)
    {
      node->m_left = helperInsert(key, node->m_left); // Recursive call to move to left 

      /*if(height(node->m_left) - height(node->m_right) == 2)
	{
	  if(key < node->m_left->m_key)
	    {
	      node = singleRightRotation(node);
	      
	    }
	  else
	    {
	      node = doubleRightRotate(node);
	    }
	    }*/
    }
      
      // Greater then goes right 
  else if(node->m_key < key) 
    {
      node->m_right = helperInsert(key, node->m_right); // Recursive call to move right 
      /*
      if(height(node->m_right) - height(node->m_left) == 2)
	{
	  if(key > node->m_right->m_key)
	    {
	      node = singleLeftRotation(node);
	      
	    }
	  else
	    {
	      node = doubleLeftRotate(node);
	    }
	    }*/
    }    
    
  // Calulates height
  node->m_height = max(height(node->m_left) , height(node->m_right));
 
  return node;
}

// size: Gets the size of a subtree
void CTree::size(Node *node)
{
  // Base case: 
  if(node == NULL)
    {
      return;
    }

  // Recursive case:
  else
    {
      node->m_size = 0;
      size(node->m_left);
      node->m_size = count(node);
      size(node->m_right);
    }
}

// count: helper function for size, calculates the size. recusive funtion
int CTree::count(Node *node)
{
  //  node->m_size = 0; 
  // Base case:
  if(node == NULL)
    {
      return 0 ;
    }
 
    // Recursive case:
  else
    {
      return(count(node->m_left) + count(node->m_right) + 1);
    }
}

// remove: Returns true if the node is there and removes it, else it returns false.
bool CTree::remove(int key)
{
  if(find(key) == true)
    {
      rebalance();
      m_root = helperRemove(key, m_root);     
      //      size(m_root);
      rebalance();
      return true;
    }

  else
    {
      return false; 
    }
}

// helperRemove: helper function for remove
Node* CTree::helperRemove(int key, Node *node)
{
  // base case
  if(node == NULL)
    {
      return node; 
    }

  // recusrive case
  if(node->m_key > key)
    {
      node->m_left = helperRemove( key, node->m_left);
    }

  // recursive case dos
  else if(node->m_key < key)
    {
      node->m_right = helperRemove( key, node->m_right);
    }
  
  // The key value is equal 
  else
    {
      //
      if(node->m_left == NULL and node->m_right == NULL)
	{
	  delete node;
	  node = NULL; 
	}

      //
      else if(node->m_left == NULL)
	{
	  Node *temp = node; 
	  node = node->m_right; 
	  delete temp; 
	}

      //
      else if(node->m_right == NULL)
	{
	  Node *temp = node;
	  node = node->m_left;
	  delete temp;
	}
      else
	{
	  // Node that needs to be removed has two children
	  Node *temp = helperMax(node->m_left);
	  
	  node->m_key = temp->m_key;
	  
	  node->m_left = helperRemove(temp->m_key, node->m_left); 
	}
    }

  //Another base case, to prevent a segfault. 
  if(node == NULL)
    {
      return node; 
    }
  node->m_height = max(height(node->m_left) , height(node->m_right));
  return node;
}

// helperMax: Finds the smallest value of a subtree
Node* CTree::helperMax(Node* node)
{
  if(node == NULL)
    {
      return NULL;
    }
  else
    {
      
      while(node->m_right != NULL)
	{
	  node = node->m_right; 
	}
      return node; 
    }
}

// find: Finds the node will the parameter of the key value
bool CTree::find(int key)
{
  bool flag;

  Node *temp = m_root;

  flag = search(key, temp);

  if(flag == false)
    {
      return false;
    }

  //
  else
    {

      return true;
    }
}

// search: Helper function for find function
bool CTree::search(int key, Node *node)
{
  // Checks to see if the value is in there or not
  if(node == NULL)
    {
      return false;
    }

   // If not goes to here
   else
     {

       // Returns true if the key value is there 
       if(node->m_key == key)
	 {
	   return true;      
	 }
       
       //Goes left
       if(node->m_key > key)
	 {
	
	   return search(key, node->m_left);  // If it is less than go left
	 }

       //Goes right
       else
	 {
	
	   return search(key, node->m_right); // If is greater go to the right
	 }
     }
}




// rebalance: rebalance the whole tree
void CTree::rebalance()
{
  size(m_root);
  if(m_root == NULL)
    {
      return;
    }
  
  else if(m_root->m_left == NULL or m_root->m_right == NULL)
    {
      return;
    }

  else 
    {
      m_left_size = m_root->m_left->m_size;   // Gets left size
      m_right_size = m_root->m_right->m_size; // Gets right size

      int start = 0;                          // Make the start 0
      int end = (m_root->m_size);             // Make the end the size of the tree
      int index = 0;                          // Sets a index
      int keys[end - 1];                      // Declares array to be the size of how much nodes there is

      // If left side is greater than right size
      if(m_left_size > m_right_size)
        {

          // Checks to see if the size different is two
          if(m_left_size - m_right_size > 2)
            {
              array(m_root, keys, index);                // Puts the data into an array
              helperDestroy(m_root);                     // Destroys the tree
              m_root = createTree(keys, start, end - 1); // Recreate the tree
              //size(m_root);                              // Recounts the size
            }
        }

      // Same thing but if the right size is bigger
      else if(m_right_size > m_left_size)
        {
          if(m_right_size - m_left_size > 2)
            {
              array(m_root, keys, index);
              helperDestroy(m_root);
              m_root = createTree(keys, start, end - 1);
              //size(m_root);
	    }
	}
    }
  size(m_root);
}

// array: Puts all nodes into an array
void CTree::array(Node *node, int value[], int& index)
{
  if(node == NULL)
    {
      return;
    }
  if(node->m_left != NULL)
    {
      array(node->m_left, value, index);    
    }

  value[index] = node->m_key; 
  index++;

  if(node->m_right != NULL)
    {
      array(node->m_right, value, index);
     
    }
}

// createTree: creates tree from array values
Node* CTree::createTree(int value[], int start, int end )
{
  if(start > end)
    {
      return NULL;
    }
  int mid = (start + end) / 2; 
  Node *root = newNode( value[mid]);
  
  root->m_left = createTree(value, start, mid - 1);
  root->m_right = createTree(value, mid + 1, end); 
  root->m_height = max(height(root->m_left) , height(root->m_right));
  return root; 
}

// inorder: Prints out the tree 
void CTree::inorder()
{ 
  if(m_root == NULL)
    {
      std::cout << "Tree is empty" << std::endl;
    }
  else
    {
      printInorder(m_root); 
    }
}

// printInorder: Recursive function for printing the tree inorder
void CTree::printInorder(Node* node)
{

  if(node == NULL)
    {
      return;
    }
  std::cout << "(";
  printInorder(node->m_left);

  std::cout<< node->m_key << ":" << node->m_height <<  ":" << node->m_size;

  printInorder(node->m_right);
  std::cout << ")";
}

// locate: Returns if the node is there and the key value it holds.
bool CTree::locate(const char *postion, int &key)
{
  // This is the biggest the char array can possibly get. 
  int index = 0;
  bool flag = helperLocate(postion, key, m_root, index);
  
  if(flag == true)
    {
      return true;
    }

  else
    {
      return false; 
    }
}

// helperLocate: helper function for locate
bool CTree::helperLocate(const char *str,int &key, Node *node, int index)
{
   if(node == NULL)
    {
      return false;
    }

   else if(str[index] == 'L')
    {  
      return helperLocate(str, key, node->m_left, index + 1);	  
 
    }
   else if(str[index] == 'R')
    {
      return helperLocate(str, key, node->m_right, index + 1);
    
    }
  
  else if(str[index] == '\0')
    {
      key = node->m_key;
      return true;
    }

  else
    {
      return false;
    }
}

Node* CTree::singleRightRotation(Node* &node)
{
  Node* u = node->m_left;
  node->m_left = u->m_right;
  u->m_right = node;
  node->m_height = max(height(node->m_left), height(node->m_right))+1;
  u->m_height = max(height(u->m_left), node->m_height)+1;
  return u;
}

Node* CTree::singleLeftRotation(Node* &node)
{
  Node* u = node->m_right;
  node->m_right = u->m_left;
  u->m_left = node;
  node->m_height = max(height(node->m_left), height(node->m_right))+1;
  u->m_height = max(height(node->m_right), node->m_height)+1 ;
  return u;

}
Node* CTree::doubleRightRotate(Node* &node)
{
  node->m_left = singleLeftRotation(node->m_left);
  return singleRightRotation(node);

}
Node* CTree::doubleLeftRotate(Node* &node)
{
  node->m_right = singleRightRotation(node->m_right);
  return singleLeftRotation(node);


}
