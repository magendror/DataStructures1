#ifndef RATE_TREE
#define RATE_TREE
#include <iostream>
#include "class.h"


class ModelNode{
  public:
  CarModel key;
  ModelNode*left;
  ModelNode*right;
  int height;
  ModelNode(CarModel key);
};

// int max(int a, int b);

// Calculate height
int height(ModelNode*N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

// New ModelNodecreation
ModelNode*newNode(CarModel key) {
  ModelNode* node= new ModelNode(key);
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

// Rotate right
ModelNode*rightRotate(ModelNode*y) {
  ModelNode*x = y->left;
  ModelNode*T2 = x->right;
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
ModelNode*leftRotate(ModelNode*x) {
  ModelNode*y = x->right;
  ModelNode*T2 = y->left;
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

// Get the balance factor of each node
int getBalanceFactor(ModelNode*N) {
  if (N == NULL)
    return 0;
  return height(N->left) -
       height(N->right);
}

//Find the correct postion by rate and id
ModelNode *findNodeByRate(ModelNode *node, int rate, int modelid, int typeid ){
  if(node==NULL){
    return node;
  }
  if (node->key.rate> rate){
    return (findNodeByRate(node->left, rate,modelid, typeid));
  }
  else if (node->key.rate< rate)
  {
    return (findNodeByRate(node->right, rate,modelid, typeid));
  }
  else{
    if(node->key.type_id>typeid){
      return (findNodeByRate(node->left, rate,modelid, typeid));
    }
    else if (node->key.type_id<typeid){
      return (findNodeByRate(node->right, rate,modelid, typeid));
    }
    else{
      if(node->key.model_id>modelid){
        return (findNodeByRate(node->left, rate,modelid, typeid));
      }
      else if(node->key.model_id<modelid){
        return (findNodeByRate(node->right, rate,modelid, typeid));
      }
      else
        return node;
    }
  }
}


// Insert a node
ModelNode*insertNode(ModelNode*node, CarModel key) {
  // Find the correct postion and insert the node
  if (node== NULL)
    return (newNode(key));
  if (node->key> key)
    node->left = insertNode(node->left, key);
  else if (key > node->key)
    node->right = insertNode(node->right, key);
  else
    return node;

  // Update the balance factor of each ModelNodeand
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

// ModelNodewith minimum value
ModelNode*nodeWithMimumValue(ModelNode*node) {
  ModelNode*current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
}

// Delete a node
ModelNode*deleteNode(ModelNode*root, CarModel key) {
  // Find the ModelNodeand delete it
  if (root == NULL)
    return root;
  if (root->key > key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    if ((root->left == NULL) ||
      (root->right == NULL)) {
      ModelNode*temp = root->left ? root->left : root->right;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      ModelNode*temp = nodeWithMimumValue(root->right);
      root->key = temp->key;
      root->right = deleteNode(root->right,
                   temp->key);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each ModelNodeand
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