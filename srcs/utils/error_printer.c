/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:08:26 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/22 17:16:41 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *program, char *arg, char *msg)
{
	int		len;
	char	*prefix;
	char	*buffer;

	prefix = "minishell: ";
	len = 11;
	if (program)
	{
		len += ft_strlen(program) + 2;
	}
	if (arg)
	{
		len += ft_strlen(arg) + 2;
	}
	len += ft_strlen(msg) + 2;
	buffer = x_malloc(1, len);
	strlcpy(buffer, prefix, len);
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
