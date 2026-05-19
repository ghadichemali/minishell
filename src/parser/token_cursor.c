/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamade <hhamade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 05:16:04 by hhamade           #+#    #+#             */
/*   Updated: 2026/04/20 06:04:58 by hhamade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_toktype	peek(t_parser *p)
{
	if (p->error || !p->current)
		return (TK_EOF);
	return (p->current->type);
}

t_token	*consume(t_parser *p)
{
	t_token	*tok;

	if (p->error || !p->current)
		return (NULL);
	tok = p->current;
	p->current = p->current->next;
	return (tok);
}

int	expect(t_parser *p, t_toktype type)
{
	if (peek(p) != type)
	{
		if (type == TK_RPAREN)
			set_error(p, "syntax error: expected closing ')'");
		else
			set_error(p, "syntax error: unexpected token");
		return (0);
	}
	consume(p);
	return (1);
}

int	at_end(t_parser *p)
{
	t_toktype	t;

	t = peek(p);
	return (t == TK_EOF || t == TK_NEWLINE);
}
