/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 06:11:09 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/20 06:39:40 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			env_print_list(t_env *env)
{
	while (env)
	{
		ft_printf("key :|%s| value : |%s|\n", env->key, env->value);
		env = env->next;
	}
}

static void		fatal_error_in_env_init(void)
{
	if (getstat()->env)
		free_env_list(getstat()->env);
	ft_printf_fd(STDERR_FILENO, "minishell: fatal error : ");
	ft_printf_fd(STDERR_FILENO, "%s\n", strerror(errno));
	exit(EXIT_FAILURE);
}

int				check_for_equalsign(char *s)
{
	int				i;
	int				equals;

	if (!s)
		return (0);
	i = 0;
	equals = 0;
	while (s[i])
	{
		if (s[i] == '=')
			equals++;
		i++;
	}
	if (equals < 1)
		return (0);
	else
		return (1);
}

t_env			*add_env_pair(char **sp)
{
	t_env		*env;
	char		*s;
	int			i;

	if (!sp)
		return (NULL);
	s = *sp;
	if (!(check_for_equalsign(s)))
		return (NULL);
	if (!(env = ft_memalloc(sizeof(t_env))))
		fatal_error_in_env_init();
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (!(env->key = ft_strndup(s, i)))
		fatal_error_in_env_init();
	i++;
	if (s[i] && !(env->value = ft_strndup(s + i, ft_strlen(s) - i)))
		fatal_error_in_env_init();
	return (env);
}

void			env_init(char **envp)
{
	int				i;
	t_env			*envlistp;
	t_env			*cur;

	getstat()->env = NULL;
	if (!envp || !(*envp))
		return ;
	envlistp = NULL;
	i = 0;
	if (envp[i])
		envlistp = add_env_pair(envp + i);
	cur = envlistp;
	while ((envp + i) != NULL)
	{
		if (*(envp + i) == NULL)
			break ;
		if (!(cur->next = add_env_pair(envp + i)))
			fatal_error_in_env_init();
		cur->next->next = NULL;
		cur = cur->next;
		i++;
	}
	getstat()->env = envlistp;
}
