/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:05:35 by znichola          #+#    #+#             */
/*   Updated: 2023/01/29 18:27:31 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_words(t_list *words)
// {
// 	if (!words)
// 		return ;
// 	ft_printf("{%s} ", (char *)words->content);
// 	print_words(words->next);
// }

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int		retn;

	retn = 42;
	env = init_env(envp);
	// strarr_print(env_to_strarr(env));
	if (argc != 2)
		return (0);
	char * str = param_expansion(argv[1], env, retn);
	env_cleanup_all(env);
	ft_printf("{%s}", str);
	ft_printf("\n");
	free(str);
	exit(0);
}
