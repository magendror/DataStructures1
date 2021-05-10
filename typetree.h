#ifndef TYPE_TREE_H
#define TYPE_TREE_H
#include <iostream>
#include "cars.h"

class TypeNode {
  public:
  CarType* key;
  TypeNode *left;
  TypeNode *right;
  int height;
  TypeNode(CarType* key);
};

// Calculate height
int height(TypeNode* N) {
  if (N == NULL){
    return 0;
  }
  return N->height;
}

// New TypeNode creation
TypeNode *newTypeNode(CarType* key) {
  TypeNode *node = new TypeNode(key);
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

// Rotate right
TypeNode *rightRotate(TypeNode *n) {
  TypeNode* temp_left = n->left;
  TypeNode* temp_right = temp_left->right;
  temp_left->right = n;
  n->left = temp_right;
  n->height = max(height(n->left),height(n->right)) + 1;
  temp_left->height = max(height(temp_left->left),height(temp_left->right)) + 1;
  return temp_left;
}

// Rotate left
TypeNode *leftRotate(TypeNode *x) {
  TypeNode* temp_left = x->right;
  TypeNode* temp_right = temp_left->left;
  temp_left->left = x;
  x->right = temp_right;
  x->height = max(height(x->left),height(x->right)) + 1;
  temp_left->height = max(height(temp_left->left),height(temp_left->right)) + 1;
  return temp_left;
}

// Get the balance factor of each TypeNode
int getBalanceFactor(TypeNode *N) {
  if (N == NULL){
    return 0;
  }
  return height(N->left) - height(N->right);
}

//Find the correct postion by typeID
TypeNode* findTypeNode(TypeNode *node, int type_id){
  if(node==NULL){
    return node;
  }
  if (node->key->type_id> type_id){
    return (findTypeNode(node->left, type_id));
  }
  else if (type_id > node->key->type_id)
  {
    return (findTypeNode(node->right, type_id));
  }
  else
    return node;
}

// Insert a TypeNode
TypeNode* insertTypeNode(TypeNode* node, CarType* key) {
  // Find the correct postion and insert the TypeNode
  if (node == NULL){
    return (newTypeNode(key));
  }
  if (*(node->key) > *(key)){
    node->left = insertTypeNode(node->left, key);
  }
  else if (*(key) > *(node->key)){
    node->right = insertTypeNode(node->right, key);
  }
  else{
    return node;
  }

  // Update the balance factor of each TypeNode and
  // balance the tree
  node->height = 1 + max(height(node->left),height(node->right));
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    if (*(node->left->key) > *(key)) {
      return rightRotate(node);
    }
    else if (*(key) > *(node->left->key)){
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  if (balanceFactor < -1) {
    if (*(key) > *(node->right->key)) {
      return leftRotate(node);
    }
    else if (*(node->right->key) > *(key)) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  return node;
}

// TypeNode with minimum value
TypeNode* TypeNodeWithMimumValue(TypeNode* node) {
  TypeNode *current = node;
  while (current->left != NULL){
    current = current->left;
  }
  return current;
}

// Delete a TypeNode
TypeNode *deleteTypeNode(TypeNode *root, CarType* key) {
  // Find the TypeNode and delete it
  if (root == NULL){
    return root;
  }
  if (*(root->key) > *(key)){
    root->left = deleteTypeNode(root->left, key);
  }
  else if (*(key) > *(root->key)){
    root->right = deleteTypeNode(root->right, key);
  }
  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      TypeNode *temp = root->left ? root->left : root->right;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      }
      else
        *root = *temp;
      delete temp;
    }
    else {
      TypeNode *temp = TypeNodeWithMimumValue(root->right);
      root->key = temp->key;
      root->right = deleteTypeNode(root->right,temp->key);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each TypeNode and
  // balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));
  int balanceFactor = getBalanceFactor(root);
  if (balanceFactor > 1) {
    if (getBalanceFactor(root->left) >= 0) {
      return rightRotate(root);
    }
    else {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
  }
  if (balanceFactor < -1) {
    if (getBalanceFactor(root->right) <= 0) {
      return leftRotate(root);
    }
    else {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
  }
  return root;
}
#endif
