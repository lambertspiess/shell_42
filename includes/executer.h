/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 15:53:09 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/24 23:56:30 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H
# include "lexer_struct.h"
# include "parser.h"
# include <stdio.h>
# include "minishell_structs.h"

/*
** executer.c
*/

void				execute_line(t_ast_node *astroot, t_ast_node *node);
void				launch(t_ast_node *astroot, t_ast_node *node, \
							t_cmd_info *io);
int					launch_host_bin(t_ast_node *astroot, t_ast_node *node, \
									t_cmd_info *io);

/*
** executer_get_io_filenames.c
*/

void				get_io_filenames(t_ast_node *astroot, t_cmd_info *io, \
									t_ast_node *node);

/*
** executer_pipeline.c
*/

void				execute_pipeline(t_ast_node *astroot, t_cmd_info io, \
								t_ast_node *node);
void				execute_command(t_ast_node *astroot, t_cmd_info io, \
								t_ast_node *node);
int					count_pipes(t_ast_node *node);

/*
** executer_io.c
*/

int					count_pipes(t_ast_node *node);
void				init_pipeline_fd(t_ast_node *node, int pipearr[]);
void				set_pipe_io_status(t_cmd_info *io, int statuscode, \
										int readfd, int writefd);
void				reset_io_streams(t_cmd_info *io, int in, int out, int err);
void				save_default_io(t_cmd_info *io);

/*
** set_io_streams.c
*/

void				set_io_streams(t_ast_node *astroot, t_cmd_info *io, \
								t_ast_node *node);

/*
** executer_free.c
*/

void				free_str_arr(char **arr);
void				free_env_list(t_env *env);
void				free_cmd_info(t_cmd_info *io);
void				free_cmd_av(t_cmd_info *io);

/*
** executer_get_cmd_av.c
*/

int					get_cmd_av(t_ast_node *astroot, t_cmd_info *io, \
								t_ast_node *node);
void				print_argv(t_cmd_info *io);

/*
** executer_check_dollar.c
*/

typedef struct				s_check_dollar_util {
	int				i;
	int				j;
	int				ret;
	char				buf[ARG_MAX];
}					t_check_dollar_util;

int					check_dollar(t_ast_node *astroot, t_cmd_info *io, \
									char **sp);

/*
** executer_check_dollar_utils.c
*/

int					get_key_length(char *s, int *ip);
void				get_exit_status(int *ip, int *jp, char *buf);
void				insert_special_char(int *ip, int *jp, char *s, char *buf);
void				swap_tok(t_ast_node *astroot, t_cmd_info *io, \
						char *buf, char **sp);

/*
** executer_get_env_strarray.c
*/

void				get_envstrarr(t_ast_node *astroot, t_cmd_info *io,
										t_env *env);

/*
** executer_get_pathstrarr.c
*/

void				get_pathstrarr(t_ast_node *astroot, t_cmd_info *io);

/*
** executer_get_cmd_execv.c
*/

void				executer_execve(t_ast_node *astroot, t_cmd_info *io);

/*
** executer_exit.c
*/

void				executer_exit_process(t_ast_node *astree, t_cmd_info *io, \
											int ret, int print);
void				get_exit_code(int process_status, int ret);

/*
** executer_errmsg.c
*/

void				errmsg_no_such_file_or_directory(char *pathcmd, char *file);
void				errmsg_command_not_found(char *cmd);

/*
** builtins
*/

int					execute_pwd(t_ast_node *astroot, t_ast_node *node, \
									t_cmd_info *io);
int					execute_env(t_ast_node *astroot, t_ast_node *node, \
									t_cmd_info *io);
int					execute_export(t_ast_node *astroot, t_ast_node *node, \
									t_cmd_info *io);
int					execute_unset(t_ast_node *astroot, t_ast_node *node, \
									t_cmd_info *io);
int					execute_echo(t_ast_node *astroot, t_ast_node *node, \
									t_cmd_info *io);
int					execute_cd(t_ast_node *astroot, t_ast_node *node, \
									t_cmd_info *io);
int					execute_exit(t_ast_node *astroot, t_ast_node *node, \
									t_cmd_info *io);

#endif
