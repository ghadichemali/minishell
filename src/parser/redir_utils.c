/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamade <hhamade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 05:14:32 by hhamade           #+#    #+#             */
/*   Updated: 2026/04/20 09:35:32 by hhamade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_redir	*new_redir(t_redir_type type, char *file)
{
	t_redir	*r;

	r = (t_redir *)malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = type;
	r->file = strdup(file);
	if (!r->file)
	{
		free(r);
		return (NULL);
	}
	r->next = NULL;
	return (r);
}

void	append_redir(t_node *node, t_redir *r)
{
	t_redir	*cur;

	if (!node->redirs)
	{
		node->redirs = r;
		return ;
	}
	cur = node->redirs;
	while (cur->next)
		cur = cur->next;
	cur->next = r;
}

int	append_arg(t_node *node, const char *word)
{
	char	**new_args;
	char	*dup;

	dup = strdup(word);
	if (!dup)
		return (0);
	new_args = (char **)realloc(node->args,
			sizeof(char *) * (node->argc + 2));
	if (!new_args)
	{
		free(dup);
		return (0);
	}
	node->args = new_args;
	node->args[node->argc] = dup;
	node->argc++;
	node->args[node->argc] = NULL;
	return (1);
}

int	is_redir_token(t_toktype t)
{
	return (t == TK_REDIR_IN || t == TK_REDIR_OUT
		|| t == TK_APPEND || t == TK_HEREDOC);
}
