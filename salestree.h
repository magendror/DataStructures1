#ifndef SALES_TREE
#define SALES_TREE
#include <iostream>
#include "cars.h"


class SalesNode{
  public:
  CarModel* key;
  SalesNode*left;
  SalesNode*right;
  int height;
  SalesNode(CarModel* key);
  ~SalesNode()=default;
};

SalesNode::SalesNode(CarModel* key):key(key),left(NULL),right(NULL),height(1){}

int height(SalesNode* N) {
  if (N == NULL){
    return 0;
  }
  return N->height;
}

SalesNode* newSalesNode(CarModel* key) {
  SalesNode* node= new SalesNode(key);
  return (node);
}

SalesNode* rightRotate(SalesNode* n) {
  SalesNode* temp_left = n->left;
  SalesNode* temp_right = temp_left->right;
  temp_left->right = n;
  n->left = temp_right;
  n->height = max_int(height(n->left),height(n->right)) + 1;
  temp_left->height = max_int(height(temp_left->left),height(temp_left->right)) + 1;
  return temp_left;
}

SalesNode* leftRotate(SalesNode* x) {
  SalesNode* temp_left = x->right;
  SalesNode* temp_right = temp_left->left;
  temp_left->left = x;
  x->right = temp_right;
  x->height = max_int(height(x->left),height(x->right)) + 1;
  temp_left->height = max_int(height(temp_left->left),height(temp_left->right)) + 1;
  return temp_left;
}

int getBalanceFactor(SalesNode* N) {
  if (N == NULL){
    return 0;
  }
  return height(N->left) - height(N->right);
}

SalesNode* findSalesNode(SalesNode *node, CarModel* key){
  if(node==NULL){
    return node;
  }
  if (node->key> key){
    return (findSalesNode(node->left, key));
  }
  else if (key> node->key)
  {
    return (findSalesNode(node->right, key));
  }
  else{
    return node;
  }
}

SalesNode* insertSalesNode(SalesNode* node, CarModel* key) {
  //find position and insert recursively
  if (node== NULL){
    return (newSalesNode(key));
  }
  if (*(node->key)> *(key)){
    node->left = insertSalesNode(node->left, key);
  }
  else if (*(key) > *(node->key)){
    node->right = insertSalesNode(node->right, key);
  }
  else{
    return node;
  }
  // balance the tree
  node->height = max_int(height(node->left),height(node->right)) + 1;
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    if (getBalanceFactor(node->left) >=0) {
      return rightRotate(node);
    }
    else if (getBalanceFactor(node->left) ==-1) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  if (balanceFactor < -1) {
    if (getBalanceFactor(node->right)<=0) {
      return leftRotate(node);
    }
    else if (getBalanceFactor(node->right) ==1) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  return node;
}

SalesNode* SalesNodeWithMimumValue(SalesNode*node) {
  SalesNode* current = node;
  if(current==NULL){
    return NULL;
  }
  while (current->left != NULL){
    current = current->left;
  }
  return current;
}

SalesNode* SalesNodeWithMaxValue(SalesNode*node) {
  SalesNode* current = node;
  if(current==NULL){
    return NULL;
  }
  while (current->right != NULL){
    current = current->right;
  }
  return current;
}

//find RateNode using sales as int input
SalesNode *findSalesNodeBySales(SalesNode *node, int sales, int modelid, int type_id){
  if(node==NULL){
    return node;
  }
  if (node->key->num_of_sales > sales){
    return (findSalesNodeBySales(node->left, sales,modelid, type_id));
  }
  else if (node->key->num_of_sales < sales)
  {
    return (findSalesNodeBySales(node->right, sales,modelid, type_id));
  }
  else{
    if(node->key->type_id > type_id){
      return (findSalesNodeBySales(node->right, sales,modelid, type_id));
    }
    else if (node->key->type_id < type_id){
      return (findSalesNodeBySales(node->left, sales,modelid, type_id));
    }
    else{
      if(node->key->model_id > modelid){
        return (findSalesNodeBySales(node->right, sales,modelid, type_id));
      }
      else if(node->key->model_id < modelid){
        return (findSalesNodeBySales(node->left, sales,modelid, type_id));
      }
      else
        return node;
    }
  }
}

SalesNode* deleteSalesNode(SalesNode*root, CarModel* key) {
  if (root == NULL)
    return root;
  if (*(root->key) > *(key))
    root->left = deleteSalesNode(root->left, key);
  else if (*(key) > *(root->key))
    root->right = deleteSalesNode(root->right, key);
  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      SalesNode* temp = root->left ? root->left : root->right;
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
      SalesNode* temp = SalesNodeWithMimumValue(root->right);
      root->key = temp->key;
      root->right = deleteSalesNode(root->right,temp->key);
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
    else if(getBalanceFactor(root->left) == -1) {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
  }
  if (balanceFactor < -1) {
    if (getBalanceFactor(root->right) <= 0) {
      return leftRotate(root);
    }
    else if (getBalanceFactor(root->right) == 1){
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
  }
  return root;
}
#endif