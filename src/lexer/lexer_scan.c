/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_scan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchemali <gchemali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:09:35 by gchemali          #+#    #+#             */
/*   Updated: 2026/02/23 16:09:41 by gchemali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

bool	lex_scan(const char *s, t_token **out)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i = skip_spaces(s, i);
		if (!s[i])
			break ;
		if (s[i] == '|' || s[i] == '<' || s[i] == '>')
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
