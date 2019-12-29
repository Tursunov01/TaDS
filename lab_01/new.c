#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 30
#define NONE 3
#define MINUS 2
#define PLUS 1
#define OK 0
#define EMPTY -1
#define WORD -2
#define LENGHT -3
#define NOT_FOUND -4
#define ZERO -5
#define ERR -6
#define EPS 1.0e-7
#define MAX 10000

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

int len(const char *num)
{
	int size = 0;
	if (find_e(num) != NOT_FOUND && find_point(num) != NOT_FOUND)//есть точка и е
	{
		for (int i = find_point(num)+1; i < find_e(num); i++)
			size++;
	}
	if (find_e(num) == NOT_FOUND && find_point(num) != NOT_FOUND)//есть точка и нет е
	{
		for (int i = find_point(num)+1; i < strlen(num); i++)
			size++;
	}
	return size;
}

void sign_exp(const char *num, int *exp)
{
	char e1[10];
	int k = 0;
	for (int i = find_e(num)+1; i < strlen(num); i++)
	{
		e1[k] = num[i];
		k++;
	}
	e1[k] = '\0';
	*exp = atoi(e1);
}

void rewrite(const char *num, char *a, int start, int end)
{
	int k = 0;
	for (int i = start; i < end; i++)
	{
		if (num[i] == '.')
			continue;
		else
		{
			a[k] = num[i];
			k++;
		}
	}
	a[k] = '\0';
}


int form_int(const char *num, char *a, int *power, int *sign)
{
	int exp;
	if (find_e(num) != NOT_FOUND && find_point(num) != NOT_FOUND)//есть буква е и точка
	{
		sign_exp(num, &exp);
		if (num[0] == '-' || num[0] == '+')
		{
			rewrite(num, a, 1, find_e(num));
			printf("form is %s\n", a);
			if (num[0] == '-')
				*sign = MINUS;
			if (num[0] == '+')
				*sign = PLUS;
			if (num[1] == '0')
				*power = -len(num);
			if(num[1] != '0')
				*power = -len(num);
		}
		else
		{
			rewrite(num, a, 0, find_e(num));
			if (num[0] == '0')
			{
				printf("YES\n");
				*power = -len(num);
			}
			if (num[0] != '0')
			{
				printf("NO\n");
				*power = -len(num);
			}
		}
			
	}
	if (find_e(num) == NOT_FOUND && find_point(num) != NOT_FOUND)//нет буквы е, но есть точка
	{
		if (num[0] == '-' || num[0] == '+')
		{
			rewrite(num, a, 1, strlen(num));
			if (num[0] == '-')
				*sign = MINUS;
			if (num[0] == '+')
				*sign = PLUS;
			if (num[1] == '0')
				*power = -len(num);
			if(num[1] != '0')
				*power = -len(num);
		}
		else
		{
			rewrite(num, a, 0, strlen(num));
			if (num[0] == '0')
				*power = -len(num);
			if(num[0] != '0')
				*power = -len(num);
		}
	}
	if (find_e(num) != NOT_FOUND && find_point(num) == NOT_FOUND)//есть буква е, но нет точки
	{
		sign_exp(num, &exp);
		if (num[0] == '-' || num[0] == '+')
		{
			rewrite(num, a, 1, find_e(num));
			if (num[0] == '-')
				*sign = MINUS;
			if (num[0] == '+')
				*sign = PLUS;
		}
		else
			rewrite(num, a, 0, find_e(num));
	}
	if (find_e(num) == NOT_FOUND && find_point(num) == NOT_FOUND)//нет буквы е и точки
	{
		if (num[0] == '-' || num[0] == '+')
		{
			rewrite(num, a, 1, strlen(num));
			if (num[0] == '-')
				*sign = MINUS;
			if (num[0] == '+')
				*sign = PLUS;
		}
		else
			rewrite(num, a, 0, strlen(num));
	}
	return exp;
}

 
char *division1(char dividend[],long divisor, long int *remainder)
{
   
    static char quotient[MAX];
    long temp=0;
    int i=0,j=0;
 
    while(dividend[i]){
        
         temp = temp*10 + (dividend[i] - 48);
         if(temp<divisor){
            
             quotient[j++] = 48;
            
         }
         else{
             quotient[j++] = (temp / divisor) + 48;;
             temp = temp % divisor;
 
         }
         i++;
    }
 
    quotient[j] = '\0';
    *remainder = temp;
    return quotient;
}

