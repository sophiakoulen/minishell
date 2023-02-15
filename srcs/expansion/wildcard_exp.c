/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:02:38 by znichola          #+#    #+#             */
/*   Updated: 2023/02/15 15:28:53 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		match_wildcard(char *file, char *expr);
int		check_starting_wildcard(int *i, char **file, char *expr, char ***chunks);
int		check_ending_wildcard(int i, char *file, char *expr, char **chunks);
int		check_single_chunk(int i, int *ret, char **file, char **chunks);

/*
	TODO:
	- match while ignoring quotes!
	- the matches need to be returned in alphabetical order!
	very frustrating that opendir dosn't return in alphabetical order

	ret contains a malloced string containing
	all matched files/folders seperated by a space
	if no matches are found return the expression string.

	What is the meaning of the return value??
*/
void	find_wildcard_matches(char **ret, char *str)
{
	struct dirent	*dir_entry;
	DIR				*dir;
	t_list			*words;
	char			*escaped;

	if (str == NULL || *str == '\0')
		return ;
	dir = opendir(".");
	if (dir == NULL)
	{
		*ret = ft_strjoin(str, " ");
		return ;
	}
	words = NULL;
	dir_entry = readdir(dir);
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
		escaped = escape_special_chars(*ret, ESC_TYPE_DEFAULT);
		free(*ret);
		*ret = escaped;
	}
	ft_lstclear(&words, free);
	closedir(dir);
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
	expr = ft_strdup(expr);
	chunks = wild_split(expr, '*');
	quote_removal_strarr(chunks);
	i = 0;
	if (check_starting_wildcard(&i, &file, expr, &chunks) == 1)
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
	remove quotes from a stararr only used in wildcard matching!
	modifies the input string!
 */
void	quote_removal_strarr(char **strarr)
{
	int		i;
	char	*tmp;

	i = 0;
	while (strarr[i])
	{
		tmp = quote_removal(strarr[i]);
		free(strarr[i]);
		strarr[i] = tmp;
		i++;
	}
}

/*
	updates the file string to what's left to match against
	the i chunk from the expression

	Returns 0 if we should stop iterating over the chunks
	(because we're at the end or we've mismatched)

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
	*file = tmp + ft_strlen(chunks[i]);
	return (1);
}


/*
	cleans up chunks if ret is 1
	checks if there is a starting wildcard and return accordingly
 */
int	check_starting_wildcard(int *i, char **file, char *expr, char ***chunks)
{
	if (*file[0] == '.' && expr[0] != '.')
	{
		strarr_cleanup(*chunks);
		return (1);
	}
	if (expr[0] != '*')
	{
		if (0 != ft_strncmp(*file, *chunks[0], ft_strlen(*chunks[0])))
		{
			strarr_cleanup(*chunks);
			return (1);
		}
		*file = *file + ft_strlen(*chunks[0]);
		*i = *i + 1;
	}
	return (0);
}

/*
	checks if we end with a wildcard and return accordingly

	How does this function work????

	Possibilities for file:
	either "" since we've matched the entire string

	either "something" if the last wildcard we matched wasn't at the end
	then we must check if the last chunk of the file matches the wildcard

	either "aaaa"
	then the last chunks could overlap.

*/
int	check_ending_wildcard(int i, char *file, char *expr, char **chunks)
{
	int	ret;
	int	y;

	printf("file: {%s}\n", file);
	y = ft_strlen(file) - 1;
	ret = 1;
	if (expr[ft_strlen(expr) - 1] != '*')
	{
		while (y >= 0)
		{
			if (ft_strncmp(file + y, chunks[i - 1], ft_strlen(file)) == 0)
			{
				ret = 1;
				break ;
			}
			else
			{
				ret = 0;
			}
			y--;
		}
	}
	return (ret);
}
