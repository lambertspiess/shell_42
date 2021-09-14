/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 12:08:30 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/28 14:26:17 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*find_home(void)
{
	t_env			*head;

	head = getstat()->env;
	while (head)
	{
		if (ft_strequ(head->key, "HOME"))
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

static int		update_in_env(char *key, char *value)
{
	t_env			*head;
	t_env			*prev;

	if (!value)
		return (0);
	head = getstat()->env;
	prev = head;
	while (head)
	{
		if (ft_strequ(head->key, key))
		{
			free(head->value);
			if (!(head->value = ft_strdup(value)))
				return (errno);
			return (0);
		}
		prev = head;
		head = head->next;
	}
	if (!(prev->next = ft_memalloc(sizeof(t_env))) \
		|| !(prev->next->key == ft_strdup(key)) \
		|| !(prev->next->value = ft_strdup(value)))
		return (errno);
	return (0);
}

static int		change_directory(t_cmd_info *io)
{
	char			cwd[PATH_MAX];
	int				ret;

	if (update_in_env("OLDPWD", getcwd(cwd, sizeof(cwd))) != 0)
		return (errno);
	if (ft_strequ(io->av[1], "~"))
		ret = chdir(find_home());
	else
		ret = chdir(io->av[1]);
	if (ret == -1)
	{
		ft_printf_fd(STDERR_FILENO,
			"minishell: cd: %s: No such file or directory\n", io->av[1]);
		return (EXIT_FAILURE);
	}
	else
	{
		getcwd(cwd, sizeof(cwd));
		if ((char *)(cwd) == NULL)
			ft_printf_fd(2, "minishell: cd: error\n");
		if (update_in_env("PWD", getcwd(cwd, sizeof(cwd))) != 0)
			return (errno);
	}
	return (EXIT_SUCCESS);
}

int				execute_cd(t_ast_node *astroot, t_ast_node *node, \
								t_cmd_info *io)
{
	char			oldpwd[PATH_MAX];

	(void)(astroot);
	(void)(node);
	if (io->ac == 1)
	{
		if (update_in_env("OLDPWD", getcwd(oldpwd, sizeof(oldpwd))) != 0)
			return (errno);
		chdir("/");
		return (update_in_env("PWD", "/"));
	}
	else if (io->ac > 2)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	else if (ft_istrlen(io->av[1]) > PATH_MAX)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: cd: File name too long\n");
		return (EXIT_FAILURE);
	}
	return (change_directory(io));
}
