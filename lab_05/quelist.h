#ifndef QUELIST_H
#define QUELIST_H

#include <stdlib.h>

#define MAX_LENGTH 10000
#define QUEQUE_OVERFLOW -10;
#define QUEQUE_UNDERFLOW -11;
#define NO_MEMORY -12;

struct Node{
    double data;
    struct Node *next;
};

typedef struct{
    struct Node *head, *tail;
    int size;
}List;

void InitQueueList(List *lst);
void ClearList(List *lst);
int AddQueueList(List *lst, double value, int show, int **freed_adresses);
double PopQueueList(List *lst, int show, int **freed_adresses);


//переполнение массива T3 0..10
//T2 = T4 = 0..1
//суббота 10-12
#endif // QUELIST_H
