/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:02:38 by znichola          #+#    #+#             */
/*   Updated: 2023/01/27 14:51:10 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <dirent.h>

int	match_wildcard(char *file, char *expr)
{
	char	**chunks;
	char	*tmp;
	int		i;

	chunks = ft_split(expr, '*');
	i = 0;
	while (1)
	{
		if (chunks[i] == NULL)
			return (1);
		tmp = ft_strnstr(file, chunks[i], ft_strlen(file));
		if (tmp == NULL)
			return (0);
		file = tmp;
		i++;
	}
	ft_printf("here is an error");
	return (-1);
}

int	wildcard_exp(t_list **words, char *str)
{
	struct dirent	*dir_entry;
	DIR				*dir;

	(void)words;
	(void)str;
	if (str == NULL || *str == '\0')
		return (0);
	dir = opendir(".");
	if (dir == NULL)
	{
		ft_printf("could'nt open current directory\n");
		return (0);
	}
	dir_entry = readdir(dir);
	while (dir_entry != NULL)
	{
		ft_printf("type: %d entry: %s\n", dir_entry->d_type, dir_entry->d_name);
		if (dir_entry->d_type == 8)
		{
			if (match_wildcard(dir_entry->d_name, str) == 1)
			{
				ft_printf("			match %s\n", dir_entry->d_name);
				// ft_lstadd_back(words, ft_lstnew(ft_strdup(dir_entry->d_name)));
			}
		}
		dir_entry = readdir(dir);
	}
	closedir(dir);
	return (1);
}

int	main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
		return (1);
	wildcard_exp(NULL, av[1]);
	return (0);
}
