/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_scan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamade <hhamade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:09:35 by gchemali          #+#    #+#             */
/*   Updated: 2026/04/20 06:00:06 by hhamade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static bool	is_op_char(char c)
{
	return (c == '|' || c == '<' || c == '>'
		|| c == '&' || c == '(' || c == ')');
}

bool	lex_scan(const char *s, t_token **out)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i = skip_spaces(s, i);
		if (!s[i])
			break ;
		if (is_op_char(s[i]))
		{
			if (!lex_op(s, &i, out))
				return (false);
		}
		else
		{
			if (!lex_word(s, &i, out))
				return (false);
		}
	}
	return (true);
}
