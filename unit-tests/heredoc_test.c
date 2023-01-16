/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:06:31 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/16 09:56:43 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_tests.h"

int	main()
{
	// const char *delim = "EOF";

	char *args[2] = {"cat", 0};

	int hd_pipe[2];
	if (pipe(hd_pipe) != 0)
	{
		perror("pipe() failed");
	}
	int pid = fork();
	if (pid == 0)
	{
		dup2(hd_pipe[0], STDIN_FILENO);
		close(hd_pipe[0]);
		close(hd_pipe[1]);
		execve("/bin/cat", args, 0);
		perror("execution failed\n");
	}
	close(hd_pipe[0]);
	// do_single_heredoc(delim, hd_pipe[1]);
	waitpid(pid, 0, 0);
	return (0);
}
