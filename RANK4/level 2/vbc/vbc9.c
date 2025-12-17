#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node{
	enum {
		ADD,
		MULTI,
		VAL
	} type;
	int val;
	struct node *l;
	struct node *r;
} node;

node *parse_add(char **s);

node *new_node(node n)
{
	node *ret = calloc(1, sizeof(node));
	if(!ret)
		return NULL;
	*ret = n;
	return ret;
}

void destroy_tree(node *n)
{
	node *ret;

	if(!n)
		return;
	if(n->type != VAL)
	{
		destroy_tree(n->l);
		destroy_tree(n->r);
	}
	free(n);
}

void unexpected(char c)
{
	if(c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n");
}

int accept(char **s, char c)
{
	if(**s == c)
	{
		(*s)++;
		return 1;
	}
	return 0;
}

int expect(char **s, char c)
{
	if( accept(s, c))
		return 1;
	unexpected(**s);
	return 0;
}

node *create_node(node *left, node *right, char val)
{
	node tmp;
	node *new;

	tmp.l = left;
	tmp.r = right;
	if(isdigit(val))
	{
		tmp.type = VAL;
		tmp.val = val - '0';
	}
	else if(val == '+')
		tmp.type = ADD;
	else
		tmp.type = MULTI;
	new = new_node(tmp);
	if(!new)
	{
		destroy_tree(left);
		destroy_tree(right);
		return NULL;
	}
	return new;
}

node *parse_paren(char **s)
{
	node *ret;

	if(isdigit(**s))
	{
		ret = create_node(NULL, NULL, **s);
		(*s)++;
		return ret;
	}
	
}
