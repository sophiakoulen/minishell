/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:40:00 by znichola          #+#    #+#             */
/*   Updated: 2023/02/07 15:05:10 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/* used in parse_item */
# define NO_MODIFIER -1

/* used in parsing */
# ifdef SUCCESS
#  undef SUCCESS
# endif

# define SUCCESS 0
# define STOP -1
# define SYNTAX_ERROR -2

/* used in expansion */
# define T_IFS " 	\n"

/* used in expansion */
#define MSH_DQUOTE	1U
#define MSH_SQUOTE	2U
#define MSH_ESCAPED	4U

/* colours, used in shout builtin */

# define T_BLUE "\033[38:5:117m"
# define T_RED "\033[38:5:197m"
# define T_RESET "\033[0m"

/* Possible token types corresponding strings defined in structs/t_token.c */
# define NUM_TOKEN_LITERALS 9

/* used for finding commands */
# define DEFAULT_PATH "/usr/bin:/bin"

/* used for expansion */
# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39

enum e_token_type
{
	e_or,			// ||
	e_pipe,			// |
	e_heredoc,		// <<
	e_infile,		// <
	e_append,		// >>
	e_outfile,		// >
	e_open_brace,	// (
	e_close_brace,	// )
	e_and,			// &&
	e_end,			// \n or \r\n
	e_string,
};

# define NUM_BUILTINS 8

enum e_builtin
{
	e_echo,
	e_cd,
	e_pwd,
	e_export,
	e_unset,
	e_env,
	e_exit,
	e_shout,
};

/* prompts */

# define BLUE_PROMPT "minishell\001\033[38:5:117m\002$\001\033[0m\002 "
# define RED_PROMPT "minishell\001\033[38:5:197m\002$\001\033[0m\002 "

#endif
