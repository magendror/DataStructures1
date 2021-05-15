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
  ~TypeNode()=default;
};

TypeNode::TypeNode(CarType* key):key(key),left(NULL),right(NULL),height(1){}

int height(TypeNode* N) {
  if (N == NULL){
    return 0;
  }
  return N->height;
}

TypeNode *newTypeNode(CarType* key) {
  TypeNode *node = new TypeNode(key);
  return (node);
}

TypeNode *rightRotate(TypeNode *n) {
  TypeNode* temp_left = n->left;
  TypeNode* temp_right = temp_left->right;
  temp_left->right = n;
  n->left = temp_right;
  n->height = max_int(height(n->left),height(n->right)) + 1;
  temp_left->height = max_int(height(temp_left->left),height(temp_left->right)) + 1;
  return temp_left;
}

TypeNode *leftRotate(TypeNode *x) {
  TypeNode* temp_left = x->right;
  TypeNode* temp_right = temp_left->left;
  temp_left->left = x;
  x->right = temp_right;
  x->height = max_int(height(x->left),height(x->right)) + 1;
  temp_left->height = max_int(height(temp_left->left),height(temp_left->right)) + 1;
  return temp_left;
}

int getBalanceFactor(TypeNode *N) {
  if (N == NULL){
    return 0;
  }
  return height(N->left) - height(N->right);
}

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

TypeNode* insertTypeNode(TypeNode* node, CarType* key) {
  //find position and insert recursively
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
  // balance the tree
  node->height = max_int(height(node->left),height(node->right)) + 1;
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    if (getBalanceFactor(node->left) >= 0) {
      return rightRotate(node);
    }
    else if (getBalanceFactor(node->left) == -1){
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  if (balanceFactor < -1) {
    if (getBalanceFactor(node->right) <= 0) {
      return leftRotate(node);
    }
    else if (getBalanceFactor(node->right) == 1) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  return node;
}

TypeNode* TypeNodeWithMimumValue(TypeNode* node) {
  TypeNode *current = node;
  if(current==NULL){
    return current;
  }
  while (current->left != NULL){
    current = current->left;
  }
  return current;
}

TypeNode *deleteTypeNode(TypeNode *root, CarType* key) {
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
  // balance the tree
  root->height = max_int(height(root->left),height(root->right)) + 1;
  int balanceFactor = getBalanceFactor(root);
  if (balanceFactor > 1) {
    if (getBalanceFactor(root->left) >= 0) {
      return rightRotate(root);
    }
    else if(getBalanceFactor(root->left) == -1){
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
  }
  if(balanceFactor < -1) {
    if (getBalanceFactor(root->right) <= 0) {
      return leftRotate(root);
    }
    else if(getBalanceFactor(root->right) == 1) {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
  }
  return root;
}
#endif
