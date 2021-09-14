/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 16:50:53 by lspiess           #+#    #+#             */
/*   Updated: 2020/07/01 15:10:57 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** OSX includes
** 
** # include <sys/syslimits.h>
** # include <sys/errno.h>
** # include <sys/wait.h>
** # include "libft.h"
** # include "ft_printf.h"
** # include "minishell_structs.h"
** # include "lexer.h"
** # include "parser.h"
** # include "executer.h"
** # include <sys/types.h>
*/


// Salty's VM includes

# define ARG_MAX 4096
# define PATH_MAX 4096

# include "libft.h"
# include <sys/errno.h>
# include <sys/wait.h>
# include "ft_printf.h"
# include "minishell_structs.h"
# include "lexer.h"
# include "parser.h"
# include "executer.h"
# include <sys/types.h>
 

int					reset_stat();
t_static			*getstat(void);

void				env_init(char **envp);
void				env_free(void);
void				free_env_list_and_exit(\
					t_env **envpp, char *errmsg, int ret);

void				free_ast(t_ast_node *node);
void				free_toklist(t_tok *list);

void				print_io_status(t_cmd_info *io);
void				ft_print_type(int type);

#endif
