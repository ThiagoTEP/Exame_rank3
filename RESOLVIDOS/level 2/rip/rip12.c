#include <stdio.h>
#include <stdlib.h>

int is_safe(char *buf)
{
	int i = 0;
	int count = 0;

	while(buf[i])
	{
		if(buf[i] == '(')
			count++;
		else if(buf[i] == ')')
		{
			if(count ==  0)
				return 0;
			count--;
		}
		i++;
	}
	return(count==0);
}

void backtrack(char *s, int index, int left, int rigth, int open, char *buf)
{
	if(s[index] == '\0')
	{
		buf[index] = '\0';
		if(is_safe(buf))
			puts(buf);
		return;
	}
	if(s[index] == '(')
	{
		if(left > 0)
		{
			buf[index] = ' ';
			backtrack(s, index + 1, left - 1, rigth, open, buf);
		}
		buf[index] = '(';
		backtrack(s, index + 1, left, rigth, open + 1, buf);
	}
	else
	{
		if(rigth > 0)
		{
			buf[index] = ' ';
			backtrack(s, index + 1, left, rigth - 1, open, buf);
		}
		if(open > 0)
		{
			buf[index] = ')';
			backtrack(s, index + 1, left, rigth, open - 1, buf);
		}
	}
}

int main (int ac, char *av[])
{
	char *s, *buf;
	int i = 0, left = 0, rigth = 0;

	if(ac != 2)
		return 1;
	s =  av[1];
	while(s[i])
	{
		if(s[i] == '(')
			left++;
		else
		{
			if(left > 0)
				left--;
			else
				rigth++;
		}
		i++;
	}
	buf = malloc(i + 1);
	if(!buf)
		return 1;
	backtrack(s, 0, left, rigth, 0, buf);
	free(buf);
	return 0;
}
