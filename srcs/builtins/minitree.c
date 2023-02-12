/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:31:06 by znichola          #+#    #+#             */
/*   Updated: 2023/02/12 12:09:52 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define HIGHLIGT_RED 1
// #define HIGHLIGT_BLUE 2
// #define HIGHLIGT_BOLD 4

static int	parse_and_print(char *arg, int options);
static int	parse_options(char ***args);
static int	is_valid_option(char *arg);

/*
	prints the argument ast as it's parsed by our tokenizer and parcing
	minitree 'a|b|c|d&&j|g<u|k>o||(w<<e|r&&(b|g<o)||q>>f)'
 */
int	minitree(char **args, t_env **env, int prev)
{
	int	options;

	(void)env;
	(void)prev;
	options = 0;
	if (!args)
		return (2);
	options = parse_options(&args);
	if (options & HIGHLIGT_RED)
		ft_printf("\n ~red highlighting not implemented yet!\n\n");
	if (*args)
		return (parse_and_print(*args, options));
	ft_printf("\nUsage:  minitree [opt] 'minishell comand'\n");
	ft_printf("   eg:  minitree 'a&&b|c||(d&&e&&(f||g))'\n");
	ft_printf("\nOptions:\n         -r  highlight key tokens in red\n");
	return (1);
}

static int	parse_and_print(char *arg, int options)
{
	t_token	*tok_list;
	t_token	*start;
	t_tree	*tree;

	(void)options;
	if (construct_tok_list(&tok_list, arg) != 0)
	{
		tok_list_cleanup(tok_list);
		return (1);
	}
	start = tok_list;
	if (parse_tree(&tree, &tok_list) != SYNTAX_ERROR)
		print_minitree(tree, NULL, 0);
	trunk_garbage_collector(NULL);
	tree_cleanup(tree);
	tok_list_cleanup(start);
	return (0);
}

/*
	Currently, the only supported option is "-r" which
	highlites | || && in red

	see echo for detailed explication of how it works.
*/
static int	parse_options(char ***args)
{
	int	options;

	options = 0;
	while (*args && is_valid_option(**args))
	{
		options |= HIGHLIGT_RED;
		(*args)++;
	}
	return (options);
}

/*
	Only "-r" is a valid option.
*/
static int	is_valid_option(char *arg)
{
	if (!arg)
		return (0);
	if (strncmp(arg, "-r", 2) == 0)
		return (HIGHLIGT_RED);
	return (0);
}
