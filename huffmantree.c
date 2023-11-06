#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffmantree.h"

/*erstellt huffmancode*/
void createHuffmanCode(TNODE *root, int top, int arr[])
{
    if (root->left)
    {
        arr[top] = 0;
        createHuffmanCode(root->left, top + 1, arr);
    }
    if (root->right)
    {
        arr[top] = 1;
        createHuffmanCode(root->right, top + 1, arr);
    }
    if ((root->left == NULL) && (root->right == NULL)) // leaf
    {
        if (root->data == '\n')
        {
            printf("'/n': ");
        }
        else
        {
            printf("'%c': ", root->data);
        }
        printArr(arr, top);
    }
}
/*gibt huffmancode-array aus*/
void printArr(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
    }
    printf("\n");
}
/*erstellt eine neue liste, fügt neue elemente in die liste ein und falls duplikate auftreten wird,
der wert erhöht*/
LISTE_T *insert_Node(LISTE_T *aktuellenknoten, char zeichen)
{
    LISTE_T *neuer_knoten;
    if (aktuellenknoten == NULL)
    {
        aktuellenknoten = malloc(sizeof(LISTE_T));
        if (aktuellenknoten == NULL)
        {
            printf("ERROR: Listen start");
            exit(EXIT_FAILURE);
        }
        aktuellenknoten->info = malloc(sizeof(TNODE));
        aktuellenknoten->info->data = zeichen;
        aktuellenknoten->info->value = 1;
        aktuellenknoten->info->left = NULL;
        aktuellenknoten->info->right = NULL;
        aktuellenknoten->next = NULL;
    }
    else if (aktuellenknoten->info->data == zeichen)
    {
        aktuellenknoten->info->value += 1;
        return aktuellenknoten;
    }
    else if (aktuellenknoten->next == NULL)
    {
        neuer_knoten = malloc(sizeof(LISTE_T));
        if (neuer_knoten == NULL)
        {
            printf("ERROR: Neuer Listknoten");
            exit(EXIT_FAILURE);
        }
        neuer_knoten->info = malloc(sizeof(TNODE));
        neuer_knoten->info->data = zeichen;
        neuer_knoten->info->value = 1;
        neuer_knoten->info->left = NULL;
        neuer_knoten->info->right = NULL;
        neuer_knoten->next = NULL;
        aktuellenknoten->next = neuer_knoten;
    }
    else
    {
        insert_Node(aktuellenknoten->next, zeichen);
    }
    return aktuellenknoten;
}
/*geht den baum inorder durch*/
void inorder_traversal(TNODE *root)
{
    if (root != NULL)
    {
        inorder_traversal(root->left);
        printf("%c", root->data);
        printf("%d\n", root->value);
        if ((root->left != NULL) && (root->right != NULL))
        {
            printf("left= %c,%d ", root->left->data, root->left->value);
            printf("right= %c,%d\n", root->right->data, root->right->value);
        }
        inorder_traversal(root->right);
    }
}
/*erstellt einen neuen knoten aus den ersten zwei elementen aus der liste,
der neue knoten wird das erste element in der liste*/
LISTE_T *createInternalNode(LISTE_T *list)
{
    LISTE_T *internalNode;
    internalNode = malloc(sizeof(LISTE_T));
    if (internalNode == NULL)
    {
        printf("ERROR: internalNode");
        exit(EXIT_FAILURE);
    }
    internalNode->info = malloc(sizeof(TNODE));
    internalNode->info->data = '$';                                          // symbolisierung innerer knoten
    internalNode->info->value = list->info->value + list->next->info->value; // innerer knoten hat value von den ersten zwei elementen der liste
    internalNode->info->left = list->info;                                   // zeiger auf erstes element
    internalNode->info->right = list->next->info;                            // zeiger auf zweites element
    list = deleteElements(list);                                             // erstes element gelöscht
    internalNode->next = list->next;                                         // inner knoten soll erstes element der liste sein //neuer listenknoten zeigt auf zweites element(vorher drittes)
    list = internalNode;                                                     // inner knoten soll erstes element der liste sein
    return list;
}
/*löscht das erste element aus der liste*/
LISTE_T *deleteElements(LISTE_T *list)
{
    LISTE_T *temp;
    if (list == NULL)
    {
        printf("ERROR: Liste leer(222)");
        exit(EXIT_FAILURE);
    }
    temp = list;       // liste zwischenspeichern
    list = list->next; // liste startet vom vorherigen zweiten element
    free(temp);        // speicher des ersten elements freigegeben
    return list;
}
/*bestimmt die länge der liste*/
int sizeofList(LISTE_T *root)
{
    int size = 0;
    for (; root != NULL; root = root->next)
    {
        size++;
    }
    return size;
}
/*gibt liste aus*/
void printList(LISTE_T *root)
{
    for (; root != NULL; root = root->next)
    {
        if (root->info->data == '\n')
        {
            printf("'/n':%d ", root->info->value);
        }
        else
        {
            printf("'%c':%d ", root->info->data, root->info->value);
        }
    }
    printf("\n");
}
/*sortiert liste nach aufsteigender wertigkeit*/
void sortList(LISTE_T *list) // bubblesort
{
    int swapped;
    LISTE_T *vg;        // vorgaenger
    LISTE_T *nf = NULL; // nachfolger
    if (list == NULL)
    {
        printf("ERROR: Liste leer(252)");
        exit(EXIT_FAILURE);
    }
    do
    {
        swapped = 0;
        vg = list;

        while (vg->next != nf) // läuft bis ende der liste
        {
            if (vg->info->value > vg->next->info->value) // check vorgänger mit nachfolger
            {
                swap(vg, vg->next); // variablen der knoten vertauschen
                swapped = 1;        // swap flag
            }
            vg = vg->next; // vorgaenger zeigt nun auf den nachfolger vom nachfolger
        }
        nf = vg;       // nachfolger und vorgaenger haben platz getauscht
    } while (swapped); // wenn vorgaenger mit nachfolger vertauscht wurde
}
/*tauscht vorgänger mit nachfolger*/
void swap(LISTE_T *vorgaenger, LISTE_T *nachfolger)
{
    // speicher der vorgaenger variablen
    char temp = vorgaenger->info->data;
    int tempvalue = vorgaenger->info->value;
    TNODE *vgleft = vorgaenger->info->left;
    TNODE *vgright = vorgaenger->info->right;
    // swap
    vorgaenger->info->data = nachfolger->info->data;
    vorgaenger->info->value = nachfolger->info->value;
    vorgaenger->info->left = nachfolger->info->left;
    vorgaenger->info->right = nachfolger->info->right;
    nachfolger->info->data = temp;
    nachfolger->info->value = tempvalue;
    nachfolger->info->left = vgleft;
    nachfolger->info->right = vgright;
}