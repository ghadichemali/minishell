/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamade <hhamade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 09:51:32 by hhamade           #+#    #+#             */
/*   Updated: 2026/04/20 09:51:37 by hhamade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static const char	*toktype_str(t_toktype type)
{
	if (type == TK_WORD)
		return ("WORD");
	if (type == TK_PIPE)
		return ("PIPE");
	if (type == TK_AND)
		return ("AND");
	if (type == TK_OR)
		return ("OR");
	if (type == TK_REDIR_IN)
		return ("REDIR_IN");
	if (type == TK_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == TK_APPEND)
		return ("APPEND");
	if (type == TK_HEREDOC)
		return ("HEREDOC");
	if (type == TK_LPAREN)
		return ("LPAREN");
	if (type == TK_RPAREN)
		return ("RPAREN");
	if (type == TK_NEWLINE)
		return ("NEWLINE");
	return ("EOF");
}

static const char	*safe_val(t_token *cur)
{
	if (cur->value)
		return (cur->value);
	return ("");
}

void	token_print(t_token *lst)
{
	t_token	*cur;

	cur = lst;
	while (cur)
	{
		printf("[%-10s] \"%s\"\n", toktype_str(cur->type), safe_val(cur));
		cur = cur->next;
	}
}
