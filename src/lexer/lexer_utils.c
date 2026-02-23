/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchemali <gchemali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:32:52 by gchemali          #+#    #+#             */
/*   Updated: 2026/02/23 16:06:54 by gchemali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	skip_spaces(const char *s, int i)
{
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (i);
}

//allocate a new token
//initialize tok->next to Null to always get the last node = null
t_token	*token_new(t_toktype type, char *value)
{
	t_token	*tok;

	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = value;
	tok->next = NULL;
	return (tok);
}

//add a new token to the tail of the list
void	token_add_back(t_token **lst, t_token *new_token)
{
	t_token	*cur;

	if (!lst || !new_token)
		return ;
	if (!*lst)
	{
		*lst = new_token;
		return ;
	}
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new_token;
}

//free token
void	token_clear(t_token **lst)
{
	t_token	*cur;
	t_token	*next;

	if (!lst)
		return ;
	cur = *lst;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur->value);
		free(cur);
		cur = next;
	}
	*lst = NULL;
}
