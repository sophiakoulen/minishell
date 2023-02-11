/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:47:00 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/11 19:20:51 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	returns the number of elements in env
*/
size_t	size_env(t_env *env)
{
	size_t	len;

	len = 0;
	while (env != NULL)
	{
		env = env->next;
		len++;
	}
	return (len);
}

/*
	Add a key-value pair to the environment.
	If the key already exists, its value will be overwritten.
*/
void	env_add(t_env **env, char *key, char *value)
{
	t_env	*current;
	t_env	*new_node;

	if (!*key)
		return ;
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			break ;
		}
		current = current->next;
	}
	if (current == NULL)
	{
		new_node = env_factory(&(t_env){ft_strdup(key), ft_strdup(value), NULL});
		current = env_last(*env);
		current->next = new_node;
	}
}

/*
	Remove a key from the environment.
*/
void	env_remove(t_env **env, char *key)
{
	t_env	*current;
	t_env	*previous;
	t_env	*next;

	current = *env;
	previous = 0;
	while (current)
	{
		if (ft_strcmp(key, current->key) == 0)
		{
			next = current->next;
			if (previous)
				previous->next = next;
			else
				*env = next;
			env_cleanup(current);
			current = NULL;
			break ;
		}
		previous = current;
		current = current->next;
	}
}

/*
	returns the value string associated with key
	this points to env string, don't free it!
	empty string if not found
*/
char	*ret_env_key(t_env *env, char *key)
{
	static char	empty[1] = "";

	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			return (env->value);
		}
		env = env->next;
	}
	return (empty);
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
