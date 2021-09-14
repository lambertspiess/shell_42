/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 19:09:31 by lspiess           #+#    #+#             */
/*   Updated: 2020/07/01 16:55:51 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(void)
{
	getstat()->stoprdline = 1;
	free_ast(getstat()->astroot);
	free_toklist(getstat()->lex.tok);
	getstat()->astroot = NULL;
	ft_free((void **)&(getstat()->tmp));
	ft_free((void **)&(getstat()->swap));
	ft_free((void **)&(getstat()->line));
	getstat()->exitcode = 130;
	write(STDOUT_FILENO, "\n", 1);
	if (getstat()->busy_executing == 1)
		getstat()->busy_executing = 0;
	else
		ft_printf_fd(STDOUT_FILENO,
			ANSI_COLOR_RED"minishell42%%> "ANSI_COLOR_RESET);
}

static void	catch_signal(int sigval)
{
	if (sigval == SIGINT)
		handle_sigint();
	else if (sigval == SIGQUIT)
	{
		getstat()->exitcode = 131;
		if (getstat()->busy_executing)
		{
			ft_putstr("Quit: 3\n");
			getstat()->busy_executing = 0;
		}
		else
			ft_putstr("\b\b  \b\b");
	}
}

static void	stat_bzero(int ac, char **av)
{
	t_static			*stat;

	(void)(ac);
	(void)(av);
	stat = getstat();
	ft_bzero(stat, sizeof(t_static));
	getstat()->default_fd[0] = dup(STDIN_FILENO);
	getstat()->default_fd[1] = dup(STDOUT_FILENO);
	getstat()->default_fd[2] = dup(STDERR_FILENO);
}

static void	readline_routine(void)
{
	int			ret;

	getstat()->line = NULL;
	while (1)
	{
		getstat()->tmp = NULL;
		if ((ret = get_next_line(&(getstat()->tmp), 1)) == 0)
			write(STDOUT_FILENO, "  \b\b", 4);
		getstat()->swap = ft_strjoin(getstat()->line, getstat()->tmp);
		ft_free((void **)(&(getstat()->tmp)));
		ft_free((void **)(&getstat()->line));
		getstat()->line = ft_strdup(getstat()->swap);
		ft_free((void **)(&(getstat()->swap)));
		if ((!getstat()->line || ft_istrlen(getstat()->line) == 0) && ret == 0)
		{
			ft_free((void **)(&(getstat()->line)));
			free_env_list(getstat()->env);
			ft_printf("exit\n");
			exit(0);
		}
		if (ret != 0)
			break ;
	}
	getstat()->stoprdline = 0;
}

int			main(int ac, char **av, char **envp)
{
	signal(SIGINT, catch_signal);
	signal(SIGQUIT, catch_signal);
	stat_bzero(ac, av);
	env_init(envp);
	while (reset_stat())
	{
		readline_routine();
		if (ft_istrlen(getstat()->line) == 0 || getstat()->stoprdline == 1)
			continue ;
		tokenize_line(getstat()->line, &(getstat()->lex),
				ft_istrlen(getstat()->line));
		ft_free((void **)(&(getstat()->line)));
		getstat()->astroot = parse_tokens(&(getstat()->lex));
		free_toklist(getstat()->lex.tok);
		getstat()->lex.tok = NULL;
		execute_line(getstat()->astroot, getstat()->astroot);
		free_ast(getstat()->astroot);
	}
	free_env_list(getstat()->env);
	return (getstat()->exitcode);
}
