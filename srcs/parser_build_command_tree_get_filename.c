/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_build_command_tree_get_filename.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 06:17:01 by lspiess           #+#    #+#             */
/*   Updated: 2020/07/01 16:58:29 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**  DESCRIPTION
** When output is redirected several times (whether by '>' or '>>' tokens)
** this function finds the output's final destination, creating and overwriting
** files along the way, hence reproducing BASH's behavior
**  PARAMETERS
** int gtsigncount : the number of '>' symbols read so far
** int *redirtype : the nature of the current redirection
**                  ('>' or '>>', depending on gtsigncount)
*/

void			parser_bcm_determine_redirtype(t_ast_node *commandtree, \
										char *redirout, int lastredirtype)
{
	if ((commandtree->data2 = redirout) != NULL)
	{
		if (lastredirtype == REDIR_OUTPUT)
			commandtree->type = REDIR_INPUT_AND_OUTPUT;
		else
			commandtree->type = REDIR_INPUT_AND_APPEND;
	}
	else
		commandtree->type = REDIR_INPUT;
}

static char		*handle_non_filename(int gtsigncount, int *redirtype)
{
	if (check_toktype(TYPE_GREATER, NULL) == FALSE)
		return (NULL);
	if (gtsigncount >= 2)
		return (NULL);
	return (get_filename(++gtsigncount, redirtype));
}

static int		open_fd_wmode(int gtsigncount, char *filename, int *redirtype)
{
	int				fd;

	if (gtsigncount == 1)
	{
		if ((fd = open(filename, O_RDWR | O_CREAT \
			| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		{
			return (-1);
		}
		*redirtype = REDIR_OUTPUT;
	}
	else
	{
		if ((fd = open(filename, O_RDWR | O_CREAT \
		| O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		{
			return (-1);
		}
		*redirtype = REDIR_APPEND;
	}
	return (fd);
}

char			*get_filename(int gtsigncount, int *redirtype)
{
	char			*filename;
	int				fd;

	filename = NULL;
	if (check_toktype(REGULAR_CHARS, &filename) == FALSE)
		return (handle_non_filename(gtsigncount, redirtype));
	if ((fd = open_fd_wmode(gtsigncount, filename, redirtype)) == -1)
	{
		ft_free((void **)(&filename));
		return (NULL);
	}
	close(fd);
	if (check_toktype(TYPE_GREATER, NULL) == TRUE)
	{
		ft_free((void **)(&filename));
		return (get_filename(1, redirtype));
	}
	return (filename);
}
