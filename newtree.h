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
  CarModel* newlist;
  NewNode(CarType* key);
};

// int max(int a, int b);

// Calculate height
int height(NewNode* N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

// New Node creation
NewNode* newNewNode(CarType* key) {
  NewNode *node = new NewNode(key);
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

// Rotate right
NewNode* rightRotate(NewNode* y) {
  NewNode *x = y->left;
  NewNode *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left),
          height(y->right)) +
        1;
  x->height = max(height(x->left),
          height(x->right)) +
        1;
  return x;
}

// Rotate left
NewNode* leftRotate(NewNode* x) {
  NewNode *y = x->right;
  NewNode *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left),
          height(x->right)) +
        1;
  y->height = max(height(y->left),
          height(y->right)) +
        1;
  return y;
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
  if (node->key> key)
    node->left = insertNewNode(node->left, key);
  else if (key > node->key)
    node->right = insertNewNode(node->right, key);
  else
    return node;

  // Update the balance factor of each Node and
  // balance the tree
  node->height = 1 + max(height(node->left),
               height(node->right));
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
      free(temp);
    } else {
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
  root->height = 1 + max(height(root->left),
               height(root->right));
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
