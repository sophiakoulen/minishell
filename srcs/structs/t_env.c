/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:17:28 by znichola          #+#    #+#             */
/*   Updated: 2023/01/17 11:33:38 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	env_factory(&(t_env){key_str, value_str, next})
	call with blueprint or NULL
	Don't forget to free it after!
 */
t_env	*env_factory(t_env *blueprint)
{
	t_env	*ret;

	ret = (t_env *)x_malloc(sizeof(t_env), 1);
	if (blueprint == NULL)
	{
		ret->key = NULL;
		ret->value = NULL;
		ret->next = NULL;
	}
	else
	{
		ret->key = blueprint->key;
		ret->value = blueprint->value;
		ret->next = blueprint->next;
	}
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
}

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

void	env_append(t_env **env, t_env *new)
{
	(void)env;
}

void	env_pop(t_env **env, t_env *new)
{
	(void)env;
}

void	env_find(t_env **env, t_env *new)
{
	(void)env;
}

/*
	returns a char ** of env
	this is a malloced string! remember to free it!
 */
char	**ret_env_strs(t_env *env)
{
	// while(env);
	(void)env;
}

void	env_cleanup(t_env *env)
{
	(void)env;
}
