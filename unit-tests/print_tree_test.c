/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 08:22:31 by znichola          #+#    #+#             */
/*   Updated: 2023/01/15 08:39:51 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_tests.h"

static void	print_token(t_tree *node)
{
	printf("\033[1D");
	if (node->type == e_string)
	{
		printf("%s", node->str);
		return ;
	}
	printf("%s", ret_token_literal(node->type));
}

static void print_connector(t_pos p, char dir, int depth)
{
	if (dir == 'l')
	{
		while (depth--)
		{
			printf("\033[%d;%dH/", p.y+1, p.x-1);
			p = (t_pos){p.x - 1, p.y + 1};
		}
	}
	else if (dir == 'r')
	{
		while (depth--)
		{
			printf("\033[%d;%dH\\", p.y+1, p.x+1);
			p = (t_pos){p.x + 1, p.y + 1};
		}
	}
}

void	print_tree(t_pos p, t_tree *tree)
{
	int		size;

	size = 3;
	if (tree->type != e_string)
	{
		printf("\033[%d;%dH", p.y, p.x + 1);
		print_token(tree);

		size = get_tree_max_width(tree);
		// printf("\033[%d;0H", p.y);
		// printf("s:%d", get_tree_max_width(tree));
		if (tree->left != NULL)
		{
			print_connector(p, 'l', size);
			print_tree((t_pos){p.x - size, p.y + size}, tree->left);
		}
		if (tree->right != NULL)
		{
			print_connector(p, 'r', size);
			print_tree((t_pos){p.x + size, p.y + size}, tree->right);
		}
	}
	else if (tree->type == e_string)
	{
		printf("\033[%d;%dH", p.y, p.x);
		print_token(tree);
	}
}

// wrapper for the print tree that
// calculates very roughly the space it needs
void	auto_print_tree(t_tree *tree)
{
	int	width;
	int	height;

	width = get_tree_max_width(tree) * 6;
	height = get_tree_height(tree) * 4;
	printf("\033[2J\033[1;1H");
	print_tree((t_pos){width, 2}, tree);
	printf("\033[%d;0H", height);
	printf("\n");
}
