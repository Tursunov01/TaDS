#include <stdio.h>

int compare_array(int *a1, int len_a1, int *a2, int len_a2)
{
	if (len_a1 - len_a2 != 0)
		return len_a1 - len_a2;
	else
	{
		for (int i = 0; i < len_a1; i++)
		{
			if (a1[i] != a2[i])
				return a1[i] - a2[i];
		}
	}
	return 0;
}


int *increas_array(int *a1, int len_a1, int *a2, int len_a2)
{
	int diff = len_a1 - len_a2;
	int spare = 0;
	int result = 0;
	
	for (int i = len_a2 - 1; i >= 0; i--)
	{
		result = a1[diff + i] + a2[i] + spare;
		spare = 0;
		if (result > 9)
		{
			a1[diff + i] = result % 10;
			spare = result / 10;
		}
		else
			a1[diff + i] = result;
	}
	a1[0] += spare;
	if (diff == 0 && spare != 0)
		a1[0] = result;
	return a1;
}

void umenshit(int *a1, int len_a1, int *a2, int len_a2)
{
	int diff = len_a1 - len_a2;
	
	for (int i = len_a2 - 1;  i > -1; i--)
	{
		a1[i + diff] -= a2[i];
		if (a1[i + diff] < 0)
		{
			a1[i + diff] += 10;
			a1[i-1+diff]--;
		}
	}
}

int vichest(int *a1, int len_a1, int *a2, int len_a2)
{
	int a3[len_a1];
	int len_a3 = len_a1;
	int diff = len_a1 - len_a2;
	int count = 1;
	
	for (int i = 0; i  <  len_a3; i++)
		a3[i] = 0;
	for (int i = len_a2 - 1; i >= 0; i--)
		a3[diff + i] = a2[i];
	while (compare_array(a1, len_a1, increas_array(a3, len_a3, a2, len_a2), len_a3) >= 0)
		count++;
	umenshit(a3, len_a3, a2, len_a2);
	umenshit(a1, len_a1, a3, len_a3);
	return count;
}

void move_left(int *array)
{
	for (int i = 0; i < 30 - 1; i++)
		array[i] = array[i + 1];
}




int division(int *a1, int len_a1, int *a2, int len_a2, int *result, int *len_result)
{
	int tmp_len;
	int count = 0;
	int flag = 0;
	
	while(len_a1 > 0 && *len_result < 30)
	{
		tmp_len = 0;
		while(compare_array(a1, tmp_len, a2, len_a2) < 0)
			tmp_len++;
		if (tmp_len > len_a1)
		{
			count+=tmp_len - len_a1;
			len_a1 = tmp_len;
		}
		result[*len_result] = vichest(a1, tmp_len, a2, len_a2);
		*len_result += 1;
		while(a1[0] == 0 && tmp_len > 0)
		{
			move_left(a1);
			tmp_len -= 1;
			len_a1 -= 1;
			if (flag == 1 && len_a1 != 0)
			{
				result[*len_result] = 0;
				*len_result += 1;
			}
			flag = 1;
		}
		flag = 0;
	}
	for (int i = 0; i < 30; i++)
		printf("%d", result[i]);
	return count;
}


int main(void)
{
	int a1[2] = {1,2}, a2[2] = {4,5}, result[30] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int len_a1 = 2, len_a2 = 2, len_result = 0;
	int count;
	setbuf(stdout, NULL);
	/*printf("input a1: ");
	for (int i = 0; i < len_a1; i++)
		scanf("%d", &a1[i]);
	printf("input a2: ");
	for (int i = 0; i < len_a2-1; i++)
		scanf("%d", &a2[i]);*/
	count = division(a1, len_a1, a2, len_a2, result, &len_result);
	printf("Count is %d\n", count);
	printf("len Result is %d\n", len_result);
	/*for (int i = 0; i < 2; i++)
		printf("%d ", a1[i]);
	printf("hello\n");
	for (int i = 0; i < 2; i++)
		printf("%d ", a2[i]);
	printf("world");*/
	for (int i = 0; i < len_result; i++)
	{
		printf("%d\n", i);
		printf("%d", result[i]);
	}
	return 0;
}