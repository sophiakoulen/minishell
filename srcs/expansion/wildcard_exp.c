/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:02:38 by znichola          #+#    #+#             */
/*   Updated: 2023/01/29 13:48:39 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	TODO:
	- case not handled when we start or end with a wildcard
	- when not starting with a wildcard it's imporcat to do a
		strcmp to only match if the beginning of the word does
	- when ending with no wildcard match needs to be found
	- when ending with wildcard no need to keep looking for matches,
		this is the current bihaviour
	- should be resistant to getting a string that has no wildcard matches
	- match while ignoring quotes!
	- matching is not done on ignored files, but is on folders!?
	- refactor the function to:

	int	wildcard_exp(char **ret, char *str);

	ret contains a malloced string with all the files that match the wildcard expression.
	if no matches are found return the expression string.

 */

int	match_wildcard(char *file, char *expr);

int	wildcard_exp(char **ret, char *str)
{
	struct dirent	*dir_entry;
	DIR				*dir;
	t_list			*words;

	(void)ret;
	(void)str;
	words = NULL;
	if (str == NULL || *str == '\0')
		return (0);
	dir = opendir(".");
	if (dir == NULL)
	{
		ft_printf("could'nt open current directory\n");
		return (0);
	}
	dir_entry = readdir(dir);
	dir_entry = readdir(dir);
	dir_entry = readdir(dir); // thrice to get rid of the starting . and .. directory
	while (dir_entry != NULL)
	{
		// ft_printf("type: %d entry: %s\n", dir_entry->d_type, dir_entry->d_name);
		// if (dir_entry->d_name[0] != '.' && match_wildcard(dir_entry->d_name, str) == 1)
		if (match_wildcard(dir_entry->d_name, str) == 1)
		{
			// ft_printf("			match %s\n", dir_entry->d_name);
			ft_lstadd_back(&words, ft_lstnew((char *)ft_strjoin(dir_entry->d_name, " ")));
		}
		dir_entry = readdir(dir);
	}
	*ret = list_to_str(words);
	ft_lstclear(&words, free);
	closedir(dir);
	return (1);
}

int	match_wildcard(char *file, char *expr)
{
	char	**chunks;
	char	*tmp;
	int		i;
	int		ret;

	ret = -1;
	chunks = ft_split(expr, '*');
	i = 0;
	if (expr[0] != '*')
	{
		if (0 != ft_strncmp(file, chunks[0], ft_strlen(chunks[0])))
		{
			strarr_cleanup(chunks);
			return (0);
		}
		i++;
	}
	while (1)
	{
		if (chunks[i] == NULL)
		{
			ret = 1;
			break ;
		}
		tmp = ft_strnstr(file, chunks[i], ft_strlen(file));
		if (tmp == NULL)
		{
			ret = 0;
			break ;
		}
		file = tmp;
		i++;
	}
	strarr_cleanup(chunks);
	return (ret);
}
