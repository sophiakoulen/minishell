/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tree_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:33:20 by znichola          #+#    #+#             */
/*   Updated: 2023/02/16 14:04:33 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_tree_node(t_tree *root, t_trunk *trunk, int opts);
static void		print_minitree_pipeline(t_list *lst, int opts);
static void		print_minitree_cmd(t_item *lst);

/*
	printf the ast using recursion
 */
void	print_minitree(t_tree *root, t_trunk *prev, int isright, int opts)
{
	char	*prev_str;
	t_trunk	*trunk;

	if (root == NULL)
		return ;
	prev_str = TREE_EMPTY;
	trunk = trunk_factory(&(t_trunk){TREE_EMPTY, prev});
	print_minitree(root->left, trunk, 1, opts);
	if (!prev)
		trunk->str = TREE_STRAGHT;
	else if (isright)
	{
		trunk->str = TREE_TOP_JOINT;
		prev_str = TREE_VERT_JOINT;
	}
	else
	{
		trunk->str = TREE_BOT_JOINT;
		prev->str = prev_str;
	}
	print_tree_node(root, trunk, opts);
	if (prev)
		prev->str = prev_str;
	trunk->str = TREE_VERT_JOINT;
	print_minitree(root->right, trunk, 0, opts);
}

/*
	prints a node of the tree
	the pipeline is a leaf
	token literal is the root node
 */
static void	print_tree_node(t_tree *root, t_trunk *trunk, int opts)
{
	trunk_print(trunk);
	if (root->pipeline)
		print_minitree_pipeline(root->pipeline, opts);
	else
	{
		if (opts & HIGHLIGT_RED)
			ft_printf(T_RED);
		ft_printf("%s", ret_token_literal(root->type));
		if (opts)
			ft_printf(T_RESET);
	}
	ft_printf("\n");
}

static void	print_minitree_pipeline(t_list *lst, int opts)
{
	int	flag;

	if (lst == NULL)
		return ;
	ft_printf(" ");
	flag = 0;
	while (lst)
	{
		if (flag)
		{
			if (opts & HIGHLIGT_RED)
				ft_printf(T_RED);
			ft_printf("| ");
			if (opts)
				ft_printf(T_RESET);
		}
		print_minitree_cmd(lst->content);
		lst = lst->next;
		flag = 1;
	}
}

static void	print_minitree_cmd(t_item *lst)
{
	t_item	*current;

	current = lst;
	while (current)
	{
		if (current->modifier == NO_MODIFIER)
			ft_printf("%s ", current->word);
		current = current->next;
	}
	current = lst;
	while (current)
	{
		if (current->modifier != NO_MODIFIER)
			ft_printf("%s%s ",
				ret_token_literal(current->modifier), current->word);
		current = current->next;
	}
}
