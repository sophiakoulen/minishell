/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:52:48 by znichola          #+#    #+#             */
/*   Updated: 2023/01/20 17:33:42 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	next_word(t_list *word, char **str, t_env *env, int retn);
static int	get_bare_word(char **str, char **ret);
static int	get_single_q_word(char **str, char **ret);
static int	get_double_q_word(char **str, char **ret, t_env *env, int retn);
static int	get_env_variable(char **str, char **ret, t_env *env, int retn);
static int	get_tilde_variable(char **str, char **ret, t_env *env);

/*
	expand env parameter, replace $VAR $? $~
	cleans up after it's self, mallocs new return string
 */
char	*param_expansion(char *str, t_env *env, int retn)
{
	t_list	*words;
	t_list	*tmp;
	char	*ret;

	words = NULL;
	while (str && *str)
	{
		tmp = ft_lstnew(NULL);
		next_word(tmp, &str, env, retn);
		ft_lstadd_back(&words, tmp);
	}
	ret = list_to_str(words);
	ft_lstclear(&words, free);

	return(ret);
}

/*
	looks for the next "word" / chunk
	 1 check single quote   start '  stop at ' \0
	 2 check double quote   start "  stop at " \0
	 3 check var param      start $  stop at $ ? ~ " '
	 4 check tilde          start ~  only do ~
	 5 check bare word    letters    stop at " ' $ \0 ~
	these function also put the str in ret and advance str
 */
static void	next_word(t_list *word, char **str, t_env *env, int retn)
{
	char	*ret;

	if (get_bare_word(str, &ret))
		;
	else if (get_single_q_word(str, &ret))
		;
	else if (get_double_q_word(str, &ret, env, retn))
		;
	else if (get_env_variable(str, &ret, env, retn))
		;
	else if (get_tilde_variable(str, &ret, env))
		;
	else
	{
		ft_printf("DEBUG: error detecting end of word");
		ret = ft_substr(*str, 0, 0);
	}

	word->content = ret;
}

/*
	check single quote   start '  stop at ' \0
	return 1 on sucess and ret is filled with malloced string
 */
static int	get_single_q_word(char **str, char **ret)
{
	int		i;

	i = 1;
	if ((*str)[0] == '\0' || **str != SINGLE_QUOTE)
		return (0);
	while ((*str)[i] && ft_strchr("\'", (*str)[i]) == NULL)
		i++;
	if (i == 0)
		return (0);
	*ret = ft_substr(*str, 0, i);
	*str += i;
	return (1);
}

/*
	check double quote   start "  stop at " \0
	return 1 on sucess and ret is filled with malloced string
 */
static int	get_double_q_word(char **str, char **ret, t_env *env, int retn)
{
	int		i;
	int		single_q;
	char	*s1;
	char	*s2;
	char	*tmp;

	i = 1;
	if ((*str)[0] == '\0' || (**str != DOUBLE_QUOTE))
		return (0);
	s1 = x_malloc(sizeof(char), 1);
	s1[0] = '\0';
	while ((*str)[i] && ft_strchr("\"$", (*str)[i]) == NULL)
	{
		if ((*str)[i] == SINGLE_QUOTE)
			single_q = 1;
		if (single_q && (*str)[i] == '$')
		{
			tmp = ft_substr(*str, 0, i);
			s1 = ft_strjoin(s1, tmp);
			free(tmp);
			if (get_env_variable(str, &s2, env, retn))
			{
				tmp = ft_strjoin(s1, s2);
				free(s2);
				free(s1);
				s1 = tmp;
				free(tmp);
			}
		}
		// ft_printf("adsad\n");
		// much needs to happen here
		// return (get_env_variable(str, ret, env, retn));
		i++;
	}
	if (i == 0)
		return (0);
	*ret = ft_substr(*str, 0, i);
	*str += i;
	return (1);
}

/*
	check var param      start $  stop at $ ? ~ " '
	return 1 on sucess and ret is filled with malloced string
 */
static int	get_env_variable(char **str, char **ret, t_env *env, int retn)
{
	int		i;
	char	*key;
	char	*value;

	(void)retn;

	if ((*str)[0] == '\0' || (*str)[0] != '$')
		return (0);
	i = 1;
	if ((*str)[1] == '?')
	{
		*ret = ft_strdup(ft_itoa(retn));
		return (1);
	}
	while ((*str)[i] && ft_strchr("\'\"$", (*str)[i]) == NULL && ft_strchr(T_IFS, (*str)[i]) == NULL)
		i++;
	key = ft_substr(*str, 1, i - 1);
	value = ret_env_key(env, key);
	if (value == NULL)
		value = ft_strchr(key, '\0');
	free(key);
	*str += i;
	// ft_printf("key is:%s\n", key);
	// ft_printf("value is:%s\n", value);
	*ret = ft_strdup(value);
	return (1);
}

/*
	check tilde          start ~  only do ~
	return 1 on sucess and ret is filled with malloced string
 */
static int	get_tilde_variable(char **str, char **ret, t_env *env)
{
	char	*tmp;

	if ((*str)[0] == '\0' || (*str)[0] != '~')
		return (0);
	tmp = ret_env_key(env, "HOME");
	*str += 1;
	if (tmp == NULL)
		return (0);
	*ret = ft_strdup(tmp);
	return (1);
}


/*
	check bare word    letters    stop at " ' $ \0 ~
	return 1 on sucess and ret is filled with malloced string
 */
static int	get_bare_word(char **str, char **ret)
{
	int		i;

	i = 0;
	while ((*str)[i] && ft_strchr("\'\"$~", (*str)[i]) == NULL)
		i++;
	if (i == 0)
		return (0);
	*ret = ft_substr(*str, 0, i);
	*str += i;
	return (1);
}
