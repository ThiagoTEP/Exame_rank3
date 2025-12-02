#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c;

	while((c = fgetc(f)) != EOF)
	{
		if(!isspace(c))
		{
			ungetc(c, f);
			break;
		}
	}

    return (0);
}

int match_char(FILE *f, char c)
{
    int ch = fgetc(f);

	if(ch == c)
		return 1;
	if(ch != EOF)
		ungetc(ch, f);
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
	int c = fgetc(f);

	if(c == EOF)
		return 0;
	char *dst = va_arg(ap, char *);
	*dst = (char)c;
	return 1;
}

int scan_int(FILE *f, va_list ap)
{
       int c = fgetc(f);
	int value = 0;
	int sign = 1;

	if(c == '-' || c == '+')
	{
		if(c == '-')
			sign = -1;
		c = fgetc(f);
	}
	while(isdigit(c))
	{
		value = value * 10 + (c - '0');
		c = fgetc(f);
	}
	if(c != EOF)
		ungetc(c, f);
	int *dst = va_arg(ap, int *);
	*dst = value * sign;
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
    char *dst = va_arg(ap, char *);
	int c = fgetc(f);
	int i = 0;

	if(c == EOF)
		return 0;
	dst[i++] = (char)c;

	while((c = fgetc(f)) != EOF && !isspace(c))
		dst[i++] = (char)c;
	if(c != EOF)
		ungetc(c, f);
	dst[i] = '\0';
    return (1);
}

int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;
	int c = fgetc(f);

	if (c == EOF)
		return EOF;
	ungetc(c, f);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	if (ferror(f))
		return EOF;
	return nconv;
}

int ft_scanf(const char *format, ...)
{
	int ret;
	va_list ap;
	va_start(ap, format);
	ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}

int main(void)
{
	int num;
	char t;
	char line[20];

	printf("NUM\n");
	if(ft_scanf("%d", &num) != 1)
		return 1;
	printf("CHAR\n");
	if(ft_scanf(" %c", &t) != 1)
		return 1;
	printf("LINE\n");
	if(ft_scanf("%s", line) != 1)
		return 1;


	printf("num : %d\n", num);
	printf("Char : %c\n", t);
	printf("Line : %s\n", line);
	return 0;
}
