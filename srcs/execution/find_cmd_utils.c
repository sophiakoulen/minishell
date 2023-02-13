/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:58:10 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/13 11:29:45 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
