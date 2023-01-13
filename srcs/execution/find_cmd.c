/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:58:13 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/13 17:59:21 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(int errno_value, char *str);
static int	search_path(char **path, const char *filename, char **res);
static int	compute_status(int errno_value);

/*
	Finds a specified command and sets a heap-allocated string containing
	the absolute path to the program.
	
	res is set to 0 if no such file with executable permissions is found,
	and an appropriate error code is returned.

	if filename is a path and the path is executable, the filename is
	duplicated in res.

	if filename is not a path and such a command is found in the PATH,
	res is set to the path to that command.

	This function prints the appropriate error message.

*/
int	find_cmd(char **path, char *filename, char **res)
{
	int			errno_value;

	//what if filename is null??
	errno_value = ENOENT;
	*res = 0;
	if (*filename)
	{
		if (has_slashes(filename))
		{
			errno_value = file_ok(filename, res);
		}
		else
		{
			errno_value = search_path(path, filename, res);
		}
	}
	print_error(errno_value, filename);
	return (compute_status(errno_value));
}

static void	print_error(int errno_value, char *str)
{
	if (errno_value == ENOENT && !has_slashes(str))
	{
		ft_dprintf(2, "%s: command not found\n", str);
	}
	else if (errno_value != 0)
	{
		perror(str);
	}
}

/*
	Checks all paths from the PATH variable.
	If not exist, 127 is returned.
	If no permission, 126 is returned.
	If malloc error, 1 is returned.
	If something else, 1 is returned.
	In any case an error message is printed.

	If OK, res is set to the abs path.
	If NOT OK, res is set to 0.

	!!!! Error message may be innacurate if something
	else is happening.
*/
static int	search_path(char **path, const char *filename, char **res)
{
	int		i;
	int		status;
	int		ret;
	char	*concat;

	ret = ENOENT;
	if (path)
	{
		i = 0;
		while (path[i])
		{
			concat = concat_slash(path[i], filename);
			if (!concat)
				return (errno);
			
			status = file_ok(concat, res);
			free(concat);
			if (status == 0) // executable file is found
			{
				return (0);
			}
			else if (status != ENOENT)
			{
				ret = status;
			}
			i++;
		}
	}
	*res = 0;
	return (ret);
}

static int	compute_status(int errno_value)
{
	if (errno_value == 0)
		return (0);
	if (errno_value == ENOENT)
		return (127);
	if (errno_value == ENOMEM)
		return (2);
	return (126);
}
