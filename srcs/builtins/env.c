/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:47:55 by znichola          #+#    #+#             */
/*   Updated: 2023/01/17 11:48:09 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	returns allocated linked list of env variables
 */
t_env	*init_env(char **envp)
{
	t_env	*start;
	t_env	*current;
	t_env	*tmp;
	int		index;

	start = NULL;
	while (*envp)
	{
		index = ft_strchr(*envp, '=') - *envp;
		tmp = env_factory(&(t_env){ft_substr(*envp, 0, index),
						ft_substr(*envp, index + 1, ft_strlen(*envp + index)),
						NULL});
		if (start == NULL)
		{
			start = tmp;
			current = start;
		}
		else
		{
			current->next = tmp;
			current = current->next;
		}
		envp++;
	}
	return (start);
}

void	print_env(t_env *env, char *how)
{
	if (env == NULL)
		return ;
	if (ft_strncmp(how, "centered", 9) == 0)
		ft_printf("%29s = %s\n", env->key, env->value);
	else
		ft_printf("%s=%s\n", env->key, env->value);

	print_env(env->next, how);
}


char	**env_to_strarr(t_env *env)
{
	char	**ret;
	int		size;
	int		i;

	size = size_env(env) + 1;
	// ft_printf("size:%d\n", size);
	ret = x_malloc(sizeof(*ret), size);
	i = 0;
	while (i < size - 1)
	{
		// ret[i] = ft_strdup((char *)lst->content); //careful, args list is malloced!
		// lst = lst->next;
		i++;
	}
	ret[i] = 0;
	return (ret);
}

void	env(t_env *env)
{
	print_env(env, NULL);
}
