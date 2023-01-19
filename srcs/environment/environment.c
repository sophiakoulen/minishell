/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:41:48 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/19 12:45:03 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	returns allocated linked list of env structs
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

/*
	return malloced strarr of env
	remember to free it!
 */
char	**env_to_strarr(t_env *env)
{
	char	**ret;
	char	*tmp;
	int		size;
	int		i;

	size = size_env(env);
	ret = x_malloc(sizeof(*ret), size + 1);
	i = 0;
	while (i < size)
	{
		tmp = ft_strjoin(env->key, "=");
		ret[i] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
		i++;
	}
	ret[i] = 0;
	return (ret);
}

/*
	returns the value associated with key
	this is pointer to string in env, don't free it!
	NULL if not found
*/
char	*ret_env_key(t_env *env, char *key)
{
	size_t	l;

	while (env)
	{
		l = ft_strlen(key);
		if (l < ft_strlen(env->key))
			l = ft_strlen(env->key);
		if (ft_strncmp(env->key, key, l))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}
