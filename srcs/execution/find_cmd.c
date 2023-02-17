/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:58:13 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/17 09:32:08 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_path(char **path, const char *filename, char **res);
static int	compute_status(int errno_value);
static char	*concat_slash(const char *str1, const char *str2);
static int	file_ok(char *filename, char **res);

/*
	Finds a specified command and sets res to the absolute path if found,
	or NULL.

	If the command contains slashes, it's considered an absolute path.
	Else, we search in the PATH variable until an executable with
	that name is found.

	An error message is printed if command is not found, and an error
	code is returned:
		- 127 if ENOENT: command not found / no such file or directory
		- 126 else: permission denied / too many symbolic links / etc.
*/
int	find_cmd(char **path, char *filename, char **res)
{
	int			errno_value;

	errno_value = ENOENT;
	*res = 0;
	if (ft_strchr(filename, '/') != NULL)
	{
		errno_value = file_ok(filename, res);
		if (errno_value != 0)
			print_error(0, filename, strerror(errno_value));
	}
	else
	{
		if (filename[0] == '\0')
			errno_value = ENOENT;
		else
			errno_value = search_path(path, filename, res);
		if (errno_value != 0)
		{
			if (errno_value == ENOENT)
				print_error(0, filename, "command not found");
			else
				print_error(0, filename, strerror(errno_value));
		}
	}
	return (compute_status(errno_value));
}

/*
	file_ok:

	Checks whether we have access to an absolute path.

	If we have access:
		res is set to a strdup of the filename,
		0 is returned.
	If we do not have access:
		res is set to 0,
		errno is returned.
*/
static int	file_ok(char *filename, char **res)
{
	struct stat	path_info;

	*res = 0;
	if (access(filename, F_OK) == -1)
		return (errno);
	if (lstat(filename, &path_info) != 0)
	{
		print_error(0, 0, strerror(errno));
		exit(5);
	}
	if (S_ISDIR(path_info.st_mode))
		return (EISDIR);
	if (access(filename, X_OK) == -1)
		return (errno);
	*res = ft_strdup(filename);
	return (0);
}

/*
	Checks all paths from the PATH variable, for a filename.
	Stop at first executable filename.

	An error code is returned, which corresponds to an error
	from the access() function.
	error codes different than ENOENT have priority.

	If found, the absolute path is copied to res.
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
			status = file_ok(concat, res);
			free(concat);
			if (status == 0)
				return (0);
			else if (status != ENOENT)
				ret = status;
			i++;
		}
	}
	*res = 0;
	return (ret);
}

/*
	Concatenates the two strings with a '/' as a separator.
*/
static char	*concat_slash(const char *str1, const char *str2)
{
	char	*res;
	size_t	buffer_size;

	buffer_size = ft_strlen(str1) + ft_strlen(str2) + 2;
	res = x_malloc(buffer_size, 1);
	ft_strlcpy(res, str1, buffer_size);
	ft_strlcat(res, "/", buffer_size);
	ft_strlcat(res, str2, buffer_size);
	return (res);
}

/*
	Compute return value based on errno value.

	If 0, then return 0
	If ENOENT, return 127
	Else, return 126
*/
static int	compute_status(int errno_value)
{
	if (errno_value == 0)
		return (0);
	if (errno_value == ENOENT)
		return (127);
	return (126);
}
