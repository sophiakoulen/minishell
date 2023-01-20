/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:54:24 by znichola          #+#    #+#             */
/*   Updated: 2023/01/20 14:01:21 by znichola         ###   ########.fr       */
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
	(void)envp;
	// t_env	*env;

	// env = init_env(envp);
	// strarr_print(env_to_strarr(env));
	if (argc != 2)
		return (0);
	char * str = quote_removal(argv[1]);
	ft_printf("{%s}", str);
	ft_printf("\n");
	free(str);
}
