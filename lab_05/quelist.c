#include "quelist.h"

void InitQueueList(List *lst){

    lst -> head = lst -> tail = NULL;
    lst -> size = 0;
}

int AddQueueList(List *lst, double value, int show, int **freed_adresses){

    if(lst -> size >= MAX_LENGTH)
        return QUEQUE_OVERFLOW;

    struct Node *NewNode = (struct Node*)malloc(sizeof(struct Node));

    if(!NewNode)
        return NO_MEMORY;

    if(show){
        for(int i = 0; i < MAX_LENGTH; i++){
            if((int*)NewNode == freed_adresses[i]){
                for(int j = i; j < (MAX_LENGTH-1); j++){
                    freed_adresses[j] = freed_adresses[j+1];
                }
                freed_adresses[(MAX_LENGTH-1)] = NULL;
            }
        }
    }

    NewNode -> data = value;
    NewNode -> next = NULL;

    if(lst -> size == 0){
        lst -> head = lst -> tail = NewNode;
    }
    else{
        lst -> tail -> next = NewNode;
        lst -> tail = NewNode;
    }
    lst -> size++;

    return 0;
}

double PopQueueList(List *lst, int show, int **freed_adresses){

    if(lst -> size <= 0)
        return QUEQUE_UNDERFLOW;

    struct Node *DelNode = lst -> head;

    if(DelNode && show){ //2048
        for(int i = 0; i < MAX_LENGTH; i++){
            if(freed_adresses[i] == NULL){
                freed_adresses[i] = (int*)DelNode;
                break;
            }
        }
    }

    lst -> head = lst -> head -> next;
    lst -> size--;

    double ret_value = DelNode -> data;
    DelNode -> data = 0;
    DelNode -> next = NULL;
    free(DelNode);

    return ret_value;
}

void ClearList(List *lst){
    if(!lst)
        return;

    if(lst -> size <= 0){
        lst -> head = lst -> tail = NULL;
        lst -> size = 0;
        return;
    }

    struct Node *Curr = lst -> head;
    struct Node *Next;

    for(int i = 0; i < lst -> size - 1; i++){
        Next = Curr -> next;
        free(Curr);
        Curr = Next;
    }
    free(lst -> tail);

    lst -> head = lst -> tail = NULL;
    lst -> size = 0;
}