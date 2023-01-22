/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:08:26 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/22 17:29:44 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calc_len(char *prefix, char *program, char *arg, char *msg);

/*
	Print error on stderr.

	Error has the form:
		minishell: {program}: {arg}: {msg}
	
	program and arg can be null, then they won't be printed
	and neither will the corresponding colon and space. 
*/
void	print_error(char *program, char *arg, char *msg)
{
	int		len;
	char	*prefix;
	char	*buffer;

	prefix = "minishell: ";
	len = calc_len(prefix, program, arg, msg);
	buffer = x_malloc(1, len);
	ft_strlcpy(buffer, prefix, len);
	if (program)
	{
		ft_strlcat(buffer, program, len);
		ft_strlcat(buffer, ": ", len);
	}
	if (arg)
	{
		ft_strlcat(buffer, arg, len);
		ft_strlcat(buffer, ": ", len);
	}
	ft_strlcat(buffer, msg, len);
	ft_strlcat(buffer, "\n", len);
	write(2, buffer, len);
	free(buffer);
}

/*
	Compute length of error message.
*/
static int	calc_len(char *prefix, char *program, char *arg, char *msg)
{
	int	len;

	len = ft_strlen(prefix) + 2 + ft_strlen(msg) + 2;
	if (program)
		len += ft_strlen(program) + 2;
	if (arg)
		len += ft_strlen(arg);
	return (len);
}
