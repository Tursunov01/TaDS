#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 30
#define OK 0
#define EMPTY -1
#define WORD -2
#define LENGHT -3
#define NOT_FOUND -4
#define ZERO -5
#define ERR -6
#define EPS 1.0e-7

int find_e(const char *num)
{
    for (int i = 0; i < strlen(num); i++)
    {
        if (num[i] == 'e' || num[i] == 'E')
            return i;
    }
    return NOT_FOUND;
}

//Функция которая находит позицию точки  в числе
int find_point(const char *num)
{
    for (int i = 0; i < strlen(num) && i < 11; i++)
    {
        if (num[i] == '.')
            return i;
    }
    return NOT_FOUND;
}

void transform_int(const char *num, char *num_1)
{
    int k = 0;
	for (int i = 0; i < strlen(num); i++)
	{
        num_1[k] = num[i];
		k++;
		if (k >= 10)
			break;
	}
	num_1[k] = '\0';
}

void rewrite(int len, const char *num, char *num_1)
{
	int k = 0;
	for (int i = 0; i < len - 1; i++)
    {
        if(num[i] == '.')
            continue;
        else
        {
            num_1[k] = num[i];
            k++;
			if (k >= 10)
				break;
        }
    }
	num_1[k] = '\0';
}

void transform_real(const char *num, char *num_1)
{
	int k = 0;
	if (find_point(num) != NOT_FOUND && find_e(num)  == NOT_FOUND)//если есть точка и нет экспоненты
		rewrite(strlen(num), num, num_1);
    if (find_point(num) != NOT_FOUND && find_e(num) != NOT_FOUND)//если есть точка и экспонента
		rewrite(find_e(num), num, num_1);
    if (find_point(num) == NOT_FOUND && find_e(num) != NOT_FOUND)//если нет точки и есть экспонента
    {
        for (int i = 0; i < find_e(num) && i < 11; i++)
		{
            num_1[k] = num[i];
			k++;
			if (k >= 10)
				break;
		}
		num_1[k] = '\0';
    }
	if (find_point(num) == NOT_FOUND && find_e(num) == NOT_FOUND)//если нет точки и есть экспонента
    {
        printf("eee Baby\n");
		for (int i = 0; i < strlen(num) && i < 11; i++)
		{
            num_1[k] = num[i];
			k++;
			printf("k is %d\n", k);
			if (k >= 9)
				break;
		}
		num_1[k] = '\0';
    }
}

void division(const char *num_1, const char *num_2)
{
    long long int k;
    long long int m, n;
    m = atoi(num_1);
    n = atoi(num_2);
	printf("m is %I64d\nn is %I64d\n", m, n);
    printf("%I64d.", m / n);
    for (int i = 0; i < MAX_LEN - 1; i++)
    {
        m = (m % n) * 10;
        printf("%I64d", m / n);
    }
    m = (m % n)*10;
    k = m / n;
    if (((m % n) * 10/ n) >= 5)
        printf("%I64d",k+1);
    else
        printf("%I64d",k);
}


int main(void)
{
    char a[30] = {"-1"};
    char b[30] = {"3"};
    char a1[30], b1[30];
    transform_real(a, a1);
	transform_int(b, b1);
    division(a1, b1);
    return 0;
}