/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:41:48 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/08 12:24:28 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	incrament_shlvl(t_env **env);

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
	incrament_shlvl(&start);
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

/*
	incraments the shell level
 */
static void	incrament_shlvl(t_env **env)
{
	char	*value;
	int		lvl;

	value = ret_env_key(*env, "SHLVL");
	if (value == NULL)
		lvl = 0;
	else
	{
		if (safe_atoi(&lvl, &value))
		{
			print_error(0, 0, "shell level is too damn high, resting to 0");
			lvl = 0;
		}
		if (lvl < 0)
		{
			print_error(0, 0, "don't like this negative shell enegry, resetting to 0");
			lvl = 0;
		}
		if (safe_add(&lvl, 1))
		{
			print_error(0, 0, "tried to catch me in an overflow! well I reset you to 0");
			lvl = 0;
		}
	}
	env_add(env, "SHLVL", ft_itoa(lvl));
}
