#include <stdio.h>
#include "quearr.h"
#include "quelist.h"
#include "action.h"
#include <stdlib.h>
#include <time.h>

int main()
{
    about();


    int key = input_key(0, 3);

    switch(key){
        case 1: que_a(); break;
        case 2: que_l(); break;
        case 3: test_timer(); break;
        default: exit(0); break;
    }

    return 0;
}