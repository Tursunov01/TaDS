#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define OK 0
#define EMPTY -1
#define WORD -2
#define LENGHT -3
#define NOT_FOUND -4
#define ZERO -5
#define ERR -6
#define EPS 1.0e-7

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







int main(void)
{
	int check_int, check_double;
	//double mantis;
	//int power;
	char int_1[50];
	char real_1[50];
	int rc = OK;
	setbuf(stdout, NULL);
	printf("THIS PROGRAM IS INTENDED TO DIVIDE A VALID NUMBER INTO THE WHOLE\n");
	printf("for a real number, the number of digits in the mantissa should not exceed the number 30.\n"); 
	printf("And the maximum number of digits in the exponents should be 5\n");
	printf("Input float number: \n");
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
				//int_to_real(int_1, &mantis, &power);
				//division(real_1, mantis, power);
			}
			if (check_int == EMPTY || check_double == EMPTY)
			{
				printf("You input empty string!!\tPlease try again\n");
				rc = EMPTY;
			}
			if (check_int == WORD || check_double == WORD)
			{
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