/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamade <hhamade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:09:48 by gchemali          #+#    #+#             */
/*   Updated: 2026/04/20 06:01:22 by hhamade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static int	skip_quoted(const char *s, int i, char quote)
{
	i++;
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote)
		i++;
	return (i);
}

static int	get_word_end(const char *s, int i)
{
	while (s[i] && s[i] != ' ' && s[i] != '\t'
		&& s[i] != '|' && s[i] != '<' && s[i] != '>'
		&& s[i] != '&' && s[i] != '(' && s[i] != ')')
	{
		if (s[i] == '\'' || s[i] == '"')
			i = skip_quoted(s, i, s[i]);
		else
			i++;
	}
	return (i);
}

bool	lex_word(const char *s, int *i, t_token **out)
{
	int		start;
	int		end;
	char	*val;
	t_token	*tok;

	start = *i;
	end = get_word_end(s, start);
	if (end == start)
		return (false);
	val = ft_substr(s, start, end - start);
	if (!val)
		return (false);
	tok = token_new(TK_WORD, val);
	if (!tok)
	{
		free(val);
		return (false);
	}
	token_add_back(out, tok);
	*i = end;
	return (true);
}
