/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamade <hhamade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 06:01:55 by hhamade           #+#    #+#             */
/*   Updated: 2026/04/20 06:01:59 by hhamade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "../includes/parser.h"

static void	run_line(char *line)
{
	t_token	*tokens;
	t_node	*ast;

	tokens = lexer(line);
	if (!tokens)
		return ;
	printf("=== tokens ===\n");
	token_print(tokens);
	ast = parse(tokens);
	if (ast)
	{
		printf("=== AST ===\n");
		print_ast(ast, 0);
		free_ast(ast);
	}
	token_clear(&tokens);
}

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
		{
			add_history(line);
			run_line(line);
		}
		free(line);
	}
	return (0);
}
