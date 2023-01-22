/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:47:00 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/22 11:51:17 by skoulen          ###   ########.fr       */
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

void	env_add(t_env **env, char *key, char *value)
{
	t_env	*current;
	t_env	*new_node;

	if (!*key)
		return ;
	new_node = x_malloc(sizeof(*new_node), 1);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (*env == NULL)
	{
		*env = new_node;
		return ;
	}
	current = *env;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			free(new_node->key);
			free(new_node->value);
			free(new_node);
			break ;
		}
		current = current->next;
	}
	if (current == NULL)
	{
		new_node->next = *env;
		*env = new_node;
	}
}

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
			free(current);
			break ;
		}
		previous = current; 
		current = current->next;
	}
}
