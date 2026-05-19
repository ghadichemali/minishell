/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamade <hhamade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 05:13:55 by hhamade           #+#    #+#             */
/*   Updated: 2026/04/20 06:05:48 by hhamade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	set_error(t_parser *p, const char *msg)
{
	if (!p->error)
	{
		p->error = 1;
		p->errmsg = (char *)msg;
	}
}

t_node	*new_node(t_node_type type)
{
	t_node	*n;

	n = (t_node *)malloc(sizeof(t_node));
	if (!n)
		return (NULL);
	n->type = type;
	n->args = NULL;
	n->argc = 0;
	n->redirs = NULL;
	n->left = NULL;
	n->right = NULL;
	return (n);
}

t_node	*new_binop(t_node_type type, t_node *left, t_node *right)
{
	t_node	*n;

	n = new_node(type);
	if (!n)
	{
		free_ast(left);
		free_ast(right);
		return (NULL);
	}
	n->left = left;
	n->right = right;
	return (n);
}
