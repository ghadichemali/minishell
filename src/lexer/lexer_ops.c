/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchemali <gchemali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:07:05 by gchemali          #+#    #+#             */
/*   Updated: 2026/02/23 16:06:46 by gchemali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static bool	push_op(t_token **out, t_toktype type, const char *s)
{
	t_token	*tok;
	char	*val;

	val = ft_strdup(s);
	if (!val)
		return (false);
	tok = token_new(type, val);
	if (!tok)
	{
		free(val);
		return (false);
	}
	token_add_back(out, tok);
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

bool	lex_op(const char *s, int *i, t_token **out)
{
	if (s[*i] == '|')
	{
		if (!push_op(out, TK_PIPE, "|"))
			return (false);
		(*i)++;
		return (true);
	}
	if (handle_in_ops(s, i, out))
		return (true);
	if (handle_out_ops(s, i, out))
		return (true);
	return (false);
}
