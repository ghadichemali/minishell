/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamade <hhamade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 05:30:51 by hhamade           #+#    #+#             */
/*   Updated: 2026/04/20 06:06:52 by hhamade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdio.h>

static int	g_passed = 0;
static int	g_failed = 0;

static t_token	*mk_tok(t_toktype type, const char *val)
{
	t_token	*t;

	t = malloc(sizeof(t_token));
	t->type = type;
	t->value = val ? strdup(val) : NULL;
	t->next = NULL;
	return (t);
}

static void	chain(t_token **toks, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		toks[i]->next = toks[i + 1];
		i++;
	}
}

static void	free_tokens(t_token *t)
{
	t_token	*next;

	while (t)
	{
		next = t->next;
		free(t->value);
		free(t);
		t = next;
	}
}

static void	check(const char *label, t_node *result, int expect_ok)
{
	if (expect_ok && result)
	{
		printf("  \033[32mOK\033[0m  %s\n", label);
		print_ast(result, 2);
		free_ast(result);
		g_passed++;
	}
	else if (!expect_ok && !result)
	{
		printf("  \033[32mOK\033[0m  %s (correctly rejected)\n", label);
		g_passed++;
	}
	else
	{
		printf("  \033[31mKO\033[0m  %s\n", label);
		if (result)
			free_ast(result);
		g_failed++;
	}
	printf("\n");
}

static void	test_simple_cmd(void)
{
	t_token	*toks[3];

	printf("-- simple command\n");
	toks[0] = mk_tok(TK_WORD, "echo");
	toks[1] = mk_tok(TK_WORD, "hello");
	toks[2] = mk_tok(TK_EOF, NULL);
	chain(toks, 3);
	check("echo hello", parse(toks[0]), 1);
	free_tokens(toks[0]);
}

static void	test_redirections(void)
{
	t_token	*toks[6];

	printf("-- redirections\n");
	toks[0] = mk_tok(TK_WORD, "cat");
	toks[1] = mk_tok(TK_REDIR_IN, "<");
	toks[2] = mk_tok(TK_WORD, "in.txt");
	toks[3] = mk_tok(TK_REDIR_OUT, ">");
	toks[4] = mk_tok(TK_WORD, "out.txt");
	toks[5] = mk_tok(TK_EOF, NULL);
	chain(toks, 6);
	check("cat < in.txt > out.txt", parse(toks[0]), 1);
	free_tokens(toks[0]);
}

static void	test_pipeline(void)
{
	t_token	*toks[8];

	printf("-- pipeline\n");
	toks[0] = mk_tok(TK_WORD, "ls");
	toks[1] = mk_tok(TK_PIPE, "|");
	toks[2] = mk_tok(TK_WORD, "grep");
	toks[3] = mk_tok(TK_WORD, ".c");
	toks[4] = mk_tok(TK_PIPE, "|");
	toks[5] = mk_tok(TK_WORD, "wc");
	toks[6] = mk_tok(TK_WORD, "-l");
	toks[7] = mk_tok(TK_EOF, NULL);
	chain(toks, 8);
	check("ls | grep .c | wc -l", parse(toks[0]), 1);
	free_tokens(toks[0]);
}

static void	test_and_or(void)
{
	t_token	*toks[9];

	printf("-- && and ||\n");
	toks[0] = mk_tok(TK_WORD, "echo");
	toks[1] = mk_tok(TK_WORD, "a");
	toks[2] = mk_tok(TK_AND, "&&");
	toks[3] = mk_tok(TK_WORD, "echo");
	toks[4] = mk_tok(TK_WORD, "b");
	toks[5] = mk_tok(TK_OR, "||");
	toks[6] = mk_tok(TK_WORD, "echo");
	toks[7] = mk_tok(TK_WORD, "c");
	toks[8] = mk_tok(TK_EOF, NULL);
	chain(toks, 9);
	check("echo a && echo b || echo c", parse(toks[0]), 1);
	free_tokens(toks[0]);
}

static void	test_subshell(void)
{
	t_token	*toks[7];

	printf("-- subshell with redir\n");
	toks[0] = mk_tok(TK_LPAREN, "(");
	toks[1] = mk_tok(TK_WORD, "echo");
	toks[2] = mk_tok(TK_WORD, "hi");
	toks[3] = mk_tok(TK_RPAREN, ")");
	toks[4] = mk_tok(TK_REDIR_OUT, ">");
	toks[5] = mk_tok(TK_WORD, "out.txt");
	toks[6] = mk_tok(TK_EOF, NULL);
	chain(toks, 7);
	check("( echo hi ) > out.txt", parse(toks[0]), 1);
	free_tokens(toks[0]);
}

static void	test_heredoc(void)
{
	t_token	*toks[4];

	printf("-- heredoc\n");
	toks[0] = mk_tok(TK_WORD, "cat");
	toks[1] = mk_tok(TK_HEREDOC, "<<");
	toks[2] = mk_tok(TK_WORD, "EOF");
	toks[3] = mk_tok(TK_EOF, NULL);
	chain(toks, 4);
	check("cat << EOF", parse(toks[0]), 1);
	free_tokens(toks[0]);
}

static void	test_err_trailing_pipe(void)
{
	t_token	*toks[3];

	printf("-- error: trailing pipe\n");
	toks[0] = mk_tok(TK_WORD, "ls");
	toks[1] = mk_tok(TK_PIPE, "|");
	toks[2] = mk_tok(TK_EOF, NULL);
	chain(toks, 3);
	check("ls | (should fail)", parse(toks[0]), 0);
	free_tokens(toks[0]);
}

static void	test_err_empty_subshell(void)
{
	t_token	*toks[3];

	printf("-- error: empty subshell\n");
	toks[0] = mk_tok(TK_LPAREN, "(");
	toks[1] = mk_tok(TK_RPAREN, ")");
	toks[2] = mk_tok(TK_EOF, NULL);
	chain(toks, 3);
	check("( ) (should fail)", parse(toks[0]), 0);
	free_tokens(toks[0]);
}

static void	test_err_redir_no_file(void)
{
	t_token	*toks[3];

	printf("-- error: redir missing filename\n");
	toks[0] = mk_tok(TK_WORD, "echo");
	toks[1] = mk_tok(TK_REDIR_OUT, ">");
	toks[2] = mk_tok(TK_EOF, NULL);
	chain(toks, 3);
	check("echo > (should fail)", parse(toks[0]), 0);
	free_tokens(toks[0]);
}

int	main(void)
{
	printf("\nminishell parser -- test suite\n\n");
	test_simple_cmd();
	test_redirections();
	test_pipeline();
	test_and_or();
	test_subshell();
	test_heredoc();
	test_err_trailing_pipe();
	test_err_empty_subshell();
	test_err_redir_no_file();
	printf("--------------------------------------------\n");
	printf("Results: \033[32m%d passed\033[0m", g_passed);
	if (g_failed)
		printf("  \033[31m%d failed\033[0m", g_failed);
	printf("\n\n");
	return (g_failed > 0 ? 1 : 0);
}
