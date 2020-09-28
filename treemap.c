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

void insertTreeMap(TreeMap * tree, void* key, void * value)
{
  TreeNode* new_node = createTreeNode(key, value);
  TreeNode* aux_node = tree->root;
  TreeNode* padre = aux_node;

  if(aux_node == NULL)
  {
    tree->root = new_node;
    return;
  }

  while(aux_node != NULL)
  {
    if(aux_node->key == key) return;
    if(aux_node->key > key)
    {
      padre = aux_node;
      aux_node = aux_node->left;
    }
    else
    {
      padre = aux_node;
      aux_node = aux_node->right;
    }
  }

  if(new_node->key > padre->key)
  {
    padre->right = new_node;
    new_node->parent = padre;
  }
  else
  {
    padre->left = new_node;
    new_node->parent = padre;
  }
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
  TreeNode* aux_node = tree->root;
  if(aux_node == NULL) return NULL;

  while(aux_node->key != key)
  {
    if(aux_node->key > key)
      aux_node = aux_node->left;
    else
      aux_node = aux_node->right;
      
    if(aux_node == NULL)  return NULL;
  } 
  
  tree->current = aux_node;

  return aux_node->value;
}


void * upperBound(TreeMap * tree, void* key) {
    return NULL;
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
    if(tree->current == NULL) return NULL; //Si la posicion actual es nula retorna null
    if (tree->current->right != NULL){ // Caso si tiene hijo derecho
        tree->current = tree->current->right;
        while(tree->current->left != NULL){
            tree->current = tree->current->left;
        }
    }else{ // Caso no tiene hijo derecho
        void* llave = tree->current->key; // Se guarda la key del current
        while(tree->current->parent != NULL && tree->current->key <= llave){ //Mientras el padre exista y la llave sea menor a la llave del current
            tree->current = tree->current->parent; //current ira subiendo
        }
        if(tree->current == tree->root && tree->current->key < llave){//Caso no tiene next (es el mayor)
            tree->current = NULL;
            return NULL; 
        } 
    }
    return tree->current->value;
}
