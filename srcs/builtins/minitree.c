/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:31:06 by znichola          #+#    #+#             */
/*   Updated: 2023/02/12 11:05:19 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_minitree_pipeline(t_list *lst);
static void		print_minitree(t_tree *root, t_trunk *prev, int isright);
static void		print_minitree_cmd(t_item *lst);

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
		print_minitree(tree, NULL, 0);
	else
		return (258);
	trunk_garbage_collector(NULL);
	tree_cleanup(tree);
	tok_list_cleanup(start);
	return (0);
}

static void print_minitree(t_tree *root, t_trunk *prev, int isright)
{
	char	*prev_str;
	t_trunk	*trunk;

	if (root == NULL)
		return;

	prev_str = TREE_EMPTY;
	trunk = trunk_factory(&(t_trunk){TREE_EMPTY, prev});
	print_minitree(root->left, trunk, 1);

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

	trunk_print(trunk);
	if (root->pipeline)
		print_minitree_pipeline(root->pipeline);
	else
		ft_printf("%s", ret_token_literal(root->type));
	ft_printf("\n");

	if (prev)
		prev->str = prev_str;
	trunk->str = TREE_VERT_JOINT;

	print_minitree(root->right, trunk, 0);
}

static void	print_minitree_pipeline(t_list *lst)
{
	int	flag;

	if (lst == NULL)
		return ;
	ft_printf(" ");
	flag = 0;
	while (lst)
	{
		if (flag)
			ft_printf("| ");
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
	// ft_printf("");
	current = lst;
	while (current)
	{
		if (current->modifier != NO_MODIFIER)
			ft_printf("%s%s ",
				ret_token_literal(current->modifier), current->word);
		current = current->next;
	}
}
