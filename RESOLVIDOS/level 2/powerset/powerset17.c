#include <stdio.h>
#include <stdlib.h>

void print_solution(int *buf, int b_index)
{
	int i = 0;

	while(i < b_index)
	{
		fprintf(stdout, "%d", buf[i]);
		if(i < b_index - 1)
			fprintf(stdout, " ");
		i++;
	}
	fprintf(stdout, "\n");
}

void backtrack(int n, int s_index, int *set, int size, int *buf, int b_index, int sum)
{
	if(s_index >= size)
	{
		if(sum == n)
			print_solution(buf, b_index);
		return;
	}
	buf[b_index] = set[s_index];
	backtrack(n, s_index + 1, set, size, buf, b_index + 1, sum + set[s_index]);
	backtrack(n, s_index + 1, set, size, buf, b_index, sum);
}

int main(int ac, char *av[])
{
	int *set, *buf;
	int n, size;

	if(ac < 3)
		return 1;
	n = atoi(av[1]);
	size = ac - 2;
	buf = calloc(size, sizeof(int));
	set = calloc(size, sizeof(int));
	if(!buf || !set)
	{
		if(buf)
			free(buf);
		if(set)
			free(set);
		return 1;
	}
	int i = 0;
	while(i < size)
	{
		set[i] = atoi(av[i + 2]);
		i++;
	}
	backtrack(n , 0, set, size, buf, 0, 0);
	free(buf);
	free(set);
	return 0;
}
