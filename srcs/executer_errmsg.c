/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_errmsg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:14:02 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/11 18:23:24 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		errmsg_no_such_file_or_directory(char *pathcmd, char *file)
{
	ft_printf_fd(STDERR_FILENO, "minishell");
	if (pathcmd)
		ft_printf_fd(STDERR_FILENO, ": %s", pathcmd);
	if (file)
		ft_printf_fd(STDERR_FILENO, ": %s", file);
	ft_printf_fd(STDERR_FILENO, ": No such file or directory\n");
}

void		errmsg_command_not_found(char *cmd)
{
	ft_printf_fd(STDERR_FILENO, "minishell: command not found : %s\n", cmd);
}
