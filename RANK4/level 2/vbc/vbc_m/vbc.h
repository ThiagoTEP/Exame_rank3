#ifndef VBC_H
#define VBC_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct	node {
	enum {
		ADD,
		MULTI,
		VAL} type;
		int	val;
		struct node	*l;
		struct node *r;
} node;

node    *new_node(node n);
void    unexpected(char c);
void    destroy_tree(node *n);
int accept(char **s, char c);
int expect(char **s, char c);
node	*add(char **s);
node	*multi(char **s);
node *digit(char **s);
node	*parse_expr(char *s);
int eval_tree(node *tree);

#endif