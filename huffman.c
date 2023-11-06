#define MAX 255
#include <stdio.h>  /* standard from c */
#include <stdlib.h> /*constants like EXIT_SUCCESS or EXIT_FAILURE*/
#include <unistd.h> /* for arguments (getopt), R_OK */
#include <string.h> /*strcpy*/
#include "huffmantree.h"

void usage();

int main(int argc, char **argv)
{
     LISTE_T *list;
    char z;
    FILE *fp;
    char filename[MAX] = "";
    int cflag = 0;
    int option;
    while ((option = getopt(argc, argv, "ch")) != -1)
    {
        switch (option)
        {
        case 'h':
            usage();
            break;
        case 'c':
            cflag = 1;
            break;
        case '?':
            usage();
            break;
        default:
            usage();
            break;
        }
    }
    if (optind < argc)
    {
        strncpy(filename, argv[optind], MAX);
    }
    if (strlen(filename) != 0)
    {
        if (access(filename, R_OK) == EXIT_SUCCESS) // check ob das file readable ist und beim returnwert kein fehler auftritt (EXIT_SUCCESS = 0)
        {
            fp = fopen(filename, "r");
        }
        else
        {
            printf("ERROR: Lesbarkeit\n");
            exit(EXIT_FAILURE);
        }
    }
    if (cflag == 1)
    {
        list = NULL;
        int codeArr[MAX];
        int sizelist = 0;
        int top = 0;
        while ((z = fgetc(fp)) && !feof(fp))
        {
            list = insert_Node(list, z);
        }
        sizelist = sizeofList(list);
        printf("Hier eine Übersicht der Häufigkeiten der einzelnen Buchstaben:\n\n");
        printf("-----------------------------------------------------------------------------------\n");
        printList(list); // check list
        printf("-----------------------------------------------------------------------------------\n");
        while (sizelist > 1)
        {
            sortList(list); // list aufsteigend sortiert
            // printList(list); // check list
            list = createInternalNode(list); // zwei elemente der liste zusammengefügt und an die erste stelle der liste gehangen
            // printList(list); // check list
            sizelist = sizeofList(list); // sizelist - 1
        }
        printf("\nDer aus den Häufigkeiten entstandene Huffmanncode:\n\n");
        createHuffmanCode(list->info, top, codeArr);
    }
    free(list);
    return 0;
}
void usage()
{
    printf("Usage : ./myprog [-c] [-h] inputfile\n");
    exit(EXIT_FAILURE);
}
