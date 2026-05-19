/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamade <hhamade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 05:13:31 by hhamade           #+#    #+#             */
/*   Updated: 2026/04/20 06:05:33 by hhamade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static t_node	*wrap_subshell(t_parser *p, t_node *inner)
{
	t_node	*node;
	t_redir	*r;

	node = new_node(NODE_SUBSHELL);
	if (!node)
	{
		set_error(p, "fatal: memory allocation failed");
		return (free_ast(inner), NULL);
	}
	node->left = inner;
	while (!p->error && (peek(p) == TK_REDIR_IN || peek(p) == TK_REDIR_OUT
			|| peek(p) == TK_APPEND || peek(p) == TK_HEREDOC))
	{
		r = parse_redirection(p);
		if (!r)
			return (free_ast(node), NULL);
		append_redir(node, r);
	}
	return (node);
}

t_node	*parse_subshell(t_parser *p)
{
	t_node	*inner;

	consume(p);
	while (peek(p) == TK_NEWLINE)
		consume(p);
	if (peek(p) == TK_RPAREN)
	{
		set_error(p, "syntax error: empty subshell '( )'");
		return (NULL);
	}
	inner = parse_and_or(p);
	if (!inner || p->error)
		return (free_ast(inner), NULL);
	while (peek(p) == TK_NEWLINE)
		consume(p);
	if (!expect(p, TK_RPAREN))
		return (free_ast(inner), NULL);
	return (wrap_subshell(p, inner));
}
