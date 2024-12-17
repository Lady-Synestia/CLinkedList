#include <stdio.h>
#include "linkedlist.h"



int main(int argc, char * const argv[])
{
    const char word[] = "Feral";
    printf("Hello %s!\n", word);
    // return 0;

    List *list = newList('A');

    {
        // appending to list
        append(list, 'G');
        append(list, 'E');
        append(list, 'C');
        append(list, 'H');
        append(list, 'D');
        append(list, 'B');
        append(list, 'E');
        append(list, 'H');

        printItems(list);
    }
    {
        // index of character
        const char chr = 'A';
        printf("index of %c: %d\n", chr, indexOf(list, chr));
    }
    {
        // find item at an index
        const int index = 4;
        const char chr = getItem(list, index);
        printf(" char at index %i: %c\n", index, chr);
    }
    {
        // length of list
        printf("length: %d\n", size(list));
    }
    {
        // remove at an index
        const int index = 0;
        printf("removed %c from index %d\n", removeAtIndex(list, index), index);
        printItems(list);
    }
    {
        // remove all of one item
        const char chr = 'E';
        removeChar(list, chr);
        printf("removed all instances of %c\n", chr);
        printItems(list);
    }
    {
        // insert an item in the middle of the list
        const char chr = 'F';
        const int index = 1;
        insert(list, index, chr);
        printf("Inserted %c at index %d\n", chr, index);
        printItems(list);
    }
    {
        // split the list after an index
        const int index = 4;
        List *newList = split(list, index);
        printf("Split after index %d\n", index);
        printItems(list);
        printItems(newList);

        // merge two lists
        list = merge(list, newList);
        printf("merged lists\n");
        printItems(list);
    }
    /*{
        // sort the list
        printf("bubble sorting\n");
        bubbleSort(list);
        printf("bubble sorted\n");
        printItems(list);
    }*/
    {
        printf("merge sorting\n");
        list = mergeSort(list);
        printf("merge sorted\n");
        printItems(list);
    }

    return 0;
}

