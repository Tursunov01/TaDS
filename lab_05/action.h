#ifndef ACTION_H
#define ACTION_H

#include <stdio.h>
#include "quearr.h"
#include "quelist.h"
#include <stdlib.h>
#include <time.h>

void about();
int input_key(int key1, int key2);
void test_timer();
void que_a();
void que_l();
void print_res_table(double TimelineM, double untime, int f_arrived, int FirstDone,
    int s_arrived, int SecondDone, int SecondThrown, double time1, double time2, double Iter);
void print_cur_table(int FirstDone, int CurFirst, double f_average, int CurSecond, double s_average,
    double time1, double time2);

#endif // ACTION_H