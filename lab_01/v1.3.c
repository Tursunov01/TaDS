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


//Функция которая находит позицию e  в числе
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
	for (int i = 0; i < strlen(num); i++)
	{ 
		if (num[i] == '.')
			return i;
	}
	return NOT_FOUND;
}

int check_lenght(const char *num)
{
	int rc = OK;
	if ((strlen(num) > 30) && (num[0] != '-' || num[0] != '+'))
		return LENGHT;
	else if ((num[0] == '-' || num[0] == '+') && strlen(num) > 31)
		return LENGHT;
	return rc;
}

int with_point(const char *num)
{
	int p = find_point(num);
	int k = 0;
	char a[30], b[30];
	for (int i = 0; i < p; i++)
		a[i] = num[i];
	a[p] = '\0';
	for (int i = p+1; i < strlen(num); i++)
	{
		b[k] = num[i];
		k++;
	}
	b[k] = '\0';
	for (int i = 0; i < strlen(a); i++)
	{
		if (i == 0 && (a[0] == '-' || a[0] == '+'))
			continue;
		if (isdigit(a[i]) == 0)
			return  WORD;
	}
	if (strlen(b) == 0)
		return WORD;
	for (int i = 0; i < strlen(b); i++)
	{
		if (isdigit(b[i]) == 0)
			return WORD;
	}
	if ((strlen(a) > 30) && (a[0] != '-' || a[0] != '+'))
		return LENGHT;
	else if ((a[0] == '-' || a[0] == '+') && strlen(a) > 31)
		return LENGHT;
	if ((strlen(b) > 30) && (b[0] != '-' || b[0] != '+'))
		return LENGHT;
	else if ((b[0] == '-' || b[0] == '+') && strlen(b) > 31)
		return LENGHT;
	if (strlen(a) + strlen(b) > 30)
		return LENGHT;
	return OK;
}

 //Функция для проверки ввода целого числа
