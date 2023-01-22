/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:41:48 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/22 16:17:37 by skoulen          ###   ########.fr       */
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
	returns the value string associated with key
	this points to env string, don't free it!
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
		if (ft_strncmp(env->key, key, l) == 0)
		{
			return (ft_strdup(env->value));
		}
		env = env->next;
	}
	return (NULL);
}

/*
	Checks if a string is a valid identifier for export.

	Valid identifiers may only contain letters, digits and
	underscores, and must not start with a digit.
*/
int	is_valid_identifier(char *str)
{
	if (ft_isdigit(*str))
		return (0);
	while (ft_isalnum(*str) || *str == '_')
		str++;
	return (*str == '\0');
}
