/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_AST.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamade <hhamade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 05:16:50 by hhamade           #+#    #+#             */
/*   Updated: 2026/04/20 06:05:25 by hhamade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	print_redirs(t_redir *r, int depth)
{
	const char	*s;

	while (r)
	{
		s = "REDIR_IN";
		if (r->type == REDIR_OUT)
			s = "REDIR_OUT";
		else if (r->type == REDIR_APPEND)
			s = "REDIR_APPEND";
		else if (r->type == REDIR_HEREDOC)
			s = "REDIR_HEREDOC";
		printf("%*s[%s] \"%s\"\n", depth * 4, "", s, r->file);
		r = r->next;
	}
}

static void	print_cmd(t_node *node, int depth)
{
	int	i;

	printf("%*sNODE_CMD  args=[", depth * 4, "");
	i = 0;
	while (node->args && node->args[i])
	{
		printf("\"%s\"", node->args[i]);
		if (node->args[i + 1])
			printf(", ");
		i++;
	}
	printf("]\n");
	print_redirs(node->redirs, depth + 1);
}

static void	print_binop(t_node *node, int depth)
{
	if (node->type == NODE_PIPE)
		printf("%*sNODE_PIPE\n", depth * 4, "");
	else if (node->type == NODE_AND)
		printf("%*sNODE_AND\n", depth * 4, "");
	else
		printf("%*sNODE_OR\n", depth * 4, "");
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}

void	print_ast(t_node *node, int depth)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD)
		print_cmd(node, depth);
	else if (node->type == NODE_SUBSHELL)
	{
		printf("%*sNODE_SUBSHELL\n", depth * 4, "");
		print_redirs(node->redirs, depth + 1);
		print_ast(node->left, depth + 1);
	}
	else
		print_binop(node, depth);
}
