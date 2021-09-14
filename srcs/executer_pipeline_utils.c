/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipeline_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 23:18:56 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/21 23:20:50 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				count_pipes(t_ast_node *node)
{
	t_ast_node		*head;
	int				count;

	head = node;
	count = 0;
	while (head)
	{
		if (head->type == PIPE)
			count++;
		else
			break ;
		head = head->right;
	}
	return (count);
}