int size(long int m, long int n)
{
	int k = 0;
	long int num = m;
	while (num > 0)
	{
		num = num/n;
		k++;
	}
	return k;
}


void division2(const char *num_1, long int n, int power, int exp, int sign1, int sign2)
{
    long int k;
    long int m;
	int s = 0, check  = 0;
    m = atoi(num_1);
	s = size(m, n) + 1;
	printf("s is %d\n", s);
	if ((sign1 == MINUS && sign2 == MINUS) || (sign1 == PLUS && sign2 == PLUS) || (sign1 == NONE && sign2 == NONE))
	{	
		if ((m / n) > 0)
		{
			check = s;
			printf("0.%ld", m / n);
		}
		else
			printf("%ld.", m / n);
	}
	else
	{
		if ((m / n) > 0)
		{
			check = s;
			printf("-0.%ld", m / n);
		}
		else
			printf("-%ld.", m / n);
	}
	if (check > 0)
	{
		for (int i = 0; i < MAX_LEN - 1- s -1; i++)
		{
			m = (m % n) * 10;
			printf("%ld", m / n);
		}
		m = (m % n)*10;
		k = m / n;
		if (((m % n) * 10/ n) >= 5)
			printf("%lde%d",k+1, power+exp+s);
		else
			printf("%lde%d",k, power+exp+s);
	}
	else
	{
		for (int i = 0; i < MAX_LEN - 1; i++)
		{
			m = (m % n) * 10;
			printf("%ld", m / n);
		}
		m = (m % n)*10;
		k = m / n;
		if (((m % n) * 10/ n) >= 5)
			printf("%lde%d",k+1, power+exp);
		else
			printf("%lde%d",k, power+exp);
	}
}

int check_in(const char *dividend, const char *divisor)
{
	long int a, b;
	a = atoi(dividend);
	b = atoi(divisor);
	if (a < b || strlen(dividend) <= 10)
		return 0;//всё ОК
	return 1;
}

void process(char *a, const char *b)
{
	int power = 0, exp1 = 0, lenght, exp2 = 0;
	int k = 0, sign1 = NONE, sign2 = NONE;
	char dividend[30], *quotient, result[30], c[30];
	long int divisor;
	long int remainder;
	exp1 = form_int(a, dividend, &power, &sign1);
	exp2 = form_int(b, c, &power, &sign2);
    divisor = atoi(c);
	if (check_in(dividend, c) == 1)
	{
		quotient = division1(dividend,divisor, &remainder);
		while(*quotient)
			if(*quotient ==48)
				quotient++;
			else
				break;
		lenght = strlen(quotient);
		if (lenght >=30)
		{
			for (int i = 0; i <= 30; i++)
			{
				result[k] = quotient[i];
				k++;
			}
			result[k] = '\0';
			if ((sign1 == MINUS && sign2 == MINUS) || (sign1 == PLUS && sign2 == PLUS) || (sign1 == NONE && sign2 == NONE))
				printf("0.%se%d\n",result, lenght+exp1+power);
			else
				printf("-0.%se%d\n",result, lenght+exp1+power);
		}
		else
		{			
			if ((sign1 == MINUS && sign2 == MINUS) || (sign1 == PLUS && sign2 == PLUS) || (sign1 == NONE && sign2 == NONE))
				printf("0.%se%d\n",quotient, lenght+exp1+power);
			else
				printf("-0.%se%d\n",quotient, lenght+exp1+power);
		}
	}
	else
		division2(dividend, divisor, power, exp1, sign1, sign2);
	
}
int main(void)
{
	char real_1[MAX], int_1[MAX];
	setbuf(stdout, NULL);
	printf("Input float number: \n");
	fgets(real_1, sizeof(real_1), stdin);
	real_1[strlen(real_1) - 1] = '\0';
	printf("Input integer number: \n");
	fgets(int_1, sizeof(int_1), stdin);
	int_1[strlen(int_1) - 1] = '\0';
	process(real_1, int_1);
	return 0;
}