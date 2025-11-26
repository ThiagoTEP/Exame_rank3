#include <stdio.h>
#include <stdlib.h>

int ft_abs(int n)
{
	if(n < 0)
		return (-n);
	return n;
}

int is_safe(int *tab, int col, int row)
{
	int col_ant = 0;

	while(col_ant < col)
	{
		if(tab[col_ant] == row)
			return 0;
		if(ft_abs(tab[col_ant] - row) == col - col_ant)
			return 0;
		col_ant++;
	}
	return 1;
}

void print_solution(int *tab, int n)
{
	int i = 0;

	while(i < n)
	{
		fprintf(stdout, "%d", tab[i]);
		if(i < n - 1)
			fprintf(stdout, " ");
		i++;
	}
	fprintf(stdout, "\n");
}

void solve(int *tab, int col, int n)
{
	int row = 0;

	if(col == n)
	{
		print_solution(tab, n);
		return;
	}
	while(row < n)
	{
		if(is_safe(tab, col, row))
		{
			tab[col] = row;
			solve(tab, col + 1, n);
		}
		row++;
	}
}

int main(int ac, char *av[])
{
	int n;
	int *tab;

	if(ac != 2)
		return 1;
	n = atoi(av[1]);
	if(n <= 0)
		return 1;
	tab = malloc(sizeof(int) *  n);
	if(!tab)
		return 1;
	solve(tab, 0, n);
	free(tab);
	return 0;
}
