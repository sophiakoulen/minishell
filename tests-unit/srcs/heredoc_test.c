/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:06:31 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/10 12:23:20 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	static char	*args[2] = {"cat", 0};
	int			hd_pipe[2];
	int			pid;

	if (pipe(hd_pipe) != 0)
	{
		perror("pipe() failed");
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(hd_pipe[0], STDIN_FILENO);
		close(hd_pipe[0]);
		close(hd_pipe[1]);
		execve("/bin/cat", args, 0);
		perror("execution failed\n");
	}
	close(hd_pipe[0]);
	waitpid(pid, 0, 0);
	return (0);
}
