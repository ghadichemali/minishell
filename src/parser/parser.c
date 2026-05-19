/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamade <hhamade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 05:26:39 by hhamade           #+#    #+#             */
/*   Updated: 2026/04/20 06:05:29 by hhamade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	skip_newlines(t_parser *p)
{
	while (p->current && p->current->type == TK_NEWLINE)
		p->current = p->current->next;
}

static const char	*safe_value(t_parser *p)
{
	if (p->current->value)
		return (p->current->value);
	return ("");
}

static int	check_trailing(t_parser *p, t_node **tree)
{
	if (!at_end(p))
	{
		fprintf(stderr,
			"minishell: syntax error near unexpected token '%s'\n",
			safe_value(p));
		free_ast(*tree);
		*tree = NULL;
		return (0);
	}
	return (1);
}

static void	print_error(t_parser *p)
{
	if (p->errmsg)
		fprintf(stderr, "minishell: %s\n", p->errmsg);
	else
		fprintf(stderr, "minishell: syntax error\n");
}

t_node	*parse(t_token *tokens)
{
	t_parser	p;
	t_node		*tree;

	if (!tokens)
		return (NULL);
	p.current = tokens;
	p.error = 0;
	p.errmsg = NULL;
	skip_newlines(&p);
	if (!p.current || p.current->type == TK_EOF)
		return (NULL);
	tree = parse_and_or(&p);
	if (p.error)
	{
		print_error(&p);
		free_ast(tree);
		return (NULL);
	}
	if (!check_trailing(&p, &tree))
		return (NULL);
	return (tree);
}
