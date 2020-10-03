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
  
  if(tree == NULL) return;

  TreeNode* aux_node = tree->root;
  TreeNode* parent = NULL;

  while(aux_node != NULL)
  {
    parent = aux_node;

    if(tree->lower_than(key, aux_node->key)) aux_node = aux_node->left;
    else
      if(tree->lower_than(aux_node->key, key))
        aux_node = aux_node->right;
      else return;    
  }

  TreeNode* new_node = createTreeNode(key, value);

  new_node->parent = parent;

  if(parent == NULL) tree->root = new_node;
  else
    if(tree->lower_than(new_node->key, parent->key))
      parent->left = new_node;
    else parent->right = new_node;

  tree->current = new_node;
  
}

void removeNode(TreeMap * tree, TreeNode* node) 
{
  if(node == NULL) return;
  
  if(node->right == NULL && node->left == NULL) //no tiene hijo
  {
    if(node == node->parent->right) node->parent->right = NULL;
    if(node == node->parent->left) node->parent->left = NULL;
    free(node);
  }

  if(node->right != NULL && node->left == NULL) //node tiene solo hijo derecho
  {
    if(node == node->parent->right)
    {
      node->parent->right = node->right;
      node->right->parent = node->parent;
    } 
    else if(node == node->parent->left)
    {
      node->parent->left = node->right;
      node->right->parent = node->parent;
    }

    node = NULL;
    free(node);
  }else if(node->left != NULL && node->right == NULL) //node tiene solo hijo izquierdo
  {
    if(node == node->parent->right)
    {
      node->parent->right = node->left;
      node->left->parent = node->parent;
    } 
    else if(node == node->parent->left)
    {
      node->parent->left = node->left;
      node->left->parent = node->parent;
    }
    
    node = NULL;
    free(node);
  }
  else if(node->right != NULL && node->left != NULL) //2 hijos
  {
    TreeNode* min;
    min = node->right;
    min = minimum(min);
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
  if(tree == NULL || tree->root == NULL) return NULL;

  TreeNode* aux_node = tree->root;

  while(aux_node != NULL)
  {
    if(tree->lower_than(aux_node->key, key))
     aux_node = aux_node->right;
    else if(tree->lower_than(key, aux_node->key))
     aux_node = aux_node->left;
    else
    {
      tree->current = aux_node;
      return tree->current->value;
    }
  }

  return NULL;
}

void * upperBound(TreeMap * tree, void* key) 
{
  if(tree->root == NULL) return NULL;

  TreeNode* higher = tree->root;

  while(tree->current != NULL)
  {
    if(tree->lower_than(tree->current->key, key))
     tree->current = tree->current->right;
    else if(tree->lower_than(key, tree->current->key))
    {
      higher = tree->current;
      tree->current = tree->current->left;
    }else return tree->current->value;
  }
  
  if(tree->current == NULL) return higher->value;
  else if(tree->current->key == key) return tree->current->value;
  else return NULL;
}

void * firstTreeMap(TreeMap * tree) 
{
  if(tree->root == NULL) return NULL;

  tree->current = minimum(tree->root);

  return tree->current->value;
}

void * nextTreeMap(TreeMap * tree) 
{
  if(tree->current == NULL || tree->root == NULL) return NULL;

  if(tree->current->right != NULL)
  {
    tree->current = minimum(tree->current->right);
    if(tree->current == NULL) return NULL;
    return tree->current->value;
  }
  else
  {
    TreeNode* aux = tree->current->parent;

    while(aux != NULL && tree->current == aux->right)
    {
      tree->current = aux;
      aux = aux->parent;
    }

    tree->current = aux;
  }
  if(tree->current == NULL) return NULL;
    
  return tree->current->value;  
}