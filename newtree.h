#ifndef NEW_TREE
#define NEW_TREE
#include <iostream>
#include "cars.h"

class NewNode {
  public:
  CarType* key;
  NewNode *left;
  NewNode *right;
  int height;
  CarModelList* newlist;
  NewNode(CarType* key);
  ~NewNode()=default;
};

NewNode::NewNode(CarType* key):key(key),left(NULL),right(NULL),height(1){}

// Calculate height
int height(NewNode* N) {
  if (N == NULL)
    return 0;
  return N->height;
}

// New Node creation
NewNode* newNewNode(CarType* key) {
  NewNode *node = new NewNode(key);
  return (node);
}

// Rotate right
NewNode* rightRotate(NewNode* n) {
  NewNode* temp_left = n->left;
  NewNode* temp_right = temp_left->right;
  temp_left->right = n;
  n->left = temp_right;
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
NewNode* insertNewNode(NewNode* node, CarType* key) {
  // Find the correct postion and insert the Node
  if (node == NULL)
    return (newNewNode(key));
  if (*(node->key)> *(key)){
    node->left = insertNewNode(node->left, key);
  }
  else if (*(key) > *(node->key)){
    node->right = insertNewNode(node->right, key);
  }
  else {
    return node;
  }

  // Update the balance factor of each Node and
  // balance the tree
  node->height = 1 + max_int(height(node->left),height(node->right));
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    if (getBalanceFactor(node->left) >= 0) {
      return rightRotate(node);
    }
    else if (getBalanceFactor(node->left) == -1) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  if (balanceFactor < -1) {
    if (getBalanceFactor(node->right)<=0) {
      return leftRotate(node);
    }
    else if (getBalanceFactor(node->right)==1) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  return node;
}

// Node with minimum value
NewNode* NewNodeWithMimumValue(NewNode* node) {
  NewNode *current = node;
  if(current==NULL){
    return current;
  }
  while (current->left != NULL){
    current = current->left;
  }
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

NewNode* deleteNewNode(NewNode* root, CarType* key) {
  // Find the Node and delete it
  if (root == NULL){
    return root;
  }
  if (root->key > key){
    root->left = deleteNewNode(root->left, key);
  }
  else if (key > root->key){
    root->right = deleteNewNode(root->right, key);
  }
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
      root->right = deleteNewNode(root->right,temp->key);
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
    }
    else if (getBalanceFactor(root->left) == -1) {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
  }
  if (balanceFactor < -1) {
    if (getBalanceFactor(root->right) <= 0) {
      return leftRotate(root);
    }
    else if (getBalanceFactor(root->right) == 1) {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
  }
  return root;
}
#endif
