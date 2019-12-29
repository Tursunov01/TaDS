#include "quearr.h"

void InitQueueArray(QueueArray *arr){
    for(int i = 0; i < MAX_LENGTH; i++){
        arr -> data[i] = 0;
    }
    arr -> size = 0;
}

int AddQueueArray(QueueArray *arr, double value){
   if(arr -> size >= MAX_LENGTH){
        return QUEQUE_OVERFLOW;
   }
   else{
        arr -> data[arr -> size] = value;
        arr -> size++;
        return 0;
   }
}

double PopQueueArray(QueueArray *arr){
    if(arr -> size <= 0){
        return QUEQUE_UNDERFLOW;
    }
    else{
        double ret_value = arr -> data[0];
        for(int i = 0; i < (arr -> size - 1); i++){
            arr -> data[i] = arr -> data[i+1];
        }
        arr -> size--;
        arr -> data[arr -> size] = 0;
        return ret_value;
    }
}

void ClearQueueArray(QueueArray *arr){
    if(!arr) return;
    arr -> size = 0;
}