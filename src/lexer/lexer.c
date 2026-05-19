/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamade <hhamade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:10:01 by gchemali          #+#    #+#             */
/*   Updated: 2026/04/20 06:01:37 by hhamade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token	*lexer(const char *line)
{
	t_token	*out;

	out = NULL;
	if (!line || !*line)
		return (NULL);
	if (!lex_scan(line, &out))
	{
		token_clear(&out);
		return (NULL);
	}
	return (out);
}
