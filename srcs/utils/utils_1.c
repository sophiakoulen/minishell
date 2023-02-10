/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:16:52 by znichola          #+#    #+#             */
/*   Updated: 2023/02/10 10:27:32 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	wrapper for malloc, if we can't allocate memory, exit; just like bash!
 */
void	*x_malloc(size_t size, size_t quantity)
{
	void	*ret;

	ret = (void *)malloc(size * quantity);
	if (!ret)
	{
		perror("failed to allocate more memory, quitting.");
		exit(2);
	}
	return (ret);
}

int	ft_isspace(int c)
{
	return (c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r'
		|| c == ' ');
}

void	do_nothing(void *thing)
{
	(void)thing;
	return ;
}

void	strarr_cleanup(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
}

void	strarr_print(char **s)
{
	while (*s)
	{
		ft_printf("%s\n", *s);
		s++;
	}
}
