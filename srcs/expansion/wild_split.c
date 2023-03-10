/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:57:14 by znichola          #+#    #+#             */
/*   Updated: 2023/02/10 17:51:02 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_freeme(char **s, int i);
static char	*ft_nextword(char **str, char const c);
static int	ft_countwords(char const *s, char const c);

char	**wild_split(char const *s, char c)
{
	char	**ret;
	int		i;
	int		word_count;

	word_count = ft_countwords(s, c);
	ret = (char **)x_malloc(sizeof(char *), word_count + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < word_count)
	{
		ret[i] = ft_nextword((char **)&s, c);
		if (ret[i] == NULL)
		{
			ft_freeme(ret, i);
			return (NULL);
		}
	}
	ret[i] = NULL;
	return (ret);
}

static char	*ft_nextword(char **str, char const c)
{
	char	*ret;
	char	*end;
	size_t	len;
	int		state;

	while (**str == c && **str != '\0')
		(*str)++;
	end = (char *)*str;
	state = 0;
	while (*end != '\0' && !(*end == c && !state))
	{
		update_state(end, &state);
		end++;
	}
	len = end - *str + 1;
	ret = (char *)x_malloc(sizeof(char), len);
	if (!ret)
		return (NULL);
	end = ret;
	while (len-- > 1)
		*end++ = *(*str)++;
	*end = '\0';
	return (ret);
}

static int	ft_countwords(char const *s, char const c)
{
	int		count;
	int		flag;
	int		old_flag;
	int		state;

	flag = -1;
	count = 0;
	state = 0;
	while (*s)
	{
		old_flag = flag;
		update_state((char *)s, &state);
		if (state == 0 && *s == c)
			flag = 0;
		else
			flag = 1;
		if (old_flag != flag && flag == 1)
			count++;
		s++;
	}
	return (count);
}

static void	ft_freeme(char **s, int i)
{
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
}
