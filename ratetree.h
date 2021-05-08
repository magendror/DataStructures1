#ifndef RATE_TREE
#define RATE_TREE
#include <iostream>
#include "cars.h"


class RateNode{
  public:
  CarModel* key;
  RateNode*left;
  RateNode*right;
  int height;
  RateNode(CarModel* key);
};

// int max(int a, int b);

// Calculate height
int height(RateNode*N) {
  if (N == NULL)
    return 0;
  return N->height;
}

// New RateNodecreation
RateNode* newRateNode(CarModel* key) {
  RateNode* node= new RateNode(key);
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

// Rotate right
RateNode* rightRotate(RateNode* y) {
  RateNode* x = y->left;
  RateNode* T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left),height(y->right)) + 1;
  x->height = max(height(x->left),height(x->right)) + 1;
  return x;
}

// Rotate left
RateNode* leftRotate(RateNode* x) {
  RateNode* y = x->right;
  RateNode* T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left),height(x->right)) + 1;
  y->height = max(height(y->left),height(y->right)) + 1;
  return y;
}

// Get the balance factor of each node
int getBalanceFactor(RateNode* N) {
  if (N == NULL){
    return 0;
  }
  return height(N->left) - height(N->right);
}

//Find the correct postion by rate and id
RateNode* findRateNodeByRate(RateNode* node, int rate, int modelid, int type_id){
  if(node==NULL){
    return node;
  }
  if (node->key->rate > rate){
    return (findRateNodeByRate(node->left, rate,modelid, type_id));
  }
  else if (node->key->rate < rate){
    return (findRateNodeByRate(node->right, rate,modelid, type_id));
  }
  else{
    if(node->key->type_id > type_id){
      return (findRateNodeByRate(node->left, rate,modelid, type_id));
    }
    else if (node->key->type_id < type_id){
      return (findRateNodeByRate(node->right, rate,modelid, type_id));
    }
    else{
      if(node->key->model_id > modelid){
        return (findRateNodeByRate(node->left, rate,modelid, type_id));
      }
      else if(node->key->model_id < modelid){
        return (findRateNodeByRate(node->right, rate,modelid, type_id));
      }
      else
        return node;
    }
  }
}


// Insert a node
RateNode* insertRateNode(RateNode* node, CarModel* key) {
  // Find the correct postion and insert the node
  if (node== NULL)
    return (newRateNode(key));
  if (*(node->key)> *(key))
    node->left = insertRateNode(node->left, key);
  else if (*(key) > *(node->key))
    node->right = insertRateNode(node->right, key);
  else
    return node;

  // Update the balance factor of each RateNodeand
  // balance the tree
  node->height = 1 + max(height(node->left),
               height(node->right));
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    if (*(node->left->key) > *(key)) {
      return rightRotate(node);
    }
    else if (*(key) > *(node->left->key)) {
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

// RateNodewith minimum value
RateNode* RateNodeWithMimumValue(RateNode* node) {
  RateNode*current = node;
  while (current->left != NULL){
    current = current->left;
  }
  return current;
}

// Delete a node
RateNode* deleteRateNode(RateNode* root, CarModel* key) {
  // Find the RateNodeand delete it
  if (root == NULL){
    return root;
  }
  if (*(root->key) > *(key)){
    root->left = deleteRateNode(root->left, key);
  }
  else if (*(key) > *(root->key)){
    root->right = deleteRateNode(root->right, key);
  }
  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      RateNode* temp = root->left ? root->left : root->right;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      }
      else{
        *root = *temp;
      }
      free(temp);
    }
    else {
      RateNode*temp = RateNodeWithMimumValue(root->right);
      root->key = temp->key;
      root->right = deleteRateNode(root->right,temp->key);
    }
  }
  if (root == NULL){
    return root;
  }

  // Update the balance factor of each RateNodeand
  // balance the tree
  root->height = 1 + max(height(root->left),height(root->right));
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