/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_get_envstrarr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 09:37:40 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/18 17:40:51 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		envcount(t_env *env)
{
	int				i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static void		build_env_string_pairs(t_ast_node *astroot, t_cmd_info *io,
										t_env *env)
{
	char			*to_free;
	int				i;

	i = 0;
	while (env)
	{
		if (!(to_free = ft_strjoin(env->key, "=")))
			executer_exit_process(astroot, io, errno, 1);
		if (env->value)
		{
			if (!(io->envstrarr[i] = ft_strjoin(to_free, env->value)))
				executer_exit_process(astroot, io, errno, 1);
		}
		else
		{
			if (!(io->envstrarr[i] = ft_strdup(to_free)))
				executer_exit_process(astroot, io, errno, 1);
		}
		free(to_free);
		to_free = 0;
		i++;
		env = env->next;
	}
}

void			print_cmd_env(t_cmd_info *io)
{
	int				i;

	if (!(io->envstrarr))
	{
		ft_printf("io->envstrarr = %p\n", io->envstrarr);
		return ;
	}
	i = 0;
	while (io->envstrarr[i])
	{
		ft_printf("io->envstrarr[%d] = %s\n", i, io->envstrarr[i]);
		i++;
	}
}

void			get_envstrarr(t_ast_node *astroot, t_cmd_info *io,
										t_env *env)
{
	int				count;

	if ((count = envcount(env)) == 0)
		return ;
	if (!(io->envstrarr = ft_memalloc(sizeof(char *) * (count + 1))))
		executer_exit_process(astroot, io, errno, 1);
	build_env_string_pairs(astroot, io, env);
}
