#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct LinkedList LinkedList;

struct Node{
    char* str;
    Node* next;
    Node* prev;
};

struct LinkedList{
    Node* head;
    Node* tail;
};

void push_to_list(LinkedList* list, char* str){
    Node* newElem = malloc(sizeof(Node));
    if (list->head == NULL){
        list->head = newElem;
    }

    newElem->prev = list->tail;
    newElem->next = NULL;
    newElem->str = malloc(strlen(str)+1);
    if (list->tail != NULL){
        list->tail->next = newElem;
    }
    list->tail = newElem;
    strcpy (newElem->str, str);
}

int main() {
    char stroka[100];
    fgets(stroka, 100, stdin);
    LinkedList lst;
    lst.head = NULL;
    lst.tail = NULL;
    while (stroka[0] != '.'){
        push_to_list(&lst, stroka);
        fgets(stroka, 100, stdin);
    }
    Node* node = lst.head;
    while (node != NULL){
        printf("%s", node->str);
        node = node->next;
        if (node != NULL && node->prev != NULL){
            free(node->prev->str);
            free(node->prev);
        }
    }
    return 0;
}
