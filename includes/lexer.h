/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchemali <gchemali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:51:14 by gchemali          #+#    #+#             */
/*   Updated: 2026/02/23 16:16:33 by gchemali         ###   ########.fr       */
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
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_APPEND,
	TK_HEREDOC,
}	t_toktype;

typedef struct s_token
{
	t_toktype		type;
	char			*value;
	struct s_token	*next;
}	t_token;

//public
t_token	*lexer(const char *line);
void	token_clear(t_token **lst);

//scan
bool	lex_scan(const char *s, t_token **out);

//ops
bool	lex_op(const char *s, int *i, t_token **out);

//word
bool	lex_word(const char *s, int *i, t_token **out);

//utils
int		skip_spaces(const char *s, int i);
t_token	*token_new(t_toktype type, char *value);
void	token_add_back(t_token **lst, t_token *new_token);

#endif