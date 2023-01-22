/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:47:00 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/22 16:36:39 by skoulen          ###   ########.fr       */
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
	t_env	*node;

	if (!*key)
		return ;
	current = *env;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			break ;
		}
		current = current->next;
	}
	if (current == NULL)
	{
		node = env_factory(&(t_env){ft_strdup(key), ft_strdup(value), *env});
		*env = node;
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
		if (ft_strncmp(key, current->key, ft_strlen(key)) == 0)
		{
			next = current->next;
			if (previous)
				previous->next = next;
			else
				*env = next;
			env_cleanup(current);
			break ;
		}
		previous = current; 
		current = current->next;
	}
}
