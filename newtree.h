#ifndef NEW_TREE
#define NEW_TREE
#include <iostream>
#include "cars.h"

class NewNode {
  public:
  CarType* key;
  NewNode *left;
  NewNode *right;
  NewNode *father;
  int height;
  CarModelList* newlist;
  NewNode(CarType* key,NewNode *father);
  ~NewNode()=default;
};

NewNode::NewNode(CarType* key,NewNode *father):key(key),left(NULL),right(NULL),father(father),height(1){}

// Calculate height
int height(NewNode* N) {
  if (N == NULL)
    return 0;
  return N->height;
}

// New Node creation
NewNode* newNewNode(CarType* key,NewNode *father) {
  NewNode *node = new NewNode(key,father);
  return (node);
}

// Rotate right
NewNode* rightRotate(NewNode* n) {
  NewNode* temp_left = n->left;
  NewNode* temp_right = temp_left->right;
  temp_left->right = n;
  n->left = temp_right;
  temp_left->father=n->father;
  n->father=temp_left;
  temp_right->father=n;
  n->height = max_int(height(n->left),height(n->right)) + 1;
  temp_left->height = max_int(height(temp_left->left),height(temp_left->right)) + 1;
  return temp_left;
}

// Rotate left
NewNode* leftRotate(NewNode* x) {
  NewNode* temp_left = x->right;
  NewNode* temp_right = temp_left->left;
  temp_left->left = x;
  x->right = temp_right;
  temp_left->father=x->father;
  x->father=temp_left;
  temp_right->father=x;
  x->height = max_int(height(x->left),height(x->right)) + 1;
  temp_left->height = max_int(height(temp_left->left),height(temp_left->right)) + 1;
  return temp_left;
}

// Get the balance factor of each Node
int getBalanceFactor(NewNode* N) {
  if (N == NULL)
    return 0;
  return height(N->left) -
       height(N->right);
}

// Insert a Node
NewNode* insertNewNode(NewNode* node, CarType* key, NewNode *father=NULL) {
  // Find the correct postion and insert the Node
  if (node == NULL)
    return (newNewNode(key,father));
  if (node->key> key)
    node->left = insertNewNode(node->left, key, node);
  else if (key > node->key)
    node->right = insertNewNode(node->right, key, node);
  else
    return node;

  // Update the balance factor of each Node and
  // balance the tree
  node->height = 1 + max_int(height(node->left),height(node->right));
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    if (node->left->key> key) {
      return rightRotate(node);
    } else if (key > node->left->key) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  if (balanceFactor < -1) {
    if (key > node->right->key) {
      return leftRotate(node);
    } else if (node->right->key > key) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  return node;
}

// Node with minimum value
NewNode* NewNodeWithMimumValue(NewNode* node) {
  NewNode *current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
}

NewNode *findNewNode(NewNode *node, int type_id){

  if(node==NULL){
    return node;
  }
  if (node->key->type_id> type_id){
    return (findNewNode(node->left, type_id));
  }
  else if (type_id > node->key->type_id)
  {
    return (findNewNode(node->right, type_id));
  }
  else
    return node;
}

// Delete a Node

///////Need to move also list, not just key!!!!////

NewNode* deleteNewNode(NewNode* root, CarType* key) {
  // Find the Node and delete it
  if (root == NULL)
    return root;
  if (root->key > key)
    root->left = deleteNewNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNewNode(root->right, key);
  else {
    if ((root->left == NULL) ||
      (root->right == NULL)) {
      NewNode *temp = root->left ? root->left : root->right;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      delete temp;
    }
    else {
      NewNode *temp = NewNodeWithMimumValue(root->right);
      root->key = temp->key;
      root->right = deleteNewNode(root->right,
                   temp->key);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each Node and
  // balance the tree
  root->height = 1 + max_int(height(root->left),height(root->right));
  int balanceFactor = getBalanceFactor(root);
  if (balanceFactor > 1) {
    if (getBalanceFactor(root->left) >= 0) {
      return rightRotate(root);
    } else {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
  }
  if (balanceFactor < -1) {
    if (getBalanceFactor(root->right) <= 0) {
      return leftRotate(root);
    } else {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
  }
  return root;
}
#endif
