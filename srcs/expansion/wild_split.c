/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:57:14 by znichola          #+#    #+#             */
/*   Updated: 2023/02/09 11:42:07 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_freeme(char **s, int i);
static char	*ft_nextword(char **str, char const c);
static int	ft_countwords(char const *s, char const c);
static void	update_wld_state(char c, int *state);

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

static void	update_wld_state(char c, int *state)
{
	if (c == SINGLE_QUOTE && !(*state & MSH_DQUOTE) && !(*state & MSH_ESCAPED))
	{
		*state ^= MSH_SQUOTE;
	}
	else if (c == DOUBLE_QUOTE && !(*state & MSH_SQUOTE) && !(*state & MSH_ESCAPED))
	{
		*state ^= MSH_DQUOTE;
	}
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
	// printf("\n");
	// update_wld_state(*end, &state);
	while (*end != '\0' && !(*end == c && !state))
	// while (*end != '\0')
	{
		// printf("%c:  %d : %d  [%d]\n", *end, *end == c, state, !(*end == c && !state));
		update_wld_state(*end, &state);
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
		update_wld_state(*s, &state);
		// printf("%c:%d f:%d\n", *s, state, flag);
		if (state == 0 && *s == c)
			flag = 0;
		else
			flag = 1;
		if (old_flag != flag && flag == 1)
			count++;
		s++;
	}
	// printf("count:%d\n\n", count);
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
