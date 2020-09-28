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

TreeNode* minimum(TreeNode* node){
  return NULL;
}

void insertTreeMap(TreeMap * tree, void* key, void * value) {

}

void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




void * searchTreeMap(TreeMap * tree, void* key) 
{
  /*
  TreeNode* aux_node = tree->root;
  if(aux_node == NULL) return NULL;

  int validador;

  while(is_equal(aux_node->key, key) == 0)
  {
    validador = lower_than(aux_node->key, key);
    if(validador == 0);
  }
  */
  return NULL;
}


void * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

void * firstTreeMap(TreeMap * tree) {
    return NULL;
}

void * nextTreeMap(TreeMap * tree) {
    return NULL;
}
