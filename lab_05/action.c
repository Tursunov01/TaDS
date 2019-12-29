#include "action.h"
#include <math.h>

int func();

void about(){
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
           "----------------------------",
           "Check type of queque:",
           "1 - Array",
           "2 - List",
           "3 - Time",
           "0 - Exit",
           "----------------------------");
}

void test_timer(){
    srand(time(NULL));

    time_t time_array, time_list;
    QueueArray TestArray;
    List TestList;
    int **buf = NULL;
    InitQueueArray((QueueArray*)&TestArray);
    InitQueueList(&TestList);
    printf("----------------------------\n");
    printf("Time at clocks: \n");

    time_array = clock();
    for(int i = 0; i < MAX_LENGTH; i++)
        AddQueueArray((QueueArray*)&TestArray,1);
    time_array = clock() - time_array;
    printf("Array(Add elements): %ld\n", time_array);

    time_array = clock();
    for(int i = 0; i < MAX_LENGTH; i++)
        PopQueueArray((QueueArray*)&TestArray);
    time_array = clock() - time_array;
    printf("Array(Pop elements): %ld\n", time_array);

    time_list = clock();
    for(int i = 0; i < MAX_LENGTH; i++)
        AddQueueList(&TestList, 1, 0, buf);
    time_list = clock() - time_list;
    printf("List(Add elements): %ld\n", time_list);

    time_list = clock();
    for(int i = 0; i < MAX_LENGTH; i++)
        PopQueueList(&TestList, 0, buf);
    time_list = clock() - time_list;
    printf("List(Pop elements): %ld\n", time_list);


 /*   printf("----------------------------\n");
    printf("Time at clocks: \n");
    printf("Array: %ld\n", time_array);
    printf("List: %ld\n", time_list);*/
}

void print_res_table(double TimelineM, double untime, int f_arrived, int FirstDone,
int s_arrived, int SecondDone, int SecondThrown, double time1, double time2, double Iter){
    printf("\n--------------------------------------------------\n");
    printf("result\n");
    printf("--------------------------------------------------\n");
    printf(" 1) Time in work: %2.1lf\n", TimelineM);
    printf(" 2) Time not work: %2.1lf\n", untime);
    printf(" 3) Amount T1 elements(all) go: %d\n", f_arrived);
    printf(" 4) Amount T1 elements(only) go: %d\n", FirstDone);
    printf(" 5) Amount T2 elements(all) go: %d\n", s_arrived);
    printf(" 6) Amount T2 elements(only) go: %d\n", SecondDone);
    printf(" 7) Amount T2 elements(go out): %d\n", SecondThrown);
    printf(" 8) Average time Type1 queue: %2.1f\n", time1);
    printf(" 9) Average time Type2 queue: %2.1f\n", time2);
  //  printf("10) Time Apparatus Work: %lf\n", Iter);
    printf("10) Time Apparatus Work: %lf\n", TimelineM-untime);
    printf("11) Percent: %lf%%", Iter);
}

void print_cur_table(int FirstDone, int CurFirst, double f_average, int CurSecond, double s_average,
                     double time1, double time2){
   // printf("\n--------------------------------------------------\n");
    printf("\nFor: %d\n", FirstDone);
  //  printf("--------------------------------------------------\n");
    printf("Tekushiy Len (1) queue: %d\n", CurFirst);
    printf("Average Len (1) queue: %2.1lf\n", f_average);
    printf("Tekushiy Len (2) queue: %d\n", CurSecond);
    printf("Average Len (2) queue: %2.1lf\n", s_average);
    printf("Average time Type1 queue: %2.1f\n", time1);
    printf("Average time Type2 queue: %2.1f\n", time2);
}

