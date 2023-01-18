/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:18:55 by znichola          #+#    #+#             */
/*   Updated: 2023/01/18 15:06:58 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int		ret;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	ret = exec_env(env_to_strarr(env));
	env_cleanup(env);
	return (ret);
}
