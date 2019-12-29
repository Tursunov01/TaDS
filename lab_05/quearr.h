#ifndef QUEARR_H
#define QUEARR_H

#include <stdlib.h>

#define MAX_LENGTH 10000
#define QUEQUE_OVERFLOW -10;
#define QUEQUE_UNDERFLOW -11;
#define NO_MEMORY -12;

typedef struct{
    double data[MAX_LENGTH];
    int size;
}QueueArray;

void InitQueueArray(QueueArray *arr);
int AddQueueArray(QueueArray  *arr, double value);
double PopQueueArray(QueueArray *arr);
void ClearQueueArray(QueueArray *arr);

#endif // QUEARR_H