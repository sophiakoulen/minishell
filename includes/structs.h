/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:30:09 by znichola          #+#    #+#             */
/*   Updated: 2023/02/01 11:51:37 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "defines.h"

/* **************************************************************************

	sructs/t_struct.c -- expected structure

	t_struct	*struct_factory(t_struct *blueprint);

	t_struct	*struct_print(t_struct);

	t_struct	*struct_cleanup(t_struct);

   ************************************************************************** */

/*
	basic token linked list
	- the tokenization stage fills this list
	- all subsequent parsing ops happen this list
 */
typedef struct s_token
{
	enum e_token_type	type;
	char				*str;
	struct s_token		*next;
}	t_token;

/*
	tree structure containing the exicution order information
 */
typedef struct s_tree
{
	enum e_token_type	type;
	char				*str;
	struct s_tree		*left;
	struct s_tree		*right;
}	t_tree;

/*
	info we need during the execution phase.

	- input and output file descriptors we'll need to redirect to
	- full path of the command if it is found in PATH or already a path
	- status of the command. 0 means we can execute.
*/
typedef struct s_cmd
{
	int		i_fd;
	int		o_fd;
	char	*full_path;
	int		status;
	char	*hd_buffer;
	int		builtin;
	char	**args;
	int		i;
	int		n;
}	t_cmd;

/**
 * Screen posiiton struct.
 * used in print tree and TODO: for cool intro animations
 */
typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_item
{
	char			*word;
	int				modifier;
	struct s_item	*next;
}	t_item;

/*
	environment variable struct
*/
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_exec
{
	int		n;

	int		**hd_pipes;
	int		**pipes;

	int		fd_count;

	char	**path;

	t_env	**env;
	int		prev;

	t_cmd	*cmds;

}	t_exec;

#endif
