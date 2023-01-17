/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strarr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:55:21 by znichola          #+#    #+#             */
/*   Updated: 2023/01/17 10:35:41 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	FILE AND FUNCTIONS UNUSED AND NOT IN MAKEFILE!
 */

/*
	appends a new string to the array
	mallocs a new string arrary NULL terminating it
	doesn't free strarr & doesn't free new
	it should be ok to give two NULL, but just don't
 */
char	**append_strarr(char **strarr, char *new)
{
	char	**ret;
	int		l;
	int		i;

	i = 0;
	l = 0;
	while (strarr && strarr[l])
		l++;
	ret = (char **)x_malloc(sizeof(char *), l + 2);
	while (strarr && i < l)
	{
		ret[i] = ft_strdup(strarr[i]);
		i++;
	}
	if (new)
		ret[i] = ft_strdup(new);
	ret[i + 1] = NULL;
	return (ret);
}
