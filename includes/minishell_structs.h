/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 15:55:56 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/30 08:09:12 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "lexer_struct.h"

typedef enum			s_node_type {
						SEMICOLON,
						PIPE,
						REDIR_INPUT,
						REDIR_OUTPUT,
						REDIR_APPEND,
						REDIR_INPUT_AND_OUTPUT,
						REDIR_INPUT_AND_APPEND,
						EXECNAME,
						ARG,
}						t_node_type ;

typedef struct			s_ast_node {
	int					type;
	char				*data;
	char				*data2;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

typedef struct			s_env {
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct			s_static {
	t_env				*env;
	int				stoprdline;
	char				*line;
	char				*tmp;
	char				*swap;
	int					exitcode;
	int					busy_executing;
	t_ast_node			*astroot;
	t_lexical_list		lex;
	int					default_fd[3];
}						t_static;

typedef struct			s_cmd_info {
	int					ac;
	char				**av;
	char				**envstrarr;
	char				**pathstrarr;
	t_ast_node			*cmdnode;
	int					reads_input_from_pipe;
	int					writes_output_to_pipe;
	int					pipe_write_fd;
	int					pipe_read_fd;
	int					input_fd;
	int					output_fd;
	char				*input_file_name;
	char				*output_file_name;
	int					default_fd[3];
}						t_cmd_info;

typedef struct			s_builtin_tab {
	char				*execname;
	int					(*execute_exec)(t_ast_node *astroot, \
											t_ast_node *node, t_cmd_info *io);
}						t_builtin_tab;

#endif