int check_integer(const char *num)
{
	int rc = OK;
	if (strlen(num) == 0)
		rc = EMPTY;
	if (rc == OK)
	{
		if (strlen(num) == 1 && num[0] == '0')
			rc = ZERO;
		for (int i = 0; i < strlen(num) && rc == OK; i++)
		{
			if (i == 0 && (num[0] == '-' || num[0] == '+'))
				continue;
			if (isdigit(num[i]) == 0)
				rc = WORD;
		}
		if (rc == OK)
			rc = check_lenght(num);
	}
	return rc;
}
// Функция для проверки ввода действительного числа
int check_real(const char *num)
{
	int pos_e = find_e(num);
	int pos_point = find_point(num);
	int rc = 0;
	int k = 0;
	char a[30], b[30];
	if (strlen(num) == 0)
		return EMPTY;
	if (pos_e == NOT_FOUND)//если нет экспоненты
	{
		if (pos_point == NOT_FOUND)//если нет точки
		{
			for (int i = 0; i < strlen(num); i++)
			{
				if (i == 0 && (num[0] == '-' || num[0] == '+'))
					continue;
				if (isdigit(num[i]) == 0)
					return WORD;
			}
			if ((strlen(num) > 30) && (num[0] != '-' || num[0] != '+'))
				return LENGHT;
			else if ((num[0] == '-' || num[0] == '+') && strlen(num) > 31)
				return LENGHT;
		}
		else//если есть точка
		{
			rc = with_point(num);
			if (rc != OK)
				return rc;
		}
	}
	else//если экспонента существует
	{
		for (int i = 0; i < pos_e; i++)
			a[i] = num[i];
		a[pos_e] = '\0';
		for (int i = pos_e+1; i < strlen(num); i++)
		{
			b[k] = num[i];
			k++;
		}
		b[k] = '\0';
		if (find_point(a) == NOT_FOUND)
		{
			for (int i = 0; i < strlen(a); i++)
			{
				if (i == 0 && (a[0] == '-' || a[0] == '+'))
					continue;
				if (isdigit(a[i]) == 0)
					return  WORD;
			}
			if (rc == OK)
			{
				if ((strlen(a) > 30) && (a[0] != '-' || a[0] != '+'))
					return LENGHT;
				else if ((a[0] == '-' || a[0] == '+') && strlen(a) > 31)
					return LENGHT;
			}
			for (int i = 0; i < strlen(b); i++)
			{
				if (i == 0 && (b[0] == '-' || b[0] == '+'))
					continue;
				if (isdigit(b[i]) == 0)
					return  WORD;
			}
			if (rc == OK)
			{
				if ((strlen(b) > 5) && (b[0] != '-' || b[0] != '+'))
					return LENGHT;
				else if ((b[0] == '-' || b[0] == '+') && strlen(b) > 6)
					return LENGHT;
			}
		}
		else
			rc = with_point(a);
		if (rc == OK)
		{
			for (int i = 0; i < strlen(b); i++)
			{
				if (i == 0 && (b[0] == '-' || b[0] == '+'))
					continue;
				if (isdigit(b[i]) == 0)
					return  WORD;
			}
			if (rc == OK)
			{
				if ((strlen(b) > 5) && (b[0] != '-' || b[0] != '+'))
					return LENGHT;
				else if ((b[0] == '-' || b[0] == '+') && strlen(b) > 6)
					return LENGHT;
			}
		}
		else 
			return rc;
	}
	return rc;
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


void form_int(const char *num, char *a, int *power, int *sign, int *exp)
{
	if (find_e(num) != NOT_FOUND && find_point(num) != NOT_FOUND)//есть буква е и точка
	{
		sign_exp(num, exp);
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
		sign_exp(num, exp);
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
	int  num = m/n;
	int k = 0;
	while(num != 0)
	{
		num = num / 10;
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
	s = size(m, n);
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
	if (strlen(dividend) < strlen(divisor) || strlen(dividend) <= 10)
		return 0;//всё ОК
	return 1;
}

void process(char *a, const char *b)
{
	int power = 0, exp = 0, lenght;
	int k = 0, sign1 = NONE, sign2 = NONE;
	char dividend[30], *quotient, result[30], c[30];
	long int divisor;
	long int remainder;
	form_int(a, dividend, &power, &sign1, &exp);
	form_int(b, c, &power, &sign2, &exp);
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
		printf("lenght is %d\n", lenght);
		if (lenght >=30)
		{
			for (int i = 0; i <= 30; i++)
			{
				result[k] = quotient[i];
				k++;
			}
			result[k] = '\0';
			if ((sign1 == MINUS && sign2 == MINUS) || (sign1 == PLUS && sign2 == PLUS) || (sign1 == NONE && sign2 == NONE))
				printf("0.%se%d\n",result, lenght+exp+power);
			else
				printf("-0.%se%d\n",result, lenght+exp+power);
		}
		else
		{			
			if ((sign1 == MINUS && sign2 == MINUS) || (sign1 == PLUS && sign2 == PLUS) || (sign1 == NONE && sign2 == NONE))
				printf("0.%se%d\n",quotient, lenght+exp+power);
			else
				printf("-0.%se%d\n",quotient, lenght+exp+power);
		}
	}
	else
		division2(dividend, divisor, power, exp, sign1, sign2);	
}

int main(void)
{
	int check_int, check_double;
	char int_1[MAX];
	char real_1[MAX];
	int rc = OK;
	setbuf(stdout, NULL);
	printf("\t\t\t\tINFO\n\n");
	printf("\tThis program is intended to divide a valid number into the whole\n");
	printf("\n  For a real number, the number of digits in the mantissa should not exceed the number 30.\n"); 
	printf("\n\tAnd the maximum number of digits in the exponents should be 5\n");
	printf("\n\tThere is no difference between e or E\n");
	printf("\n\tYou can input only numbers and symbols of '.' or '-' or '+'\n");
	printf("\n\tResult will be given in exponential form\n\n");
	
	printf("\nInput float number: \n");
	printf("\n|       place for mantis      |e|power|\n");
	if (fgets(real_1, sizeof(real_1), stdin) == NULL)
		rc = ERR;
	if (rc == OK)
	{
		real_1[strlen(real_1) - 1] = '\0';
		printf("Input integer number: \n");
		if (fgets(int_1, sizeof(int_1), stdin) != NULL)
		{
			int_1[strlen(int_1) - 1] = '\0';
			check_int = check_integer(int_1);
			check_double = check_real(real_1);
			if (check_int == OK && check_double == OK)
			{
				printf("OK\n");
				process(real_1, int_1);
			}
			if (check_int == EMPTY || check_double == EMPTY)
			{
				printf("You input empty string!!\tPlease try again\n");
				rc = EMPTY;
			}
			if (check_int == WORD || check_double == WORD)
			{
				printf("int is %d\tfloat is %d\n", check_int, check_double);
				printf("You input not allowed symbols!!\tPlease try again\n");
				rc = WORD;
			}
			if (check_int == LENGHT || check_double == LENGHT)
			{
				printf("You input too much quantity of numbers!!\tPlease try again\n");
				rc = LENGHT;
			}
			if (check_int == ZERO)
			{
				printf("You input zero!!\tPlease try again\n");
				rc = ZERO;
			}
		}
		else
			rc = ERR;
	}
	else
		printf("Error in input!\n");
	return rc;
}