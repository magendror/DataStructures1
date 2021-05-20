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
  ~RateNode()=default;
};

RateNode::RateNode(CarModel* key):key(key),left(NULL),right(NULL),height(1){}

int height(RateNode*N) {
  if (N == NULL)
    return 0;
  return N->height;
}

RateNode* newRateNode(CarModel* key) {
  RateNode* node= new RateNode(key);
  return (node);
}

RateNode* rightRotate(RateNode* n) {
  RateNode* temp_left = n->left;
  RateNode* temp_right = temp_left->right;
  temp_left->right = n;
  n->left = temp_right;
  n->height = max_int(height(n->left),height(n->right)) + 1;
  temp_left->height = max_int(height(temp_left->left),height(temp_left->right)) + 1;
  return temp_left;
}

RateNode* leftRotate(RateNode* x) {
  RateNode* temp_left = x->right;
  RateNode* temp_right = temp_left->left;
  temp_left->left = x;
  x->right = temp_right;
  x->height = max_int(height(x->left),height(x->right)) + 1;
  temp_left->height = max_int(height(temp_left->left),height(temp_left->right)) + 1;
  return temp_left;
}

int getBalanceFactor(RateNode* N) {
  if (N == NULL){
    return 0;
  }
  return height(N->left) - height(N->right);
}

//find RateNode using rate as int input
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


RateNode* insertRateNode(RateNode* node, CarModel* key) {
  //find position and insert recursively
  if (node== NULL){
    return (newRateNode(key));
  }
  if (*(node->key)> *(key)){
    node->left = insertRateNode(node->left, key);
  }
  else if (*(key) > *(node->key)){
    node->right = insertRateNode(node->right, key);
  }
  // balance the tree
  node->height = max_int(height(node->left),height(node->right)) + 1;
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
    if (getBalanceFactor(node->right) <=0) {
      return leftRotate(node);
    }
    else if (getBalanceFactor(node->right) ==1) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  return node;
}

RateNode* RateNodeWithMimumValue(RateNode* node) {
  RateNode*current = node;
  if(current==NULL){
    return current;
  }
  while (current->left != NULL){
    current = current->left;
  }
  return current;
}

RateNode* deleteRateNode(RateNode* root, CarModel* key) {
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
      delete temp;
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
  // balance the tree
  root->height = max_int(height(root->left),height(root->right)) + 1;
  int balanceFactor = getBalanceFactor(root);
  if (balanceFactor > 1) {
    if (getBalanceFactor(root->left) >= 0) {
      return rightRotate(root);
    }
    else if (getBalanceFactor(root->left) == -1){
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