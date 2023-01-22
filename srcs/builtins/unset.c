/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:26:42 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/22 17:43:51 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	unset builtin: unset environment variables.
*/
int	exec_unset(char **args, t_env **env)
{
	int		ret;
	char	*quoted_id;

	ret = 0;
	while (*args)
	{
		if (!is_valid_identifier(*args))
		{
			quoted_id = in_quotes(*args);
			print_error("unset", quoted_id, "not a valid identifier");
			free(quoted_id);
			ret = 1;
		}
		else
		{
			env_remove(env, *args);
		}
		args++;
	}
	return (ret);
}
