
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct list_node
{
    char data;
    struct list_node *next;
    struct list_node *prev;
} Node;

typedef struct linked_list
{
    Node * head;
    Node * tail;
    Node * current;
    int size;
} List;

// constructors
List * newList(char data);
Node * createNode(char data, Node * prev, Node * next);
List * createList(Node * head, Node * tail, int size);

// sub-functions
void updateListEnds(const List* list1, const List* list2);
Node * findNode(List *list, int index);
void removeNode(List *list, Node * nodeToRemove);

// iterators
Node * next(List* list);
Node * prev(List* list);
Node * start(List* list);

// accessor functions
void append(List *list, char toAppend);
void printItems(List *list);
int indexOf(List *list, char charToFind);
char getItem(List *list, int index);
int size(const List *list);
char removeAtIndex(List *list, int index);
void removeChar(List *list, char charToRemove);
void insert(List *list, int index, char charToInsert);
void setItem(List *list, int index, char charToSet);
List * split(List *list, int index);
List * merge(List *list1, List *list2);
void bubbleSort(List * list);
Node * compareNodes(List * list1, List * list2);
List * mergeSort(List * list);

#endif //LINKEDLIST_H