void que_l(){
    srand(time(NULL));

    double TimelineFirst = 0, TimelineSecond = 0, TimelineM = 0, UnTime = 0;
    FILE *f;

    //srand(time(NULL));
    double FirstMin = 1;
    double RangeFirst = 5;

    double MinWorkFirst = 0;
    double RangeWorkFirst = 4;

    double SecondMin = 0;
    double RangeSecond = 3;

    double MinWorkSecond = 0;
    double RangeWorkSecond = 1;

    int have = 0;
    printf("-------------------------------\n");
    printf("Would you have reverse you TIME?\n1 - Yes\n0 - No\n>>");
    have = input_key(0, 1);
    if (have == 1){
        printf("Input T1(Queue): From and to: ");
        scanf("%lf%lf", &FirstMin, &RangeFirst);
        printf("\nInput T2(Queue): From and to: ");
        scanf("%lf%lf", &SecondMin, &RangeSecond);
        printf("\nInput T3(Work): From and to: ");
        scanf("%lf%lf", &MinWorkFirst, &RangeWorkFirst);
        printf("\nInput T4(Work): From and to: ");
        scanf("%lf%lf", &MinWorkSecond, &RangeWorkSecond);
        printf("-------------------------------\n");
    }

    int FirstDone = 0, SecondDone = 0, SecondThrown = 0;

    List FirstQueque, SecondQueque;
    InitQueueList(&FirstQueque);
    InitQueueList(&SecondQueque);

    double FirstIn, FirstWork, SecondIn, SecondWork;
    double Tiq1 = 0, Tiq2 = 0;
    int CurFirst = 0, CurFirstSum = 0, Iter = 0;;
    int CurSecond = 0, CurSecondSum = 0, WorkinSecond = 0;
    int *FreeAdFirst[2048] = {NULL}, *FreeAdSecond[2048] = {NULL};

    int show = 0;
    printf("Do you want to see addresses?\n1 - Yes;\n0 - No\n");
    show = input_key(0, 1);

    f = fopen("Free.txt", "w");
    while(FirstDone < 1000){

        Iter++;
        //2000 заявок 2го типа 1000 заявок 1 типа за 3000

        while((TimelineM > TimelineFirst) || (FirstQueque.size == 0)){
            FirstIn = FirstMin + (RangeFirst-FirstMin)*((double)rand()/(double)RAND_MAX);
            TimelineFirst += FirstIn;
            AddQueueList(&FirstQueque, TimelineFirst, show, FreeAdFirst);
        }

        while((TimelineM > TimelineSecond) || (SecondQueque.size == 0)){
            SecondIn = SecondMin + (RangeSecond-SecondMin)*((double)rand()/(double)RAND_MAX);
            TimelineSecond += SecondIn;
            AddQueueList(&SecondQueque, TimelineSecond, show, FreeAdSecond);
        }

        CurFirst = FirstQueque.size;
        CurSecond = SecondQueque.size;
        CurFirstSum += CurFirst;
        CurSecondSum += CurSecond;

        if((FirstQueque.head -> data <= TimelineM) || (FirstQueque.head -> data <= SecondQueque.head -> data)){

            if(FirstQueque.head -> data > TimelineM){
                UnTime += FirstQueque.head -> data - TimelineM;
                TimelineM += UnTime;
            }

            FirstWork = MinWorkFirst + (RangeWorkFirst-MinWorkFirst)*((double)rand()/(double)RAND_MAX);
            TimelineM += FirstWork;
            Tiq1 += TimelineM - PopQueueList(&FirstQueque, show, FreeAdFirst);
            FirstDone++;

            if (CurFirst >= MAX_LENGTH || CurSecond >= MAX_LENGTH){
                printf("\nOVERFLOW!");
                print_res_table(TimelineM, UnTime, FirstDone + FirstQueque.size, FirstDone,
                SecondDone + SecondQueque.size, SecondDone, SecondThrown, Tiq1/FirstDone, Tiq2/WorkinSecond, fabs(100*(TimelineM-FirstDone*(FirstMin+RangeFirst)/2)/(FirstDone*(FirstMin+RangeFirst)/2)));
                return;
            }

            if(FirstDone % 100 == 0){
                print_cur_table(FirstDone, CurFirst-1, (CurFirstSum-1)/(double)Iter, CurSecond,
                         CurSecondSum/(double)Iter, Tiq1/FirstDone,Tiq2/ (SecondDone + SecondThrown));

                int in_row = 10;
                int counter = 0;

                if(show){
                    //fprintf(f, "--------------------------------------------------\n");
                    //fprintf(f, "Free addresses:\n");
                    fprintf(f, "--------------------------------------------------\n");
                    fprintf(f, "                     %d\n", FirstDone);
                   // fprintf(f, "--------------------------------------------------\n");
                    fprintf(f, "Queque (1):\n");
                    for(int i = 0; i < 2048; i++){
                        if(FreeAdFirst[i] != NULL){
                            fprintf(f, "%p ", FreeAdFirst[i]);
                            counter++;
                            if(counter % in_row == 0){
                                fprintf(f, "\n");
                            }
                        }
                    }

                    counter = 0;

                    fprintf(f, "\n--------------------------------------------------\n");
                    fprintf(f, "Queque (2):\n");
                    for(int i = 0; i < 2048; i++){
                        if(FreeAdSecond[i] != NULL){
                            fprintf(f, "%p ", FreeAdSecond[i]);
                            counter++;
                            if(counter % in_row == 0){
                                fprintf(f, "\n");
                            }
                        }
                    }
                    fprintf(f, "\n\n\n");
                }
            }
        }
        else{
            WorkinSecond++;
            SecondWork = MinWorkSecond + (RangeWorkSecond-MinWorkSecond)*((double)rand()/(double)RAND_MAX);

            if(SecondQueque.head -> data > TimelineM){
                UnTime += SecondQueque.head -> data - TimelineM;
                TimelineM += UnTime;
            }

            if(FirstQueque.head -> data >= TimelineM + SecondWork){
                TimelineM += SecondWork;
                Tiq2 += TimelineM - PopQueueList(&SecondQueque, show, FreeAdSecond);
                SecondDone++;
            }
            else{
                Tiq2 += TimelineM - PopQueueList(&SecondQueque, show, FreeAdSecond);
                TimelineM = FirstQueque.head -> data;
                SecondThrown++;
               // FirstDone++;
                AddQueueList(&SecondQueque, TimelineM, show, FreeAdFirst);
            }
        }
    }

    fclose(f);
    print_res_table(TimelineM, UnTime, FirstDone + FirstQueque.size, FirstDone,
    SecondDone + SecondQueque.size, SecondDone, SecondThrown, Tiq1/FirstDone, Tiq2/WorkinSecond, fabs(100*(TimelineM-FirstDone*(FirstMin+RangeFirst)/2)/(FirstDone*(FirstMin+RangeFirst)/2)));
    ClearList(&FirstQueque);
    ClearList(&SecondQueque);
}

