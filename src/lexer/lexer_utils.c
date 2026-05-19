/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamade <hhamade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:32:52 by gchemali          #+#    #+#             */
/*   Updated: 2026/04/20 09:57:03 by hhamade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	skip_spaces(const char *s, int i)
{
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (i);
}

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

bool	push_op(t_token **out, t_toktype type, const char *s)
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
