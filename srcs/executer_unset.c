/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 05:00:01 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/17 20:30:54 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			free_env(t_env **envp)
{
	ft_free((void **)(&((*envp)->key)));
	ft_free((void **)(&((*envp)->value)));
	ft_free((void **)(envp));
}

static void			unset_env(t_cmd_info *io, t_env *env, t_env *prev)
{
	int					i;

	i = 0;
	while (++i < io->ac)
	{
		env = getstat()->env;
		if (ft_strequ(io->av[i], env->key))
		{
			getstat()->env = getstat()->env->next;
			free_env(&env);
			continue ;
		}
		while (env)
		{
			if (ft_strequ(io->av[i], env->key))
			{
				prev->next = env->next;
				free_env(&env);
				break ;
			}
			prev = env;
			env = env->next;
		}
	}
}

int					execute_unset(t_ast_node *astroot, t_ast_node *node, \
									t_cmd_info *io)
{
	(void)(astroot);
	(void)(node);
	if (io->ac < 2)
		return (0);
	unset_env(io, NULL, NULL);
	return (0);
}
