/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:49:11 by znichola          #+#    #+#             */
/*   Updated: 2023/02/08 11:52:49 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_biga(int *a, int b);
static int	check_bigb(int *a, int b);

int	safe_atoi(int *n, char **str)
{
	int	s;

	*n = 0;
	s = 1;
	while (**str == ' ' || **str == '\f' || **str == '\n'
		|| **str == '\r' || **str == '\t' || **str == '\v')
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			s = -1;
		(*str)++;
	}
	if (!(**str >= '0' && **str <= '9'))
		return (FAILIUR);
	while (**str >= '0' && **str <= '9')
	{
		if (!(safe_multi(n, 10) + safe_add(n, **str - '0') == SUCCESS))
			return (FAILIUR);
		(*str)++;
	}
	if (!(**str == ' ' || **str == '\0'))
		return (FAILIUR);
	safe_multi(n, s);
	return (SUCCESS);
}

int	safe_multi(int *a, int b)
{
	if (b == 0 || *a == 0)
	{
		*a = 0;
		return (SUCCESS);
	}
	if (check_biga(a, b) == 1)
		return (1);
	if (check_bigb(a, b) == 1)
		return (1);
	*a = *a * b;
	return (SUCCESS);
}

int	safe_add(int *a, int b)
{
	if (a > 0 && b > FT_INT_MAX - *a)
		return (1);
	else if (a < 0 && b < FT_INT_MIN - *a)
		return (1);
	*a = *a + b;
	return (SUCCESS);
}

static int	check_biga(int *a, int b)
{
	if (b == 0 || *a == 0)
	{
		*a = 0;
		return (SUCCESS);
	}
	if (*a > 0)
	{
		if (b > 0)
		{
			if (*a > (FT_INT_MAX / b))
				return (1);
		}
		else
			if ((b < 0) && b < (FT_INT_MIN / *a))
				return (1);
	}
	return (SUCCESS);
}

static int	check_bigb(int *a, int b)
{
	if (!(*a > 0))
	{
		if (b > 0)
		{
			if (*a < (FT_INT_MIN / b))
				return (1);
		}
		else
			if (b < (FT_INT_MAX / *a))
				return (1);
	}
	return (SUCCESS);
}
