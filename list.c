#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

typedef struct List{
    Node * head;
    Node * tail;
    Node * current;
} List;

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* list = (List*) malloc(sizeof(List));
    if (!list) return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
     return list;
}

void * firstList(List * list) {
    if (!list->head) return NULL;
    list->current = list->head;
    return list->head->data;
}

void * nextList(List * list) {
    if (!list->current || !list->current->next) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if (!list->tail) return NULL;
    list->current = list->tail;
    return list->tail->data;
}

void * prevList(List * list) {
    if (!list->current || !list->current->prev) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* newNode = createNode(data);
    if (!newNode) return;

    newNode->next = list->head;
    if (list->head) list->head->prev = newNode;
    list->head = newNode;
    if (!list->tail) list->tail = newNode;
    if (!list->current) list->current = newNode;
}


void pushBack(List * list, void * data) {
    if (!list->head) {
        pushFront(list, data);
        return;
    }
    Node* newNode = createNode(data);
    if (!newNode) return;

    newNode->prev = list->tail;
    list->tail->next = newNode;
    list->tail = newNode;
}


void pushCurrent(List * list, void * data) {
    if (!list->current) return;
    Node* newNode = createNode(data);
    if (!newNode) return;

    newNode->next = list->current->next;
    newNode->prev = list->current;

    if (list->current->next) list->current->next->prev = newNode;
    list->current->next = newNode;

    if (list->current == list->tail) list->tail = newNode;

    list->current = newNode;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    if (!list->tail) return NULL;
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (!list->current) return NULL;
    Node* aux = list->current;
    void* data = aux->data;

    if (aux->prev) aux->prev->next = aux->next;
    else list->head = aux->next;

    if (aux->next) aux->next->prev = aux->prev;
    else list->tail = aux->prev;

    list->current = aux->next;
    free(aux);
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        free(popFront(list));
    }
    free(list);
}
