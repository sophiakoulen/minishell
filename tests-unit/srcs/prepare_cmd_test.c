/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:19:13 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/10 12:21:05 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "unit_tests.h"
#include "minishell.h"

/*
static void	print_fds(t_fds *fds, int n)
{
	ft_printf("pipes:\n");
	for (int i = 0; i < n - 1; i++)
	{
		ft_printf("\tREAD:[%d] - WRITE [%d]\n",
			fds->pipes[i][0], fds->pipes[i][1]);
	}
	ft_printf("heredoc pipes:\n");
	for (int i = 0; i < n; i++)
	{
		ft_printf("\tREAD:[%d] - WRITE [%d]\n",
			fds->hd_pipes[i][0], fds->hd_pipes[i][1]);
	}
	ft_printf("infiles:\n");
	for (int i = 0; i < n; i++)
	{
		ft_printf("\t[%d] ", fds->infile_fds[i]);
	}
	ft_printf("\n");
	ft_printf("outfiles:\n");
	for (int i = 0; i < n; i++)
	{
		ft_printf("\t[%d] ", fds->outfile_fds[i]);
	}
	ft_printf("\n");
	ft_printf("\n");
}


static void	print_infos(t_cmd_info *infos, int n)
{
	for(int i = 0; i < n; i++)
	{
		ft_printf("info on cmd #%i:\n\n", i);
		ft_printf("\tinput:[%d]\n", infos[i].i_fd);
		ft_printf("\toutput:[%d]\n", infos[i].o_fd);
		ft_printf("\tfull_path:%s\n", infos[i].full_path);
		ft_printf("\tstatus:%d\n\n", infos[i].status);
	}
}
*/

int	main(void)
{
	return (0);
}

	/*t_fds	*fds = prepare_fds(2);

	char	*args1[] = {"hello", "-la", 0};
	char	*args2[] = {"ls", "-la", "*", 0};
	//char	*args3[] = {"echo", "hello", "world", "this", "is", "test", 0};

	t_redir	in1 = {.type = e_infile, .str = "input1.txt"};
	t_redir	out1 = {.type = e_outfile, .str = "output1.txt"};

	//t_redir	in2 = {.type = INFILE, .str = "input2.txt"};
	t_redir	out2 = {.type = e_outfile, .str = "output2.txt"};
	//t_redir	in3 = {.type = INFILE, .str = "input3.txt"};
	//t_redir	out3 = {.type = OUTFILE, .str = "output3.txt"};

	t_cmd cmd1 = {.args = args1, .in = &in1, .out = &out1};
	t_cmd cmd2 = {.args = args2, .in = 0, .out = &out2};
	//t_cmd cmd3 = {.args = args3, .in = &in3, .out = &out3};

	t_cmd cmds[] = {cmd1, cmd2};

	t_cmd_info *infos;

	infos = prepare_all_cmds(cmds, fds, 2);

	print_fds(fds, 2);

	print_infos(infos, 2);

	cleanup_fds(fds, 2);
	*/