void que_a(){
    srand(time(NULL));
    int ll = 0;

    double FirstMin = 1;
    double RangeFirst = 5;

    double MinWorkFirst = 0;
    double RangeWorkFirst = 4;

    double SecondMin = 0;
    double RangeSecond = 3;

    double MinWorkSecond = 0;
    double RangeWorkSecond = 1;

    int FirstDone = 0, SecondDone = 0, SecondThrown = 0;
    double TimelineFirst = 0, TimelineSecond = 0, TimelineM = 0, UnTime = 0;

    QueueArray FirstQueque, SecondQueque;
    InitQueueArray(&FirstQueque);
    InitQueueArray(&SecondQueque);

    double FirstIn = 0, FirstWork = 0, SecondIn = 0, SecondWork = 0;
    double Tiq1 = 0, Tiq2 = 0;
    int CurFirst = 0, CurSecond = 0, Iter = 0;
    int CurFirstSum = 0, CurSecondSum = 0, WorkinSecond = 0;

    int have = 0;
    printf("-------------------------------\n");
    printf("Would you have reverse you TIME?\n1 - Yes\n0 - No\n>>");
    have = input_key(0, 1);
    if (have == 1){
        printf("Input T1(Queue): From and to: ");
        scanf("%lf%lf", &FirstMin, &RangeFirst);
        printf("\nInput T2(Queue): From and to: ");
        scanf("%lf%lf", &SecondMin, &RangeSecond);
        printf("\nInput T3(Work): From and to: ");
        scanf("%lf%lf", &MinWorkFirst, &RangeWorkFirst);
        printf("\nInput T4(Work): From and to: ");
        scanf("%lf%lf", &MinWorkSecond, &RangeWorkSecond);
        printf("-------------------------------\n");
    }

    while(FirstDone < 1000){
        Iter++;
        //ONE
        while((TimelineM > TimelineFirst) || (FirstQueque.size == 0)){
            FirstIn = FirstMin + (RangeFirst-FirstMin)*((double)rand()/(double)RAND_MAX);
           // printf("FirstIn = %lf FirstDone = %d\n", FirstIn, FirstDone);
            TimelineFirst += FirstIn;
            AddQueueArray(&FirstQueque, TimelineFirst);
        }

        while((TimelineM > TimelineSecond) || (SecondQueque.size == 0)){
            SecondIn = SecondMin + (RangeSecond-SecondMin)*((double)rand()/(double)RAND_MAX);
            //printf("SecondtIn = %lf SecondDone = %d\n", SecondIn, SecondDone);
            TimelineSecond += SecondIn;
            AddQueueArray(&SecondQueque, TimelineSecond);
        }

        CurFirst = FirstQueque.size;
        CurSecond = SecondQueque.size;
        CurFirstSum += CurFirst;
        CurSecondSum += CurSecond;

        if (CurFirst >= MAX_LENGTH || CurSecond >= MAX_LENGTH){
            printf("\nOVERFLOW!");
            print_res_table(TimelineM, UnTime, FirstDone + FirstQueque.size, FirstDone,
            SecondDone + SecondQueque.size, SecondDone, SecondThrown, Tiq1/FirstDone, Tiq2/WorkinSecond, fabs(100*(TimelineM-FirstDone*(FirstMin+RangeFirst)/2)/(FirstDone*(FirstMin+RangeFirst)/2)));
            return;
        }

        if((FirstQueque.data[0] <= TimelineM) || (FirstQueque.data[0] <= SecondQueque.data[0])){

            if(FirstQueque.data[0] > TimelineM){
                UnTime += FirstQueque.data[0] - TimelineM;
                TimelineM += FirstQueque.data[0] - TimelineM;
            }

            FirstWork = MinWorkFirst + (RangeWorkFirst-MinWorkFirst)*((double)rand()/(double)RAND_MAX);
            TimelineM += FirstWork;
            Tiq1 += TimelineM - PopQueueArray(&FirstQueque);
            FirstDone++;
            // ll++;
            if(FirstDone % 100 == 0){
                print_cur_table(FirstDone, CurFirst-1, (CurFirstSum-1)/(double)Iter, CurSecond,
                         CurSecondSum/(double)Iter, Tiq1/FirstDone, Tiq2/ (SecondDone + SecondThrown));
            }
        }
        else{
            WorkinSecond++;
            SecondWork = MinWorkSecond + (RangeWorkSecond-MinWorkSecond)*((double)rand()/(double)RAND_MAX);
            ll++;
            if(SecondQueque.data[0] > TimelineM){
                UnTime += SecondQueque.data[0] - TimelineM;
                TimelineM += SecondQueque.data[0] - TimelineM;
            }

            if(FirstQueque.data[0] >= TimelineM + SecondWork){
                TimelineM += SecondWork;
                Tiq2 += TimelineM - PopQueueArray(&SecondQueque);
                SecondDone++;
            }
            else{
                Tiq2 += TimelineM - PopQueueArray(&SecondQueque);
                TimelineM = FirstQueque.data[0];
                SecondThrown++;
                AddQueueArray(&SecondQueque, TimelineM);
            }
        }
    }
    printf("%d", ll);
    print_res_table(TimelineM, UnTime, FirstDone + FirstQueque.size, FirstDone,
    SecondDone + SecondQueque.size, SecondDone, SecondThrown, Tiq1/FirstDone, Tiq2/WorkinSecond, fabs(100*(TimelineM-FirstDone*(FirstMin+RangeFirst)/2)/(FirstDone*(FirstMin+RangeFirst)/2)));
    ClearQueueArray(&FirstQueque);
    ClearQueueArray(&SecondQueque);
}

int input_key(int key1, int key2){
    int result;
    printf(">> ");
    result = func();
    while (1){
        if (result >= key1 && result <= key2)
            break;
        else
        {
            printf("incorrect input, please return input...\n");
            printf(">> ");
            result = func();
        }
    }
    return result;
}

int func(){
    int result;
    while (scanf("%d",&result) != 1){
        while (getchar() != '\n');
        printf("incorrect input, please return input...\n");
        printf(">> ");
    }
    return result;
}
