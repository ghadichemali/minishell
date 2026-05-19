/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamade <hhamade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 05:59:05 by hhamade           #+#    #+#             */
/*   Updated: 2026/04/20 09:37:20 by hhamade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL,
	NODE_REDIR
}	t_node_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_node
{
	t_node_type		type;
	char			**args;
	int				argc;
	t_redir			*redirs;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_parser
{
	t_token	*current;
	int		error;
	char	*errmsg;
}	t_parser;

t_node			*parse(t_token *tokens);
void			free_ast(t_node *node);
void			print_ast(t_node *node, int depth);

t_toktype		peek(t_parser *p);
t_token			*consume(t_parser *p);
int				expect(t_parser *p, t_toktype type);
int				at_end(t_parser *p);

t_node			*parse_and_or(t_parser *p);
t_node			*parse_pipeline(t_parser *p);
t_node			*parse_simple_cmd(t_parser *p);
t_node			*parse_subshell(t_parser *p);
t_redir			*parse_redirection(t_parser *p);

t_node			*new_node(t_node_type type);
t_node			*new_binop(t_node_type type, t_node *left, t_node *right);
t_redir			*new_redir(t_redir_type type, char *file);
void			append_redir(t_node *node, t_redir *r);
int				append_arg(t_node *node, const char *word);

void			set_error(t_parser *p, const char *msg);

int				is_redir_token(t_toktype t);

#endif