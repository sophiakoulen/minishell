/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:48:25 by znichola          #+#    #+#             */
/*   Updated: 2023/02/16 16:35:44 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lst_words_len(t_list *word, size_t *len)
{
	if (!word)
		return ;
	*len += ft_strlen((char *)word->content);
	lst_words_len(word->next, len);
}

/*
	tranforms a linked list of words to a single string
 */
char	*list_to_str(t_list *word)
{
	char	*ret;
	size_t	size;

	size = 1;
	lst_words_len(word, &size);
	ret = (char *)x_malloc(sizeof(char), size + 1);
	ret[0] = '\0';
	while (word)
	{
		ft_strlcat(ret, word->content, size);
		word = word->next;
	}
	return (ret);
}

void	words_print(t_list *word)
{
	if (word == NULL)
		return ;
	ft_printf("{%s}", (char *)word->content);
	words_print(word->next);
}

/*
	frees the two input strings!
	returns a new malloced string
 */
char	*ft_strmerge(char *s1, char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (ret);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	max_len;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 >= len2)
		max_len = len1;
	else
		max_len = len2;
	return (ft_strncmp(s1, s2, max_len + 1));
}
