/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:17:28 by znichola          #+#    #+#             */
/*   Updated: 2023/01/17 14:09:17 by znichola         ###   ########.fr       */
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

void	env_cleanup(t_env *env)
{
	(void)env;
}
