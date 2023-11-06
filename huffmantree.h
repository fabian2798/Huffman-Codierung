#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

struct treeNode
{
    char data;
    int value;
    struct treeNode *left;
    struct treeNode *right;
};
typedef struct treeNode TNODE;

struct Liste_s
{
    TNODE *info;
    struct Liste_s *next;
};
typedef struct Liste_s LISTE_T;


void sortList(LISTE_T *start);
void printList(LISTE_T *root);
void swap(LISTE_T *vorgaenger, LISTE_T *nachfolger);
void createHuffmanCode(TNODE *root, int top, int arr[]);
void printArr(int arr[], int size);
void inorder_traversal(TNODE *root);
int sizeofList(LISTE_T *root);
LISTE_T *deleteElements(LISTE_T *list);
LISTE_T *createInternalNode(LISTE_T *list);
LISTE_T *insert_Node(LISTE_T *aktuellenknoten, char zeichen);

#endif