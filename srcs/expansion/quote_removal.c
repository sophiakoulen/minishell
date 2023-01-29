/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:02:44 by znichola          #+#    #+#             */
/*   Updated: 2023/01/29 13:31:58 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//l$USR"a"

static void	next_word(t_list *word, char **str);
static char	*get_bare_word(char **str);
static char	*get_single_q_word(char **str);
static char	*get_double_q_word(char **str);

/*
	- string expansion steps -
	remove outside quotes
	preserve spaces
	if replacing an env variable remove the extra spaces inbetween the new caracters
 */


/*
	remove extra single_quotes quotes from a string
 */
char	*quote_removal(char *str)
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

/*
	Quote removal, repecting escaped sequences.
*/
char	*quote_removal2(char *str)
{
	int		state;
	int		i;
	char	*res;

	res = x_malloc(1, ft_strlen(str) + 1);
	state = 0;
	i = 0;
	while (*str)
	{
		if (!update_state(str, &state))
		{
			res[i] = *str;
			i++;
		}
		str++;
	}
	res[i] = 0;
	return (res);
}

/*
	removes the quotes around words and returns the resulting strings
	also expands $variables inside the quotes.
 */
static void	next_word(t_list *word, char **str)
{
	char	*s1;
	char	*s2;

	s1 = get_bare_word(str);
	if (**str == SINGLE_QUOTE || **str == '\0')
		s2 = get_single_q_word(str);
	else
		s2 = get_double_q_word(str);
	word->content = (char *)ft_strjoin(s1, s2);
	free(s1);
	free(s2);
}


static char	*get_bare_word(char **str)
{
	int		i;
	char	*ret;

	i = 0;
	while ((*str)[i] && (*str)[i] != SINGLE_QUOTE && (*str)[i] != DOUBLE_QUOTE)
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

/*
	This stage we remove the double quotes
	Variables in double quotes don't produce two words!
 */
static char	*get_double_q_word(char **str)
{
	int		i;
	char	*ret;
	// char	*s1;
	// char	*s2;

	i = 1;
	if ((*str)[0] == '\0')
		return (ft_substr(*str, 0, 0));
	while ((*str)[i])
	{
		if ((*str)[i] == DOUBLE_QUOTE)
		{
			ret = ft_substr(*str, 1, i  - 1);
			*str += i + 1;
			return (ret);
		}
		// if ((*str)[i] == '$')
		// {
		// 	s1 = ft_substr(*str, 1, i  - 1);
		// 	*str += i;
		// 	s2 = get_env_variable(str, env);
		// 	ret =ft_strjoin(s1, s2);
		// 	free(s1);
		// 	free(s2);
		// 	return (ret);
		// }
		i++;
	}
	ret = ft_substr(*str, 1, i);
	*str += i;
	return (ret);
}
