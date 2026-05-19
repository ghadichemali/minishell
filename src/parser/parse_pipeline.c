/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamade <hhamade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 09:52:03 by hhamade           #+#    #+#             */
/*   Updated: 2026/04/20 09:52:08 by hhamade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static t_node	*parse_term(t_parser *p)
{
	if (peek(p) == TK_LPAREN)
		return (parse_subshell(p));
	return (parse_simple_cmd(p));
}

t_node	*parse_pipeline(t_parser *p)
{
	t_node	*left;
	t_node	*right;

	left = parse_term(p);
	if (!left || p->error)
		return (left);
	while (peek(p) == TK_PIPE)
	{
		consume(p);
		while (peek(p) == TK_NEWLINE)
			consume(p);
		if (at_end(p) || peek(p) == TK_PIPE)
		{
			set_error(p, "syntax error near unexpected token '|'");
			return (free_ast(left), NULL);
		}
		right = parse_term(p);
		if (!right || p->error)
			return (free_ast(left), NULL);
		left = new_binop(NODE_PIPE, left, right);
		if (!left)
			return (set_error(p, "fatal: memory allocation failed"), NULL);
	}
	return (left);
}

static t_node_type	op_to_nodetype(t_toktype op)
{
	if (op == TK_AND)
		return (NODE_AND);
	return (NODE_OR);
}

static t_node	*and_or_step(t_parser *p, t_node *left)
{
	t_node		*right;
	t_node_type	ntype;

	ntype = op_to_nodetype(peek(p));
	consume(p);
	while (peek(p) == TK_NEWLINE)
		consume(p);
	if (at_end(p))
	{
		set_error(p, "syntax error: unexpected end of input");
		return (free_ast(left), NULL);
	}
	right = parse_pipeline(p);
	if (!right || p->error)
		return (free_ast(left), NULL);
	left = new_binop(ntype, left, right);
	if (!left)
		return (set_error(p, "fatal: memory allocation failed"), NULL);
	return (left);
}

t_node	*parse_and_or(t_parser *p)
{
	t_node	*left;

	left = parse_pipeline(p);
	if (!left || p->error)
		return (left);
	while (peek(p) == TK_AND || peek(p) == TK_OR)
	{
		left = and_or_step(p, left);
		if (!left || p->error)
			return (left);
	}
	return (left);
}
