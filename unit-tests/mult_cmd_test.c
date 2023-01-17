/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_cmd_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:50:19 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/17 10:40:51 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_tests.h"

static void print_fds(t_fds *fds, int n)
{
	printf("pipes:\n");
	for (int i = 0; i < n - 1; i++)
	{
		printf("\tREAD:[%d] - WRITE [%d]\n", fds->pipes[i][0], fds->pipes[i][1]);
	}
	printf("heredoc pipes:\n");
	for (int i = 0; i < n; i++)
	{
		printf("\tREAD:[%d] - WRITE [%d]\n", fds->hd_pipes[i][0], fds->hd_pipes[i][1]);
	}
	printf("infiles:\n");
	for (int i = 0; i < n; i++)
	{
		printf("\t[%d] ", fds->infile_fds[i]);
	}
	printf("\n");
	printf("outfiles:\n");
	for (int i = 0; i < n; i++)
	{
		printf("\t[%d] ", fds->outfile_fds[i]);
	}
	printf("\n");
	printf("\n");
}

static void	print_infos(t_cmd_info *infos, int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("info on cmd #%i:\n\n", i);
		printf("\tinput:[%d]\n", infos[i].i_fd);
		printf("\toutput:[%d]\n", infos[i].o_fd);
		printf("\tfull_path:%s\n", infos[i].full_path);
		printf("\tstatus:%d\n\n", infos[i].status);
	}
}

int main()
{
	t_fds	*fds = prepare_fds(2);
	
	char	*args1[] = {"cat", 0};
	char	*args2[] = {"grep", "hello", 0};
	//char	*args3[] = {"existepas", "hello", "world", "this", "is", "test", 0};

	t_redir	in1 = {.type = e_heredoc, .str = "EOF"};
	//t_redir	out1 = {.type = OUTFILE, .str = "output1.txt"};

	//t_redir	in2 = {.type = INFILE, .str = "input2.txt"};
	//t_redir	out2 = {.type = OUTFILE, .str = "output2.txt"};
	
	//t_redir	in3 = {.type = INFILE, .str = "input3.txt"};
	//t_redir	out3 = {.type = OUTFILE, .str = "output3.txt"};

	t_cmd cmd1 = {.args = args1, .in = &in1, .out = 0};
	t_cmd cmd2 = {.args = args2, .in = 0, .out = 0};
	//t_cmd cmd3 = {.args = args3, .in = 0, .out = 0};

	t_cmd cmds[] = {cmd1, cmd2}; 

	int ret;

	ret = multiple_commands(cmds, fds, 2);
	
	printf("return value:%d\n", ret);
	
	//print_fds(fds, 2);
	
	cleanup_fds(fds, 2);

	return (0);
}
