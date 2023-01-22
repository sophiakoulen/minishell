/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:29:21 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/22 17:06:04 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *str, int errno_value);

/*
	cd builtin: Change working directory.

	TO DO: Update $PWD and $OLDPWD variables.
*/
int	exec_cd(char **args, t_env **env)
{
	(void)env;
	if (!*args)
		return (0);
	if (chdir(*args) != 0)
	{
		print_error(*args, errno);
		return (1);
	}
	return (0);
}

static void	print_error(char *str, int errno_value)
{
	char	*prefix;
	char	*msg;
	char	*buffer;
	int		len;

	prefix = "minishell: cd: ";
	msg = strerror(errno_value);
	len = ft_strlen(str) + 15 + ft_strlen(msg) + 4;
	buffer = x_malloc(1, len);
	ft_strlcpy(buffer, prefix, len);
	ft_strlcat(buffer, str, len);
	ft_strlcat(buffer, ": ", len);
	ft_strlcat(buffer, msg, len);
	ft_strlcat(buffer, "\n", len);
	write(2, buffer, len - 1);
	free(buffer);
}
