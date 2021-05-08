#ifndef RATE_TREE
#define RATE_TREE
#include <iostream>
#include "cars.h"


class RatelNode{
  public:
  CarModel* key;
  RatelNode*left;
  RatelNode*right;
  int height;
  RatelNode(CarModel* key);
};

// int max(int a, int b);

// Calculate height
int height(RatelNode*N) {
  if (N == NULL)
    return 0;
  return N->height;
}

// New RatelNodecreation
RatelNode* newRateNode(CarModel* key) {
  RatelNode* node= new RatelNode(key);
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

// Rotate right
RatelNode* rightRotate(RatelNode* y) {
  RatelNode* x = y->left;
  RatelNode* T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left),height(y->right)) + 1;
  x->height = max(height(x->left),height(x->right)) + 1;
  return x;
}

// Rotate left
RatelNode* leftRotate(RatelNode* x) {
  RatelNode* y = x->right;
  RatelNode* T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left),height(x->right)) + 1;
  y->height = max(height(y->left),height(y->right)) + 1;
  return y;
}

// Get the balance factor of each node
int getBalanceFactor(RatelNode* N) {
  if (N == NULL){
    return 0;
  }
  return height(N->left) - height(N->right);
}

//Find the correct postion by rate and id
RatelNode* findRateNodeByRate(RatelNode* node, int rate, int modelid, int type_id){
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
RatelNode* insertRateNode(RatelNode* node, CarModel* key) {
  // Find the correct postion and insert the node
  if (node== NULL)
    return (newRateNode(key));
  if (*(node->key)> *(key))
    node->left = insertRateNode(node->left, key);
  else if (*(key) > *(node->key))
    node->right = insertRateNode(node->right, key);
  else
    return node;

  // Update the balance factor of each RatelNodeand
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

// RatelNodewith minimum value
RatelNode* RateNodeWithMimumValue(RatelNode* node) {
  RatelNode*current = node;
  while (current->left != NULL){
    current = current->left;
  }
  return current;
}

// Delete a node
RatelNode* deleteRateNode(RatelNode* root, CarModel* key) {
  // Find the RatelNodeand delete it
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
      RatelNode* temp = root->left ? root->left : root->right;
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
      RatelNode*temp = RateNodeWithMimumValue(root->right);
      root->key = temp->key;
      root->right = deleteRateNode(root->right,temp->key);
    }
  }
  if (root == NULL){
    return root;
  }

  // Update the balance factor of each RatelNodeand
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