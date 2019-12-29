#include <stdio.h>
#include <string.h>
#include <math.h>

#define EPS 1.0e-7
//Функция для сравнения 2 действителных чисел
int compare(double num_1, float num_2)
{
    if (fabs(num_1 - num_2) < EPS)
        return 1;
    else
        return 0;
}

//Функция которая находит позицию e  в числе
int find_e(const char *num)
{
	for (int i = 0; i < strlen(num); i++)
	{ 
 		if (num[i] == 'e' || num[i] == 'E')
			return i;
	}
	return -1;
}
 //Функция для проверки ввода целого числа
int check_integer(const char *num)
{
	int n = strlen(num);
	if (num[0] == '0')
	{
		printf("Integer element can not be equal zero\n");
		return -1;
	}
	for (int i = 0; i < n; i++)
	{
		if (num[i] == '.')
		{
			printf("You input float number\n Please input integer number!\n");
			return -1;
		}
	}
	if (num[0] == '-' || num[0] == '+')
	{
		if (n - 1 > 30)
		{
			printf("Quantity of numbers in mantis is over 30\n");
			return -1;
		}
	}
	if ((n) > 30)
	{
		printf("Quantity of numbers in mantis is over 30\n");
		return -1;
	}
	return 0;
}
// Функция для проверки ввода действительного числа
int check_real(const char *num)
{
	int before_e = 0, after_e = 0;
	int pos_e = find_e(num);
	int status = 0, points = 0;
	for (int i = 0; i < strlen(num); i++)
	{
		if (num[i] == '.')
		{
			if (i > pos_e && pos_e != -1)
			{
				printf("exponent must be integer\n");
				return -1;
			}
			points++;
		}
	}
	if (points >= 2)
	{
		printf("Form of number is incorrect\n");
		return -1;
	}
	else
	{
		if (num[pos_e + 1] == '-' || num[pos_e + 1] == '+')
			status = 1;
		if (pos_e == -1)
		{
			if (num[0] == '-' || num[0] == '+')
			{
				if (strlen(num) - 2 > 30)
				{
					printf("Quantity of numbers in mantis is over 30\n");
					return -1;
				}
			}
				if (strlen(num) - 1 > 30)
				{
					printf("Quantity of numbers in mantis is over 30\n");
					return -1;
				}
		}
		else
		{
			for (int i = 0; i < pos_e; i++)
				before_e++;
			for (int i = pos_e+1; i < strlen(num); i++)
				after_e++;
			if (before_e - 1 > 30)
				{
					printf("Quantity of numbers in mantis is over 30\n");
					return -1;
				}
			if (status == 1)
			{
				if (after_e - 1 > 5)
				{
					printf("exponent must consist of 5 numbers\n");
					return -1;
				}
			}
			else
			{
				if (after_e > 5)
				{
					printf("exponent must consist of 5 numbers\n");
					return -1;
				}
			}
		}
	}
	return 0;
}

//функция для представления целого числа в экспоненуиальной форме
void int_to_real(const char *num, double *mantis, int *power)
{
	int size = strlen(num);
	int cur;
	cur = atof(num);
	(*mantis) = cur / pow(10, size);
	(*power) = size;
}

//Функция для преобразования мантиссы
void change(double *mantis, int *power)
{
	double b;
	int n = 0;
	if ((*mantis) > 1 || compare(*mantis, 1) == 1)
	{
		b = *mantis;
		while (b > 1 || compare(b, 1) == 1)
		{
			b = b / 10;
			n++;
		}
		(*mantis) = b;
		(*power)+= n;
	}
	if ((*mantis) < -1 || compare(*mantis, -1) == 1)
	{
		b = *mantis;
		while (b < -1 || compare(b, -1) == 1)
		{
			b = b / 10;
			n++;
		}
		(*mantis) = b;
		(*power)+= n;
	}
}


//Функция для работы с действительными числами, которые записаны не в экспоненциальной форме
void transform(const char *num, double mantis_int, int power_int)
{
	double a = atof(num);
	double res_mantis;
	printf("transform is %lf\n", a);
	int n = 0, res_power;
	if (a < 1 && a > 0)
	{
		while (a < 1)
		{
			a*=10;
			n--;
		}
	}
	if (a > 1 || a < 0)
	{
		while (a > 1)
		{
			a/=10;
			n++;
		}
		a*=10;
		n--;
	}
	res_mantis = a / mantis_int;
	res_power = n - power_int;
	change(&res_mantis, &res_power);
	printf("Final result is %lfe%d\n", res_mantis, res_power);
}
//Функция для деления
void division(const char *num, double mantis_int, int power_int)
{
	char power_real[6];
	char mantis_real[31];
	int pos_e = find_e(num), k = 0, power_result, power_1;
	double mantis_1, mantis_result;
	if (pos_e == -1)
		transform(num, mantis_int, power_int);
	else if (pos_e == 0)
	{
		mantis_result = 1;
		for (int i = pos_e + 1; i < strlen(num); i++)
		{
			power_real[k] = num[i];
			k++;
		}
		power_real[k+1] = '\0';
		power_1 = atof(power_real);
		power_result = power_1 - power_int;
		change(&mantis_result, &power_result);
		printf("Final result is %lfe%d\n", mantis_result, power_result);
	}
	else
	{
		for (int i = 0; i < pos_e; i++)	
			mantis_real[i] = num[i];
		mantis_real[pos_e] = '\0';
		for (int i = pos_e + 1; i < strlen(num); i++)
		{
			power_real[k] = num[i];
			k++;
		}
		power_real[k+1] = '\0';
		mantis_1 = atof(mantis_real);
		power_1 = atof(power_real);
		mantis_result = mantis_1 / mantis_int;
		power_result = power_1 - power_int;
		change(&mantis_result, &power_result);
		printf("result is %lfe%d\n", mantis_result, power_result);
		printf("the result is presented in exponential form\n");
	}
}

int main(void)
{
	int check_int, check_double;
	double mantis;
	int power;
	char int_1[50];
	char real_1[50];
	setbuf(stdout, NULL);
	printf("THIS PROGRAM IS INTENDED TO DIVIDE A VALID NUMBER INTO THE WHOLE\n");
	printf("for a real number, the number of digits in the mantissa should not exceed the number 30.\n"); 
	printf("And the maximum number of digits in the exponents should be 5\n");
	printf("Input float number: \n");
	fgets(real_1, sizeof(real_1), stdin);
	real_1[strlen(real_1) - 1] = '\0';
	printf("Input integer number: \n");
	fgets(int_1, sizeof(int_1), stdin);
	int_1[strlen(int_1) - 1] = '\0';
	
	check_int = check_integer(int_1);
	check_double = check_real(real_1);
	if (check_int == 0 && check_double == 0)
	{
		int_to_real(int_1, &mantis, &power);
		division(real_1, mantis, power);
	}
	else
	{
		printf("Error in input!!");
		return -2;
	}
	return 0;
}