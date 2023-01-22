/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:07:13 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/22 13:11:49 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	greater(char *str1, char *str2);
static void	swap(char **str1, char **str2);

/*
	Sort the environment variables list using bubblesort.
*/
void	sort_env(t_env **env)
{
	int		sorted;
	t_env	*current;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		current = *env;
		while (current && current->next)
		{
			if (greater(current->key, current->next->key))
			{
				sorted = 0;
				swap(&current->key, &current->next->key);
				swap(&current->value, &current->next->value);
			}
			current = current->next;
		}
	}	
}

/*
	Checks if string str1 is lexographically greater compared
	to string str2.
*/
static int	greater(char *str1, char *str2)
{
	int	len;

	len = ft_strlen(str1);
	return (ft_strncmp(str1, str2, len + 1) > 0);
}

/*
	Exchange two strings in memory.
*/
static void	swap(char **str1, char **str2)
{
	char	*tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}
