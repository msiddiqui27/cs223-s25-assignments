/**
 * name: Maryam
 * date: 02/28/2025
 * assignment:program that builds a binary search tree of a given set of files. After building the tree, the program should give the user a prompt where they can list the processed files in alphabetical order and then query the dependencies of the file by giving the filename.
 */

#include <stdio.h>
#include "tree.h"
#include <stdlib.h>
#include <string.h>

struct DependencyNode
{
  /**
   * Struct DependancyNode: stores linked list of dependencies
   */
  char name[128];
  struct DependencyNode *next;
};

struct FileN
{
  /**
   * struct FileNode: stores a filename and its dependencies
   */
  char filename[128];//filname stored in tree
  struct DependencyNode *dependencies;//list of dependencies for the file
  struct FileN *left;//pointers to left and right nodes
  struct FileN *right;
};

struct FileN *insertFile(struct FileN *root, const char *filename){

  /**
   * inserts filename into the binary search tree (BST)
   * @param root: root of the bst
   * @param filename: filename to be inserted
   * @return struct FileN: updated root of bst
   */
  if (root == NULL)
  {
    struct FileN *newNode = (struct FileN *)malloc(sizeof(struct FileN));
    if (!newNode)
    {
      fprintf(stderr, "Memory Allocation error\n");
      exit(1);
    }
    strncpy(newNode->filename, filename, 128);
    newNode->dependencies = NULL;
    newNode->left = newNode->right = NULL;
    return newNode;
  }

  int cmp = strcmp(filename, root->filename);
  if (cmp < 0)
  {
    root->left = insertFile(root->left, filename);
  }
  else if (cmp > 0)
  {
    root->right = insertFile(root->right, filename);
  }
  return root;
}

struct FileN *findFile(struct FileN *root, const char *filename)
/**
 * inserts filename into binary search tree
 * @param root: root of BST
 * @param filename: filaname to be inserted
 * @return struct FileN*: updated root of the bst
 */

{
  if (root == NULL)
    return NULL;

  int cmp = strcmp(filename, root->filename);
  if (cmp == 0)
    return root;
  else if (cmp < 0)
    return findFile(root->left, filename);
  else
    return findFile(root->right, filename);
}
void printDependencies(struct FileN *node)
{
  if (node == NULL)
    return;

  printf("%s has the following dependencies:\n", node->filename);
  struct DependencyNode *dep = node->dependencies;

  if (!dep)
  {
    printf("  (None)\n");
  }
  else
  {
    while (dep)
    {
      printf("  %s\n", dep->name);
      dep = dep->next;
    }
  }
}

void printSortedd(struct FileN *root)
/**
 * recursively print filenames in sorted order
 */
{
  if (root == NULL)
  {
    return;
  }
  printSortedd(root->left);
  printf("%s\n", root->filename);
  printSortedd(root->right);
}
void processCommands(struct FileN *root)
/**
 * handles user input commands like "list"
 */
{
  char command[256];
  while (1)//infinite loop
  {
    if (!fgets(command, sizeof(command), stdin))
    {
      break;
    }
    command[strcspn(command, "\n")] = 0;//remove new line character

    if (strcmp(command, "quit") == 0)//exit program
    {
      break;
    }
    else if (strcmp(command, "list") == 0)//list all files in sorted order
    {
      printSortedd(root);
    }
    else
    {
      struct FileN *node = findFile(root, command);
      if (node)
      {
        printDependencies(node);//print file dependencies
      }
      else
      {
        printf("%s not found\n", command);
      }
    }
  }
}
void extraDep(const char *line)
/**
 * extracts the dependency name from a '#include" line
 * @param line: a line of text from the file
 */
{
  char buffer[256];
  strncpy(buffer, line, sizeof(buffer) - 1);
  buffer[sizeof(buffer) - 1] = '\0';
  char *token = strtok(buffer, "\"<>");//extract filename from #include line
  if (token && strstr(line, "#include"))
  {
    printf("Extracted: %s\n", token);
  }
}

void extractD(struct FileN *node)
/**
 * parses file to find the dependencies
 * @param node: file node whose dependencies should be extracted
 */
{
  FILE *file = fopen(node->filename, "r");
  if (!file)
    return;

  char buffer[256];
  while (fgets(buffer, sizeof(buffer), file))
  {
    if (strstr(buffer, "#include"))//check if line contains #include
    {
      char depName[128];

      char *token = strtok(buffer, "\"<>");
      if (token)
      {
        strncpy(depName, token, 128);

        struct DependencyNode *newDep = (struct DependencyNode *)malloc(sizeof(struct DependencyNode));//create new dependency node and add it to list
        strncpy(newDep->name, depName, 128);
        newDep->next = node->dependencies;
        node->dependencies = newDep;
      }
    }
  }
  fclose(file);
}
int main(int argc, char *argv[])
/**
 * main function that processes files, builds binary search tree, and starts the command
 * @param argc:number of command-line arguments
 * @param argv: list of command-line arguments
 * @return exit
 */
{
  if (argc < 2)
  {
    printf("Usage: ./dependency <files>\n");
    return EXIT_FAILURE;
  }
  struct FileN *root = NULL;
  printf("Processing %d files:\n", argc - 1);
  for (int i = 1; i < argc; i++)//read each filename from command-line arguments and insert into binary search tree
  {
    printf("Checking file: %s\n", argv[i]);

    FILE *file = fopen(argv[i], "r");
    if (file)
    {
      fclose(file);
      printf("Adding: %s\n", argv[i]);
      root = insertFile(root, argv[i]);//insert file into bst
    }
    else
    {
      printf("%s file not found\n", argv[i]);
    }
  }
  processCommands(root);//prcoessing the loop
  return 0;
}
