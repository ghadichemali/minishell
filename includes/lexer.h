/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamade <hhamade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:51:14 by gchemali          #+#    #+#             */
/*   Updated: 2026/04/20 09:57:19 by hhamade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdio.h> //for printf
# include <stdlib.h> //for free
# include <readline/readline.h>  //for readline()
# include <readline/history.h>  //for add_history()
# include <sys/types.h> //for pid_t
# include <unistd.h> //for fork() and execve()
# include <sys/wait.h> //for wait, waitpid
# include <stdbool.h> //for boolean
# include "../libft/libft.h"

typedef enum e_toktype
{
	TK_WORD,
	TK_PIPE,
	TK_AND,
	TK_OR,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_APPEND,
	TK_HEREDOC,
	TK_LPAREN,
	TK_RPAREN,
	TK_NEWLINE,
	TK_EOF
}	t_toktype;

typedef struct s_token
{
	t_toktype		type;
	char			*value;
	struct s_token	*next;
}	t_token;

t_token	*lexer(const char *line);
bool	lex_scan(const char *s, t_token **out);
bool	lex_op(const char *s, int *i, t_token **out);
bool	lex_word(const char *s, int *i, t_token **out);

int		skip_spaces(const char *s, int i);
t_token	*token_new(t_toktype type, char *value);
void	token_add_back(t_token **lst, t_token *new_token);
void	token_clear(t_token **lst);
void	token_print(t_token *lst);
bool	push_op(t_token **out, t_toktype type, const char *s);

#endif