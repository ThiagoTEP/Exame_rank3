#include <stdio.h>
#include <stdlib.h>

size_t ft_strlen(char *s)
{
	size_t i = 0;

	while(s[i])
		i++;
	return i;
}

void backtrack(char *s, size_t s_len, char *buf, size_t b_len, int *used)
{
	size_t i = 0;

	if(s_len == b_len)
	{
		buf[b_len] = '\0';
		puts(buf);
		return;
	}
	while(i < s_len)
	{
		if(!used[i])
		{
			used[i] = 1;
			buf[b_len] = s[i];
			backtrack(s, s_len, buf, b_len + 1, used);
			used[i] = 0;
		}
		i++;
	}
}

int main(int ac, char *av[])
{
	char *s, *buf;
	size_t s_len;
	int *used;
	char tmp;

	if(ac != 2)
		return 1;
	s = av[1];
	s_len = ft_strlen(s);
	buf = malloc(sizeof(char) *  s_len + 1);
	used = calloc(s_len, sizeof(int));
	if(!buf || !used)
	{
		if(buf)
			free(buf);
		if(used)
			free(used);
		return 1;
	}
	size_t i = 0;
	while(i < s_len - 1)
	{
		size_t j = i + 1;
		while(j < s_len)
		{
			if(s[i] > s[j])
			{
				tmp = s[i];
				s[i] = s[j];
				s[j] = tmp;
			}
			j++;
		}
		i++;
	}
	backtrack(s, s_len, buf, 0, used);
	free(buf);
	free(used);
	return 0;
}
