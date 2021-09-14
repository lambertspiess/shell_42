/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 08:13:47 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/17 20:32:14 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			free_str_arr(char **arr)
{
	int				i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = 0;
		i++;
	}
	free(arr);
	arr = 0;
}

void			free_env_list(t_env *env)
{
	t_env			*head;
	t_env			*to_free;

	if (env == NULL)
		return ;
	head = env;
	while (head)
	{
		to_free = head;
		if (head->key)
			free(head->key);
		head->key = NULL;
		if (head->value)
			free(head->value);
		head->value = NULL;
		head = head->next;
		free(to_free);
		to_free = NULL;
	}
}

void			free_cmd_av(t_cmd_info *io)
{
	int			i;

	if (io->av == 0)
		return ;
	i = 0;
	while (i < io->ac)
	{
		free(io->av[i]);
		io->av[i] = 0;
		i++;
	}
	ft_free((void **)(&(io->av)));
}
