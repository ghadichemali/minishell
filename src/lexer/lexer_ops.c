/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamade <hhamade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 09:51:09 by hhamade           #+#    #+#             */
/*   Updated: 2026/04/20 09:56:47 by hhamade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static bool	handle_pipe_ops(const char *s, int *i, t_token **out)
{
	if (s[*i] != '|')
		return (false);
	if (s[*i + 1] == '|')
	{
		if (!push_op(out, TK_OR, "||"))
			return (false);
		(*i) += 2;
		return (true);
	}
	if (!push_op(out, TK_PIPE, "|"))
		return (false);
	(*i) += 1;
	return (true);
}

static bool	handle_in_ops(const char *s, int *i, t_token **out)
{
	if (s[*i] != '<')
		return (false);
	if (s[*i + 1] == '<')
	{
		if (!push_op(out, TK_HEREDOC, "<<"))
			return (false);
		(*i) += 2;
		return (true);
	}
	if (!push_op(out, TK_REDIR_IN, "<"))
		return (false);
	(*i) += 1;
	return (true);
}

static bool	handle_out_ops(const char *s, int *i, t_token **out)
{
	if (s[*i] != '>')
		return (false);
	if (s[*i + 1] == '>')
	{
		if (!push_op(out, TK_APPEND, ">>"))
			return (false);
		(*i) += 2;
		return (true);
	}
	if (!push_op(out, TK_REDIR_OUT, ">"))
		return (false);
	(*i) += 1;
	return (true);
}

static bool	handle_paren_ops(const char *s, int *i, t_token **out)
{
	if (s[*i] == '(')
	{
		if (!push_op(out, TK_LPAREN, "("))
			return (false);
		(*i) += 1;
		return (true);
	}
	if (s[*i] == ')')
	{
		if (!push_op(out, TK_RPAREN, ")"))
			return (false);
		(*i) += 1;
		return (true);
	}
	return (false);
}

bool	lex_op(const char *s, int *i, t_token **out)
{
	if (s[*i] == '&' && s[*i + 1] == '&')
	{
		if (!push_op(out, TK_AND, "&&"))
			return (false);
		(*i) += 2;
		return (true);
	}
	if (handle_paren_ops(s, i, out))
		return (true);
	if (handle_pipe_ops(s, i, out))
		return (true);
	if (handle_in_ops(s, i, out))
		return (true);
	if (handle_out_ops(s, i, out))
		return (true);
	return (false);
}
