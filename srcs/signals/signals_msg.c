/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:48:54 by znichola          #+#    #+#             */
/*   Updated: 2023/02/16 19:56:59 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*ret_sig_msg(int sig);
static int			calc_len(const char *msg, char *num);

/*
	Print error message along with number
	{ error msg }: {num}

	if num is not in our message range, we do nothing.

	n == 13  // for broken pipe that dosn't do a newline!?
*/
void	print_pipe_error(int n)
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
	if (n == 13)
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
	returns the error message string pointer
	Messages strings are defined in the defines.h
 */

static const char	*ret_sig_msg(int sig)
{
	static const char	*msg[19] = {
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
		MSH_MSG_SIGURG,
		MSH_MSG_SIGSTOP,
		MSH_MSG_SIGTSTP,
	};

	if (sig <= 0 || sig >= 19)
		return ("");
	return (msg[sig]);
}

/*
	Compute length of error message.
*/
static int	calc_len(const char *msg, char *num)
{
	return (ft_strlen(msg) + 2 + ft_strlen(num) + 2);
}
