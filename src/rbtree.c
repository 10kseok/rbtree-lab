#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  p->nil = (node_t *)calloc(1, sizeof(node_t));
  if (p->nil == NULL)
  {
    free(p);
    return NULL;
  }
  p->nil->color = RBTREE_BLACK;
  p->nil->parent = p->nil->left = p->nil->right = p->nil;
  p->root = p->nil;
  return p;
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  free(t);
}

void left_rotate(rbtree *t, node_t *p)
{
  node_t *cur_node = t->root;           // cur_node = x
  node_t *node_right = cur_node->right; // node_right = y
  cur_node->right = node_right->left;
  if(node_right->left != t->nil){
    node_right->left->parent = cur_node;
  }
  node_right ->parent = cur_node ->parent;
  if(cur_node->parent == t->nil){
    t->root = node_right;
  }
  else if (cur_node == cur_node->parent->left){
    cur_node->parent->left = node_right;
  }
  else{
    cur_node->parent->right = node_right;
  }
  node_right->left = cur_node;
  cur_node->parent = node_right;

  return ;
}

void right_rotate(rbtree *t, node_t *p)
{
  node_t *cur_node = t->root;           // cur_node = x
  node_t *node_left = cur_node->left; // node_right = y
  cur_node->left = node_left->right;
  if(node_left->right != t->nil){
    node_left->right->parent = cur_node;
  }
  node_left ->parent = cur_node ->parent;
  if(cur_node->parent == t->nil){
    t->root = node_left;
  }
  else if (cur_node == cur_node->parent->right){
    cur_node->parent->right = node_left;
  }
  else{
    cur_node->parent->left = node_left;
  }
  node_left->right = cur_node;
  cur_node->parent = node_left;
  
  return ;
}

void rbtree_insert_fixup_2(rbtree *t, node_t *p) {
  while (p->parent->color == RBTREE_RED) {
    if (p->parent == p->parent->parent->left) {
      node_t *y = p->parent->parent->right;
      if (y->color == RBTREE_RED) {
        p->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        p->parent->parent->color = RBTREE_RED;
        p = p->parent->parent;
      } else {
        if (p == p->parent->right) {
          p = p->parent;
          left_rotate(t, p);
        }
        p->parent->color = RBTREE_BLACK;
        p->parent->parent->color = RBTREE_RED;
        right_rotate(t, p->parent->parent);
      }
    } else {
      node_t *y = p->parent->parent->left;
      if (y->color == RBTREE_RED) {
        p->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        p->parent->parent->color = RBTREE_RED;
        p = p->parent->parent;
      } else {
        if (p == p->parent->left) {
          p = p->parent;
          right_rotate(t, p);
        }
        p->parent->color = RBTREE_BLACK;
        p->parent->parent->color = RBTREE_RED;
        left_rotate(t, p->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  // TODO: implement insert
  // 적절한 위치 찾는 코드
  // 값 삽입
  node_t *SENTINEL_NODE = t->nil;
  node_t *parent_node = t->nil;

  node_t *new_node = malloc(sizeof(node_t));
  new_node->key = key;
  new_node->right = SENTINEL_NODE;
  new_node->left = SENTINEL_NODE;
  new_node->color = RBTREE_RED;

  node_t *cur_node = t->root;
  while (cur_node != SENTINEL_NODE)
  {
    parent_node = cur_node;
    if (cur_node->key > key)
    {
      cur_node = cur_node->left;
    }
    else
    {
      cur_node = cur_node->right;
    }
  }
  new_node->parent = parent_node;

  if (parent_node == SENTINEL_NODE)
  {
    t->root = new_node;
  } 
  else if (new_node->key < parent_node->key)
  {
    parent_node->left = new_node;
  }
  else 
  {
    parent_node->right = new_node;
  }

  rbtree_insert_fixup_2(t, new_node);
  return new_node;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  // TODO: implement find
  node_t *cur_node = t->root;
  while (cur_node != t->nil)
  {
    if (cur_node->key < key)
    {
      cur_node = cur_node->left;
    }
    else if (cur_node->key > key)
    {
      cur_node = cur_node->right;
    }
    else
    {
      return cur_node;
    }
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t)
{
  node_t *cur_node = t->root;
  while (cur_node->left != t->nil)
    cur_node = cur_node->left;

  return cur_node;
}

node_t *rbtree_max(const rbtree *t)
{
  node_t *cur_node = t->root;

  while (cur_node->right != t->nil)
    cur_node = cur_node->right;

  return cur_node;
}

int rbtree_erase(rbtree *t, node_t *p)
{
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // TODO: implement to_array
  return 0;
}

