#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node{
	enum{
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
	if(accept(s, c))
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
	while(accept(s, '('))
	{
		ret = parse_add(s);
		if(!ret)
			return NULL;
		if(!expect(s, ')'))
		{
			destroy_tree(ret);
			return NULL;
		}
		return ret;
	}
	unexpected(**s);
	return NULL;
}

node *parse_multi(char **s)
{
	node *left;
	node *right;

	left = parse_paren(s);
	if(!left)
		return NULL;
	while(accept(s, '*'))
	{
		right = parse_paren(s);
		if(!right)
		{
			destroy_tree(left);
			return NULL;
		}
		left = create_node(left, right, '*');
		if(!left)
		{
			destroy_tree(right);
			return NULL;
		}
	}
	return left;
}

node *parse_add(char **s)
{
	node *left;
	node *right;

	left = parse_multi(s);
	if(!left)
		return NULL;
	while(accept(s, '+'))
	{
		right = parse_multi(s);
		if(!right)
		{
			destroy_tree(left);
			return NULL;
		}
		left = create_node(left, right, '+');
		if(!left)
		{
			destroy_tree(right);
			return NULL;
		}
	}
	return left;
}

node *parse_expr(char *s)
{
	node *ret;

	ret = parse_add(&s);
	if(!ret)
		return NULL;
	if(*s)
	{
		unexpected(*s);
		destroy_tree(ret);
		return NULL;
	}
	return ret;
}

int eval_tree(node *tree)
{
	switch(tree->type)
	{
		case ADD:
			return((eval_tree(tree->l)) + (eval_tree(tree->r)));
		case MULTI:
			return((eval_tree(tree->l)) * (eval_tree(tree->r)));
		case VAL:
			return (tree->val);
	}
	return 1;
}

int main(int ac, char *av[])
{
	if(ac != 2)
		return 1;
	node *tree = parse_expr(av[1]);
	if(!tree)
		return 1;
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
}
