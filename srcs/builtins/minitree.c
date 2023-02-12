/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:31:06 by znichola          #+#    #+#             */
/*   Updated: 2023/02/12 03:07:50 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_pipeline2(t_list *lst);
void 			print_tree2(t_tree *root, t_trunk *prev, int isright);
static void		print_cmd2(t_item *lst);
static t_trunk	*trunk_factory(t_trunk *blueprint);
void			print_trunk(t_trunk *t);

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
		print_tree2(tree, NULL, 0);
	else
		return (258);
	tree_cleanup(tree);
	tok_list_cleanup(start);
	return (0);
}


void print_tree2(t_tree *root, t_trunk *prev, int isright)
{
	char	*prev_str;
	t_trunk	*trunk;
	if (root == NULL)
		return;

	prev_str = TREE_EMPTY;
	trunk = trunk_factory(&(t_trunk){TREE_EMPTY, prev});
	print_tree2(root->left, trunk, 1);

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

	print_trunk(trunk);
	if (root->pipeline)
		print_pipeline2(root->pipeline);
	else
		ft_printf("%s", ret_token_literal(root->type));
	ft_printf("\n");

	if (prev)
		prev->str = prev_str;
	trunk->str = TREE_VERT_JOINT;

	print_tree2(root->right, trunk, 0);
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

// Helper function to print branches of the binary tree
void print_trunk(t_trunk *t)
{
	if (t == NULL)
		return ;
	print_trunk(t->prev);
	ft_printf("%s", t->str);
}

/*
	trunk_factory(&(t_trunk){str, prev})
	call with blueprint or NULL
	Don't forget to free it after!
 */
static t_trunk	*trunk_factory(t_trunk *blueprint)
{
	t_trunk	*trunk;

	trunk = (t_trunk *)x_malloc(sizeof(t_trunk), 1);
	if (blueprint)
	{
		trunk->str = blueprint->str;
		trunk->prev = blueprint->prev;
	}
	else
	{
		trunk->str = NULL;
		trunk->prev = NULL;
	}
	return (trunk);
}
