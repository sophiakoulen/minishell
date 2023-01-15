/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:03:02 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/15 17:38:27 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	DOESNT COMPILE YET
*/
/*
	Execute pipeline and return exit status of last command.

	Needs the environment to work with and send to child processes.

	If there is only one command, we don't fork.
*/
int	exec_pipeline(t_cmd *cmds, int n_cmds)
{
	t_fds	*fds;
	int		ret;

	fds = prepare_fds(cmds);
	if (n_cmds < 2)
	{
		; //ret = simple_command(cmds->cmds[0], environment);
	}
	else
	{
		ret = multiple_commands(cmds, fds, n_cmds);
	}
	cleanup_fds(fds, n_cmds);
	return (ret);
}
