/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:21:47 by znichola          #+#    #+#             */
/*   Updated: 2023/01/31 15:02:50 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*ret_builtin_literal(int n);
static int			exec_builtin(int n, char **args, t_env **env, int prev);

int	launch_builtin(t_exec *exec, int i)
{
	int	stdin_clone;
	int	stdout_clone;

	stdin_clone = dup(STDIN_FILENO);
	stdout_clone = dup(STDOUT_FILENO);
	dup2(exec->cmds[i].i_fd, STDIN_FILENO);
	dup2(exec->cmds[i].o_fd, STDOUT_FILENO);
	close_fds(exec);
	exec->cmds[i].status = exec_builtin(exec->cmds[i].builtin,
			exec->cmds[i].args + 1, exec->env, exec->prev);
	dup2(stdin_clone, STDIN_FILENO);
	dup2(stdout_clone, STDOUT_FILENO);
	close(stdin_clone);
	close(stdout_clone);
	return (exec->cmds[i].status);
}

/*
	If the string corresponds to the name of a builtin, return
	the corresponding enum.
	Else, return -1.
*/
int	ret_builtin_enum(char *str)
{
	int		i;

	i = -1;
	while (++i < NUM_BUILTINS)
	{
		if (!ft_strcmp(str, ret_builtin_literal(i)))
			return (i);
	}
	return (-1);
}

/*
	Returns the corresponding string for the builtin,
	or NULL if not in list.
*/
static const char	*ret_builtin_literal(int n)
{
	static const char	*tok_strings[NUM_BUILTINS] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		"shout"
	};

	if (n > NUM_BUILTINS || n < 0)
		return (NULL);
	return (tok_strings[n]);
}

/*
	Just say we don't support this builtin.
*/
static int	builtin_passthrough(char **args, t_env **env, int prev)
{
	(void)args;
	(void)env;
	(void)prev;
	ft_printf("don't support this builtin yet\n");
	return (0);
}

/**
 * executed the builtin using args as it's argument,
 * or NULL if not in list.
*/
static int	exec_builtin(int n, char **args, t_env **env, int prev)
{
	static int	(*builtin_arr[NUM_BUILTINS])(char **, t_env **, int) = {
		exec_echo,
		exec_cd,
		exec_pwd,
		exec_export,
		exec_unset,
		exec_env,
		exec_exit,
		exec_shout,
	};

	if (n > NUM_BUILTINS || n < 0)
		return (builtin_passthrough(args, env, prev));
	return ((builtin_arr)[n](args, env, prev));
}
