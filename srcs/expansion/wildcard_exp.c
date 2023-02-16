/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:02:38 by znichola          #+#    #+#             */
/*   Updated: 2023/02/16 16:26:04 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_empty_and_sort(t_list **words, char **ret, char *str);

/*
	ret contains a malloced string containing
	all matched files/folders seperated by a space
	if no matches are found return the expression string.
*/
void	find_wildcard_matches(char **ret, char *str)
{
	struct dirent	*dir_entry;
	DIR				*dir;
	t_list			*words;

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
			ft_lstadd_back(&words,
				ft_lstnew((char *)ft_strjoin(dir_entry->d_name, " ")));
		dir_entry = readdir(dir);
	}
	check_empty_and_sort(&words, ret, str);
	ft_lstclear(&words, free);
	closedir(dir);
}

static void	check_empty_and_sort(t_list **words, char **ret, char *str)
{
	char	*escaped;

	if (*words == NULL)
		*ret = ft_strjoin(str, " ");
	else
	{
		lst_bubble_sort(words, ft_strcmp);
		*ret = list_to_str(*words);
		escaped = escape_special_chars(*ret, ESC_TYPE_DEFAULT);
		free(*ret);
		*ret = escaped;
	}
}
