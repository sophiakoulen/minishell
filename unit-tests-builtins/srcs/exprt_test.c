/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exprt_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:58:15 by znichola          #+#    #+#             */
/*   Updated: 2023/01/26 13:27:56 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int		ret;
	char	**strs;

	(void)argc;
	env = init_env(envp);
	ret = exec_export(argv, &env, 42);
	strs = env_to_strarr(env);
	strarr_print(strs);
	strarr_cleanup(strs);
	env_cleanup(env);
	return (ret);
}
