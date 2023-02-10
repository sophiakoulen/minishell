/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:58:10 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/10 12:56:28 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	extract_path:

	Extracts the path variable from the environment,
	in the form of a null-terminated array of strings.

	If the PATH variable isn't set (not the same as empty),
	a default value for the path is used.
*/
char	**extract_path(char **envp)
{
	int		i;
	char	**default_path;

	if (envp)
	{
		i = 0;
		while (envp[i])
		{
			if (ft_strncmp("PATH=", envp[i], 5) == 0)
			{
				return (ft_split(envp[i] + 5, ':'));
			}
			i++;
		}
	}
	default_path = ft_split("", ':');
	return (default_path);
}

/*
	returns true if a filename is actually a path,
	that is, the string contains at least a slash ('/').
*/
int	has_slashes(const char *str)
{
	return (!!ft_strchr(str, '/'));
}

/*
	concat_slash: Concatenates the two strings with a
	'/' as a separator.

	Returns 0 if one of them is an empty string. WTF??

	if (*str1 == '\0' || *str2 == '\0')
	return (0); //why??
*/
char	*concat_slash(const char *str1, const char *str2)
{
	char	*res;
	size_t	buffer_size;

	if (*str1 == '\0' || *str2 == '\0')
		return (0);
	buffer_size = ft_strlen(str1) + ft_strlen(str2) + 2;
	res = malloc(buffer_size);
	if (!res)
		return (0);
	ft_strlcpy(res, str1, buffer_size);
	ft_strlcat(res, "/", buffer_size);
	ft_strlcat(res, str2, buffer_size);
	return (res);
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
int	file_ok(char *filename, char **res)
{
	*res = 0;
	if (access(filename, X_OK) == -1)
	{
		return (errno);
	}
	*res = ft_strdup(filename);
	if (!res)
	{
		return (errno);
	}
	return (0);
}
