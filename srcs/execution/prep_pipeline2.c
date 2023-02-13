/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_pipeline2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:32 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/13 14:34:12 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	**get_pipes(int n);
static char	**extract_path(t_env *env);

/*
	Initialize the exec structure before preparing the commands:
	- compute the number of commands
	- allocate and open the needed pipes
	- keep track of the number of file descriptors we opened
	- store the env and prev variable in the struct
	- extract the PATH from the environment
	- allocate memory to store info about each command

	Note:
	The amount of regular pipes we open is normally n - 1,
	unless n is 0, of course.
	The amount of heredoc pipes we open is n, although we might not
	need them all.
*/
void	init_exec(t_list *pipeline, t_exec *exec, t_env **env, int prev)
{
	int		n_pipes;

	exec->n = ft_lstsize(pipeline);
	if (exec->n != 0)
		n_pipes = exec->n - 1;
	else
		n_pipes = 0;
	exec->pipes = get_pipes(n_pipes);
	exec->hd_pipes = get_pipes(exec->n);
	exec->fd_count = n_pipes * 2 + exec->n * 2;
	exec->env = env;
	exec->prev = prev;
	exec->path = extract_path(*env);
	exec->cmds = x_malloc(sizeof(*(exec->cmds)), exec->n);
}

/*
	Allocate an array of n pipes and open them.
*/
static int	**get_pipes(int n)
{
	int	**pipes;
	int	i;

	pipes = x_malloc(sizeof(*pipes), n);
	i = 0;
	while (i < n)
	{
		pipes[i] = x_malloc(sizeof(int), 2);
		if (pipe(pipes[i]) != 0)
		{
			perror("failed to open pipe");
			exit(3);
		}
		i++;
	}
	return (pipes);
}

/*
	Extracts the PATH variable from the environment,
	in the form of a null-terminated array of strings.
*/
static char	**extract_path(t_env *env)
{
	int		i;
	char	**default_path;
	char	**strs;

	strs = env_to_strarr(env);
	if (strs)
	{
		i = 0;
		while (strs[i])
		{
			if (ft_strncmp("PATH=", strs[i], 5) == 0)
			{
				return (ft_split(strs[i] + 5, ':'));
			}
			i++;
		}
	}
	strarr_cleanup(strs);
	default_path = ft_split("", ':');
	return (default_path);
}
