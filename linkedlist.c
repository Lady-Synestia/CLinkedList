#include "linkedlist.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


Node * createNode(const char data, Node * prev, Node * next)
{
    Node * node = malloc(sizeof(Node));
    // allows setting next and prev to self
    node->next = next == NULL ? node : next;
    node->prev = prev == NULL ? node : prev;
    node->data = data;
    return node;
}

List * newList(const char data)
{
    // allocate memory for the head node
    Node * head = createNode(data, NULL, NULL);
    // list starts with 1 item
    List * list = createList(head, head, 1);
    return list;
}

List * createList(Node * head, Node * tail, const int size)
{
    List * list = malloc(sizeof(List));

    list->head = head;
    list->head->prev = tail;

    list->tail = tail;
    list->tail->next = head;

    list->current = head;
    list->size = size;
    return list;
}

void updateListEnds(const List * list1, const List * list2)
{
    list1->tail->next = list2->head;
    list1->head->prev = list2->tail;
}

void removeNode(List *list, Node * nodeToRemove)
{
    // if necessary updating head/ tail
    if (nodeToRemove == list->head)
    {
        list->head = nodeToRemove->next;
    }
    else if (nodeToRemove == list->tail)
    {
        list->tail = nodeToRemove->prev;
    }
    // pointing around remove node
    nodeToRemove->prev->next = nodeToRemove->next;
    nodeToRemove->next->prev = nodeToRemove->prev;

    // free memory
    free(nodeToRemove);
    list->size--;
}

Node * start(List * list)
{
    list->current = list->head;
    return list->current;
}

Node * next(List * list)
{
    list->current = list->current->next;
    return list->current;
}

Node * prev(List * list)
{
    list->current = list->current->prev;
    return list->current;
}

Node * findNode(List *list, const int index)
{
    start(list);
    for (int i = 0; i < index; i++)
    {
        next(list);
    }
    return list->current;
}

void append(List *list, const char toAppend)
{
    Node * newNode = createNode(toAppend, list->tail, list->head);
    // updating tail node
    list->tail->next = newNode;
    list->tail = newNode;
    // updating head node
    list->head->prev = newNode;
    list->size++;

}

void printItems(List *list)
{
    printf("| %c", start(list)->data);
    for (int i = 0; i < list->size - 1; i++)
    {
        printf(" -> %c", next(list)->data);
    };
    printf(" |\n");
}

int indexOf(List *list, const char charToFind)
{
    start(list);
    int index = 0;
    do
    {
        if (list->current->data == charToFind)
        {
            return index;
        }
        index++;
    }
    while (next(list) != list->head);
    // if char isn't found
    return -1;
}

char getItem(List *list, const int index)
{
    return findNode(list, index)->data;
}

int size(const List *list)
{
    return list->size;
}

char removeAtIndex(List * list, const int index)
{
    Node * n = findNode(list, index);
    const char data = n->data;
    removeNode(list, n);
    return data;
}

void removeChar(List * list, const char charToRemove)
{
    start(list);
    do
    {
        if (list->current->data == charToRemove)
        {
            Node * n = list->current;
            next(list);
            removeNode(list, n);
        } else
        {
            next(list);
        }
    } while (list->current != list->tail);
}

void insert(List * list, const int index, const char charToInsert)
{
    Node * n = findNode(list, index);
    Node * newNode = createNode(charToInsert, n->prev, n);

    n->prev->next = newNode;
    n->prev = newNode;

    if (index == 0)
    {
        list->head = newNode;
    }
    list->size++;
}

List * split(List * list, const int index)
{
    Node * n = findNode(list, index);
    Node * newTail = n->prev;
    List * newList = createList(n, list->tail, list->size - index);
    list->tail = newTail;
    list->size = index;


    // updating nodes
    updateListEnds(newList, newList);
    updateListEnds(list, list);

    return newList;
}

List * merge(List * list1, List * list2)
{

    updateListEnds(list1, list2);
    updateListEnds(list2, list1);

    list1->tail = list2->tail;
    free(list2);
    list1->size += list2->size;
    return list1;
}

void bubbleSort(List * list)
{
    bool swaps;
    do
    {
        printItems(list);
        start(list);
        swaps = false;
        do
        {
            if (list->current->data > list->current->next->data)
            {
                const char temp = list->current->data;
                list->current->data = list->current->next->data;
                list->current->next->data = temp;
                swaps = true;
            }
        } while (next(list) != list->tail);
    } while (swaps);
}

Node * compareNodes(List * list1, List * list2)
{
    Node * node;
    if (list1->head->data < list2->head->data)
    {
        node = list1->current;
        removeNode(list1, list1->head);
    }
    else
    {
        node = list2->current;
        removeNode(list2, list2->head);
    }
    return node;
}

List * mergeSort(List * list)
{

    List * list1;
    List * list2;
    // dividing
    if (list->size > 1)
    {
        printf("splitting\n");
        printItems(list);
        list1 = mergeSort(split(list, size(list)/2));
        list2 = mergeSort(list);
    } else
    {
        return list;
    }
    //merging
    printf("merging\n");
    printItems(list1);
    printItems(list2);
    start(list1);
    int index = 0;
    do
    {
        if (list1->current->data > list2->head->data)
        {
            insert(list1, index, list2->head->data);
            removeNode(list2, list2->head);
        }else
        {
            next(list1);
        }
        index++;
    } while (list2->size > 0 && list1->current != list1->head);
    if (list2->size > 0)
    {
        merge(list1, list2);
    }
    printItems(list1);

    return list1;
}