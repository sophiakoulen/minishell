/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:48:54 by znichola          #+#    #+#             */
/*   Updated: 2023/02/09 17:16:01 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*ret_sig_msg(int sig);
static void			print_pipe_error(int n);
static int			calc_len(const char *msg, char *num);

void	pipe_return_print(int retn)
{
	if (retn < 128)
		return ;
	print_pipe_error(retn % 128);
}

static const char	*ret_sig_msg(int sig)
{
	static const char	*msg[116] = {
		"",
		MSH_MSG_SIGHUP,
		"",
		MSH_MSG_SIGQUIT,
		MSH_MSG_SIGILL,
		MSH_MSG_SIGTRAP,
		MSH_MSG_SIGABRT,
		MSH_MSG_SIGEMT,
		MSH_MSG_SIGFPE,
		MSH_MSG_SIGKILL,
		MSH_MSG_SIGBUS,
		MSH_MSG_SIGSEGV,
		MSH_MSG_SIGSYS,
		MSH_MSG_SIGPIPE,
		MSH_MSG_SIGALRM,
		MSH_MSG_SIGTERM,
	};

	if (sig <= 0 || sig >= 16)
		return (msg[0]);
	return (msg[sig]);
}

/*
	Print error on stderr.

	Error has the form:
		minishell: {program}: {arg}: {msg}

	program and arg can be null, then they won't be printed
	and neither will the corresponding colon and space.
*/
static void	print_pipe_error(int n)
{
	int			len;
	char		*buffer;
	char		*num;
	const char	*msg;

	msg = ret_sig_msg(n);
	if (msg[0] == '\0')
	{
		write(2, "\n", 1);
		return ;
	}
	if (n == 13) // for broken pipe that dosn't do a newline!?
		return ;
	num = ft_itoa(n);
	len = calc_len(msg, num);
	buffer = x_malloc(sizeof(char), len);
	buffer[0] = '\0';
	ft_strlcat(buffer, msg, len);
	ft_strlcat(buffer, ": ", len);
	ft_strlcat(buffer, num, len);
	ft_strlcat(buffer, "\n", len);
	write(2, buffer, len - 1);
	free(buffer);
	free(num);
}

/*
	Compute length of error message.
*/
static int	calc_len(const char *msg, char *num)
{
	return (ft_strlen(msg) + 2 + ft_strlen(num) + 2);
}
