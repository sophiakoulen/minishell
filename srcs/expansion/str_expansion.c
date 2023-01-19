/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:02:44 by znichola          #+#    #+#             */
/*   Updated: 2023/01/19 18:26:30 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//l$USR"a"

char		*list_to_str(t_list *word);
static void	next_word(t_list *word, char **str);

/*
	- string expansion steps -
	remove outside quotes
	preserve spaces
	if replacing an env variable remove the extra spaces inbetween the new caracters
 */


/*
	remove extra single_quotes quotes from a string
 */
char	*str_expansion(char *str)
{
	t_list	*words;
	t_list	*tmp;
	char	*ret;

	words = NULL;
	while (str && *str)
	{
		tmp = ft_lstnew(NULL);
		next_word(tmp, &str);
		ft_lstadd_back(&words, tmp);
	}
	ret = list_to_str(words);
	ft_lstclear(&words, free);
	return (ret);
}

static char	*get_bare_word(char **str)
{
	int		i;
	char	*ret;

	i = 0;
	while ((*str)[i] && (*str)[i] != SINGLE_QUOTE)
		i++;

	ret = ft_substr(*str, 0, i);
	*str += i;
	return (ret);
}

static char	*get_single_q_word(char **str)
{
	int		i;
	char	*ret;

	i = 1;
	if ((*str)[0] == '\0')
		return (ft_substr(*str, 0, 0));
	while ((*str)[i])
	{
		if ((*str)[i] == SINGLE_QUOTE)
		{
			ret = ft_substr(*str, 1, i  - 1);
			*str += i + 1;
			return (ret);
		}
		i++;
	}
	ret = ft_substr(*str, 1, i);
	*str += i;
	return (ret);
}

static void	next_word(t_list *word, char **str)
{
	char	*s1;
	char	*s2;

	s1 = get_bare_word(str);
	s2 = get_single_q_word(str);

	// ft_printf("\nbare word:%s\n", s1);
	// ft_printf("single word:%s\n", s2);
	word->content = (char *)ft_strjoin(s1, s2);
	free(s1);
	free(s2);
}


void	words_print(t_list *word)
{
	if (word == NULL)
		return ;
	ft_printf("{%s}", (char *)word->content);
	words_print(word->next);
}

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
