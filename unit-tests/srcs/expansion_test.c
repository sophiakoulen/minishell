/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:07:13 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/10 12:23:27 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_lst(t_list *lst);

int	main(int argc, char **argv, char **envp)
{
	t_list	*lst;
	t_list	*expanded;
	t_env	*env;

	lst = NULL;
	argv++;
	while (*argv)
	{
		ft_lstadd_back(&lst, ft_lstnew(*argv));
		argv++;
	}
	env = init_env(envp);
	expanded = expand_args_list(lst, env, 42);
	ft_lstclear(&lst, do_nothing);
	env_cleanup_all(env);
	print_lst(expanded);
	ft_lstclear(&expanded, free);
}

static void	print_lst(t_list *lst)
{
	while (lst)
	{
		ft_printf("{%s} ", lst->content);
		lst = lst->next;
	}
	ft_printf("\n");
}
