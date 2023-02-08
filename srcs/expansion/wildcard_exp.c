/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:02:38 by znichola          #+#    #+#             */
/*   Updated: 2023/02/08 13:04:33 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	match_wildcard(char *file, char *expr);
int	check_starting_wildcard(int *i, char *file, char *expr, char ***chunks);
int	check_ending_wildcard(int i, char *file, char *expr, char **chunks);
int	check_single_chunk(int i, int *ret, char **file, char **chunks);

/*
	TODO:
	- match while ignoring quotes!
	- the matches need to be returned in alphabetical order!
	very frustrating that opendir dosn't return in alphabetical order

	ret contains a malloced string containing
	all matched files/folders seperated by a space
	if no matches are found return the expression string.

 */
int	find_wildcard_matches(char **ret, char *str)
{
	struct dirent	*dir_entry;
	DIR				*dir;
	t_list			*words;

	if (str == NULL || *str == '\0')
		return (0);
	dir = opendir(".");
	if (dir == NULL)
	{
		ft_printf("could'nt open current directory\n");
		return (0);
	}
	words = NULL;
	dir_entry = readdir(dir);
	dir_entry = readdir(dir);
	dir_entry = readdir(dir); // thrice to get rid of the starting . and .. directory
	while (dir_entry != NULL)
	{
		if (match_wildcard(dir_entry->d_name, str) == 1)
			ft_lstadd_back(&words, ft_lstnew((char *)ft_strjoin(dir_entry->d_name, " ")));
		dir_entry = readdir(dir);
	}
	if (words == NULL)
		*ret = ft_strjoin(str, " ");
	else
	{
		lst_bubble_sort(&words, ft_strcmp);
		*ret = list_to_str(words);
	}
	ft_lstclear(&words, free);
	closedir(dir);
	// (*ret)[ft_strlen(*ret)-1] = '\0';
	return (1);
}

/*
	checks if the file is a match with the wildcard expression
 */
int	match_wildcard(char *file, char *expr)
{
	char	**chunks;
	int		i;
	int		ret;

	ret = -1;
	expr = quote_removal(expr);
	chunks = ft_split(expr, '*');
	i = 0;
	if (check_starting_wildcard(&i, file, expr, &chunks) == 1)
	{
		free(expr);
		return (0);
	}
	while (check_single_chunk(i, &ret, &file, chunks))
		i++;
	if (ret == 1)
		ret = check_ending_wildcard(i, file, expr, chunks);
	strarr_cleanup(chunks);
	free(expr);
	return (ret);
}

/*
	updates the file string to what's left to match against
	the i chunk from the expression
 */
int	check_single_chunk(int i, int *ret, char **file, char **chunks)
{
	char	*tmp;

	if (chunks[i] == NULL)
	{
		*ret = 1;
		return (0);
	}
	tmp = ft_strnstr(*file, chunks[i], ft_strlen(*file));
	if (tmp == NULL)
	{
		*ret = 0;
		return (0);
	}
	*file = tmp;
	return (1);
}


/*
	cleans up chunks if ret is 1
	checks if there is a starting wildcard and return accordingly
 */
int	check_starting_wildcard(int *i, char *file, char *expr, char ***chunks)
{
	if (file[0] == '.' && expr[0] != '.')
	{
		strarr_cleanup(*chunks);
		return (1);
	}
	if (expr[0] != '*')
	{
		if (0 != ft_strncmp(file, *chunks[0], ft_strlen(*chunks[0])))
		{
			strarr_cleanup(*chunks);
			return (1);
		}
		*i = *i + 1;
	}
	return (0);
}

/*
	checks if we end with a wildcard and return accordingly
 */
int	check_ending_wildcard(int i, char *file, char *expr, char **chunks)
{
	int	ret;

	ret = 1;
	if (expr[ft_strlen(expr) - 1] != '*')
	{
		if (ft_strncmp(file, chunks[i - 1], ft_strlen(file)) == 0)
			ret = 1;
		else
			ret = 0;
	}
	return (ret);
}
