/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamade <hhamade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 05:12:41 by hhamade           #+#    #+#             */
/*   Updated: 2026/04/20 09:35:10 by hhamade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static t_redir_type	token_to_redir(t_toktype t)
{
	if (t == TK_REDIR_IN)
		return (REDIR_IN);
	if (t == TK_REDIR_OUT)
		return (REDIR_OUT);
	if (t == TK_APPEND)
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}

t_redir	*parse_redirection(t_parser *p)
{
	t_toktype	op_type;
	t_token		*file_tok;
	t_redir		*r;

	op_type = peek(p);
	consume(p);
	if (peek(p) != TK_WORD)
	{
		set_error(p, "syntax error: expected filename after redirection");
		return (NULL);
	}
	file_tok = consume(p);
	r = new_redir(token_to_redir(op_type), file_tok->value);
	if (!r)
		set_error(p, "fatal: memory allocation failed");
	return (r);
}

static int	handle_word(t_parser *p, t_node *node)
{
	if (!append_arg(node, consume(p)->value))
	{
		set_error(p, "fatal: memory allocation failed");
		return (0);
	}
	return (1);
}

static int	handle_redir(t_parser *p, t_node *node)
{
	t_redir	*r;

	r = parse_redirection(p);
	if (!r)
		return (0);
	append_redir(node, r);
	return (1);
}

t_node	*parse_simple_cmd(t_parser *p)
{
	t_node	*node;
	int		found;

	node = new_node(NODE_CMD);
	if (!node)
		return (set_error(p, "fatal: memory allocation failed"), NULL);
	found = 0;
	while (!p->error)
	{
		if (peek(p) == TK_WORD)
			found = handle_word(p, node);
		else if (is_redir_token(peek(p)))
			found = handle_redir(p, node);
		else
			break ;
		if (!found)
			return (free_ast(node), NULL);
		found = 1;
	}
	if (!node->argc && !node->redirs)
	{
		set_error(p, "syntax error near unexpected token");
		return (free_ast(node), NULL);
	}
	return (node);
}
