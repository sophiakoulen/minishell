/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:48:25 by znichola          #+#    #+#             */
/*   Updated: 2023/01/26 09:09:52 by znichola         ###   ########.fr       */
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

char	*list_to_str(t_list *word)
{
	char	*ret;
	size_t	size;

	size = 1;
	lst_words_len(word, &size);
	ret = (char *)x_malloc(sizeof(char), size + 1);
	ret[0] = '\0';
	// ft_printf("size%d\n", size);
	while (word)
	{
		// ft_printf("-%s-\n", word->content);
		ft_strlcat(ret, word->content, size);
		word = word->next;
	}
	// ft_printf("<%s>\n", ret);
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
