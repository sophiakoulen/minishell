/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:31:06 by znichola          #+#    #+#             */
/*   Updated: 2023/02/12 02:23:35 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_pipeline2(t_list *lst);
void 		print_tree2(t_tree *root, int space, int isright);
static void	print_cmd2(t_item *lst);

int	minitree(char **args, t_env **env, int prev)
{
	t_token	*tok_list;
	t_token	*start;
	t_tree	*tree;

	(void)env;
	(void)prev;
	if (!*args)
		return (1);
	if (construct_tok_list(&tok_list, *args) != 0)
		return (258);
	start = tok_list;
	if (parse_tree(&tree, &tok_list) != SYNTAX_ERROR)
		print_tree2(tree, 0);
	else
		return (258);
	tree_cleanup(tree);
	tok_list_cleanup(start);
	return (0);
}


void print_tree2(t_tree *root, int space, int isright)
{
	int	i;
	int	s;
	int	line;

	if (root == NULL)
		return;

	i = 5;
	s = space;
	space += i;
	line = 1;
	print_tree2(root->left, space, 1);


	// while (i++ < s)
	// 	ft_printf(" ");
	// while (s++ < space)
	// 	ft_printf("-");

	while (i++ < space)
	{
		if (i < s + 2)
			ft_printf(" ");
		else if (line)
		{
			// ft_printf("o");
			line = 0;
		}
		else
			ft_printf("-");
	}


	if (root->pipeline)
		print_pipeline2(root->pipeline);
	else
		ft_printf("%s", ret_token_literal(root->type));

	ft_printf("\n");

	print_tree2(root->right, space, 0);
}

static void	print_pipeline2(t_list *lst)
{
	int	n;

	n = ft_lstsize(lst);
	// printf("%d", n);
	while (lst)
	{
		print_cmd2(lst->content);
		lst = lst->next;
	}
}

static void	print_cmd2(t_item *lst)
{
	t_item	*current;

	current = lst;
	while (current)
	{
		if (current->modifier == NO_MODIFIER)
			ft_printf("%s ", current->word);
		current = current->next;
	}
	ft_printf(":");
	current = lst;
	while (current)
	{
		if (current->modifier != NO_MODIFIER)
			ft_printf("%s %s ",
				ret_token_literal(current->modifier), current->word);
		current = current->next;
	}
}
