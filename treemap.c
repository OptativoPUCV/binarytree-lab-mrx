#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;

struct TreeNode {
    void* key;
    void * value;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->key = key;
    new->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{
  TreeMap* map = (TreeMap*) malloc (sizeof(TreeMap));
  map->current = NULL;
  map->root = NULL;
  map->lower_than = lower_than;
  return map;
}

TreeNode* minimum(TreeNode* node)
{
  if(node->left == NULL)  return node;
  
  while(node->left != NULL) node = node->left;

  return node;
}

void insertTreeMap(TreeMap * tree, void* key, void * value)
{
  /*
  if(tree == NULL) return;

  TreeNode* aux_node = tree->root;

  while(aux_node != NULL)
  {
    if(key < aux_node->key) aux_node = aux_node->left;
    else
      if(key > aux_node->key) aux_node = aux_node->right;
      else return;    
  }

  TreeNode* new_node = createTreeNode(key, value);

  new_node->parent = aux_node;

  if(aux_node == NULL) tree->root = new_node;
  else
    if(key < aux_node->key) aux_node->left = new_node;
    else aux_node->right = new_node;
  */
}

void removeNode(TreeMap * tree, TreeNode* node) 
{
  if(node->right == NULL && node->left == NULL) node->parent = NULL;

  if(node->right != NULL && node->left == NULL)
    node->right->parent = node->parent;

  if(node->left != NULL && node->right == NULL)
    node->left->parent = node->parent;

  if(node->right != NULL && node->left != NULL)
  {
    TreeNode* min = minimum(node);
    node->key = min->key;
    node->value = min->value;
    removeNode(tree, min);
  }
  
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);
}


void * searchTreeMap(TreeMap * tree, void* key) 
{
  TreeNode* aux_node = tree->root;
  if(aux_node == NULL) return NULL;

  while(aux_node != NULL)
  {
    if(key < aux_node->key) aux_node = aux_node->left;
    else
      if(key > aux_node->key) aux_node = aux_node->right;
      else return NULL;    
  }
  
  tree->current = aux_node;
  
  return tree->current->value;
}


void * upperBound(TreeMap * tree, void* key) 
{
  TreeNode* aux_node = tree->root;
  TreeNode* higher;

  if(aux_node == NULL) return NULL;

  while(aux_node != NULL)
  {
    if(aux_node->key == key)
    {
      tree->current = aux_node;
      return aux_node->value;
    }

    if(aux_node->key >= key)
    {
      higher = aux_node;
      aux_node = aux_node->left;
    }
    else aux_node = aux_node->right;

    if(aux_node == NULL)
    {
      tree->current = higher;
      return higher->value;
    }
  }

  tree->current = aux_node;

  if(aux_node->key == key) return aux_node->value;
  else return NULL;
}

void * firstTreeMap(TreeMap * tree)
{
  TreeNode* aux_node = tree->root;
  if(aux_node == NULL) return NULL;

  while(aux_node->left != NULL) aux_node = aux_node->left;

  if(aux_node == NULL) return NULL;

  tree->current = aux_node;

  return aux_node->value;
}


void * nextTreeMap(TreeMap * tree) 
{
  if(tree->current == NULL) return NULL;

  if(tree->current->right == NULL)
  {
    void* aux_key = tree->current->key; //se guarda llave del current
    while(tree->current->key <= aux_key && tree->current->parent != NULL)
      tree->current = tree->current->parent;

    if(tree->current == tree->root && tree->current->key < aux_key) //si es el mayor
    {
      tree->current = NULL;
      return NULL;
    }    
  }
  else
  {
    tree->current = tree->current->right;
    while(tree->current->left != NULL)
      tree->current = tree->current->left; 
  }

  return tree->current->value;
}