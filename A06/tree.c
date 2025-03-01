/**
 * Name: Maryam
 * Date: 02/28/2025
 * Assignment: implement a binary search tree with insertions, searching, clearing, and printing functions
 */


#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree_node *find(const char *name, struct tree_node *root)
/**
 * searches for node with a given name in binary search tree
 * @param name: name to search for
 * @param root: root of the bst
 * @return: struct tree_node* pointer to the node that is found, or null if not
 */
{
  if (root == NULL)//if root is null, tree is empty
  {
    return NULL;
  }
  int cmp = strncmp(name, root->data.name, 64);//compare given name with current node;s name
  if (cmp == 0)//if names match, return current node
  {
    return root;
  }
  else if (cmp < 0)//if given name is smaller, search the left subtree
  {
    return find(name, root->left);//otherwise search right
  }
  else
  {
    return find(name, root->right);
  }
}

struct tree_node *insert(const char *name, struct tree_node *root)
/**
 * inserts new node with teh given name into bst
 * @param name: name to insert
 * @param root: root of the bst
 * @return struct tree_node* updated root of bst
 */
{
  if (root == NULL)//if null, insert new node here
  {
    struct tree_node *newNode = (struct tree_node *)malloc(sizeof(struct tree_node));//handle memory allocation failure
    if (!newNode)
    {
      fprintf(stderr, "Memory allocation error\n");
      exit(1);
    }
    strncpy(newNode->data.name, name, 64);//copy name into the new node
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
  }
  int cmp = strncmp(name, root->data.name, 64);//compare new name with current nodes name
  if (cmp < 0)//if new name is smaller, inser into to left subtree
  {
    root->left = insert(name, root->left);
  }
  else if (cmp > 0)//if bigger, insert to right
  {
    root->right = insert(name, root->right);
  }
  return root;//return unchanged
}

void clear(struct tree_node *root)
/**
 * recurisvely frees all nodes in the bst
 * @param root: root in bst
 */
{
  if (root != NULL)
  {
    clear(root->left);//recursively delete left subtree
    clear(root->right);//recursively delete right subtree
    free(root);//free current node
  }
}

void printHelper(struct tree_node *root, int lvl)
/**
 * helper function to print bst with indentation
 * @param root: root of bst
 * @param lvl: current level of depth of indentation
 */
{
  if (root == NULL)//base case of empty tree or end of branch
  {
    return;
  }
  if (lvl == 0) {//print root node's name with no indentation
    printf("%s\n", root->data.name);
  }

  if (root->left != NULL)//if left child exists, print it with indentation
  {
    printf("%*s l:%s\n", lvl * 2, "", root->left->data.name);
    printHelper(root->left, lvl + 1);//recursively call left subtree
  }

  if (root->right != NULL)//if right child exists, print with indentation
  {
    printf("%*s r:%s\n", lvl * 2, "", root->right->data.name);
    printHelper(root->right, lvl + 1);
  }
}

void print(struct tree_node *root)
/**
 * prints tree in strucutred format showinf left and right nodes
 * @param root: root of bst
 */
{
  printHelper(root, 0);
}

void printSorted(struct tree_node *root)
/**
 * prints bst in sorted order
 * @param root: root of the bst
 */

{
  if (root != NULL)
  {
    printSorted(root->left);//visit left subtree
    printf("%s\n", root->data.name);//print current node's name
    printSorted(root->right);//visit right subtree
  }
}
