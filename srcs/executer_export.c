/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 04:54:31 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/22 09:30:21 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If the key already exists, update it. Else add a key-value pair
*/

static void		add_export(t_ast_node *astroot, t_cmd_info *io, t_env *keypair)
{
	t_env			*head;

	head = getstat()->env;
	while (head)
	{
		if (ft_strequ(head->key, keypair->key))
		{
			free(keypair->key);
			free(head->value);
			head->value = keypair->value;
			return ;
		}
		if (!(head->next))
			break ;
		head = head->next;
	}
	if (!(head->next = ft_memalloc(sizeof(t_env))))
		executer_exit_process(astroot, io, errno, 1);
	head->next->key = keypair->key;
	head->next->value = keypair->value;
}

static void		export(t_ast_node *astroot, t_cmd_info *io, char *s)
{
	int				i;
	int				j;
	t_env			keypair;

	ft_bzero(&keypair, sizeof(t_env));
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (!(keypair.key = ft_strndup(s, i)))
		executer_exit_process(astroot, io, errno, 1);
	j = 0;
	if (s[i] == '=')
		i++;
	if ((j = ft_istrlen(s + i)) > 0)
		if (!(keypair.value = ft_strndup(s + i, j)))
		{
			ft_free((void **)(&(keypair.key)));
			executer_exit_process(astroot, io, errno, 1);
		}
	add_export(astroot, io, &keypair);
}

static int		check_validity(t_cmd_info *io, int i, int j)
{
	while (i < io->ac)
	{
		if ((io->av[i])[0] == '=')
			return (1);
		j = 0;
		while ((io->av[i])[j] && ((io->av[i])[j] != '='))
		{
			if (ft_strchr("\"\' ", (io->av[i])[j++]))
			{
				ft_printf_fd(getstat()->default_fd[2],
					"minishell: export: `%s': not a valid identifier\n",
					io->av[i]);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

int				execute_export(t_ast_node *astroot, t_ast_node *node, \
								t_cmd_info *io)
{
	int				i;

	if (io->ac == 1)
		return (execute_env(astroot, node, io));
	if (check_validity(io, 0, 0) != 0)
		return (1);
	i = 1;
	while (i < io->ac)
	{
		export(astroot, io, io->av[i++]);
	}
	return (0);
}
