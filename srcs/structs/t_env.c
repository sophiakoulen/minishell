/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:17:28 by znichola          #+#    #+#             */
/*   Updated: 2023/02/14 11:21:06 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_factory(char *key, char *value, t_env *next)
{
	t_env	*ret;

	ret = (t_env *)x_malloc(sizeof(t_env), 1);
	ret->key = key;
	ret->value = value;
	ret->next = next;
	return (ret);
}

/*
	Frees a single element of the env
*/
void	env_cleanup(t_env *env)
{
	if (env)
	{
		free(env->key);
		free(env->value);
	}
	free(env);
}

/*
	Frees the whole env linked list
*/
void	env_cleanup_all(t_env *env)
{
	t_env	*previous;

	previous = 0;
	while (env)
	{
		env_cleanup(previous);
		previous = env;
		env = env->next;
	}
	env_cleanup(previous);
}

t_env	*env_last(t_env *env)
{
	if (env == NULL)
		return (NULL);
	while (env->next != NULL)
	{
		env = env->next;
	}
	return (env);
}
